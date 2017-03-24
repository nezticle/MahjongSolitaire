#include "textureatlas.h"

#include <Qt3DRender/qtexturedata.h>
#include <Qt3DRender/qabstracttextureimage.h>
#include <Qt3DCore/qpropertyupdatedchange.h>
#include <Qt3DCore/qpropertynodeaddedchange.h>
#include <Qt3DCore/qpropertynoderemovedchange.h>

TextureAtlas::TextureAtlas(Qt3DCore::QNode *parent)
    : Qt3DRender::QAbstractTexture(Qt3DRender::QAbstractTexture::TargetAutomatic, parent)
{
    setFormat(Qt3DRender::QAbstractTexture::RGB32U);
    setWidth(2048);
    setHeight(2048);
    setDepth(1);
}

TextureAtlas::~TextureAtlas()
{

}

QOpenGLTexture::PixelFormat TextureAtlas::pixelFormat() const
{
    return m_pixelFormat;
}

void TextureAtlas::setPixelFormat(QOpenGLTexture::PixelFormat fmt)
{
    m_pixelFormat = fmt;
}

TextureAtlas::TextureId TextureAtlas::addImage(const QImage &image, int padding)
{
    if (!m_allocator) {
        Q_ASSERT(m_data.isNull());

        m_allocator.reset(new AreaAllocator(QSize(width(), height())));
        m_data = TextureAtlasDataPtr::create(width(), height(), image.format());
    }

    const QSize allocSz = image.size() + QSize(2 * padding, 2 * padding);

    // try to allocate space within image space
    const QRect alloc = m_allocator->allocate(allocSz);
    if (alloc.isEmpty())
        return InvalidTexture;

    const QRect imgRect = alloc.adjusted(padding, padding, -padding, -padding);
    AtlasTexture tex;
    tex.position = imgRect;
    tex.padding = padding;

    // store texture
    TextureId id = m_currId++;
    m_textures[id] = tex;
    m_data->addImage(tex, image);

    // update data functor
    m_currGen++;
    dataGenerator() = TextureAtlasGeneratorPtr::create(this);
    //setDataFunctor(TextureAtlasGeneratorPtr::create(this));

    return id;
}

void TextureAtlas::removeImage(TextureAtlas::TextureId id)
{
    auto it = m_textures.find(id);
    if (it != m_textures.end()) {
        QRect imgRect = it->position;
        imgRect.adjust(-it->padding, -it->padding, 2*it->padding, 2*it->padding);

        if (m_allocator)
            m_allocator->deallocate(imgRect);
        m_textures.erase(it);
    }
}

int TextureAtlas::imageCount() const
{
    return m_textures.size();
}

bool TextureAtlas::hasImage(TextureAtlas::TextureId id) const
{
    return m_textures.contains(id);
}

QRect TextureAtlas::imagePosition(TextureAtlas::TextureId id) const
{
    const auto it = m_textures.find(id);
    return (it != m_textures.cend()) ? it->position : QRect();
}

QRectF TextureAtlas::imageTexCoords(TextureAtlas::TextureId id) const
{
    const auto it = m_textures.find(id);
    if (it != m_textures.cend()) {
        const float w = m_data->width();
        const float h = m_data->height();
        return QRectF(static_cast<float>(it->position.x()) / w,
                      static_cast<float>(it->position.y()) / h,
                      static_cast<float>(it->position.width()) / w,
                      static_cast<float>(it->position.height()) / h);
    }
    return QRectF();
}

int TextureAtlas::imagePadding(TextureAtlas::TextureId id) const
{
    const auto it = m_textures.find(id);
    return (it != m_textures.cend()) ? it->padding : -1;
}

TextureAtlasData::TextureAtlasData(int w, int h, QImage::Format fmt)
    : m_image(w, h, fmt)
{

}

TextureAtlasData::~TextureAtlasData()
{

}

void TextureAtlasData::addImage(const AtlasTexture &texture, const QImage &image)
{
    QMutexLocker lock(&m_mutex);

    Update update;
    update.textureInfo = texture;
    update.image = image;
    m_updates << update;
}

QByteArray TextureAtlasData::createUpdatedImageData()
{
    m_mutex.lock();
    const QVector<Update> updates = std::move(m_updates);
    m_mutex.unlock();

    // copy sub-images into the actual texture image
    for (const Update &update : updates) {
        const QImage &image = update.image;

        const int padding = update.textureInfo.padding;
        const QRect imgRect = update.textureInfo.position;
        const QRect alloc = imgRect.adjusted(-padding, -padding, padding, padding);

        // bytes per pixel
        if (image.depth() != m_image.depth()) {
            qWarning() << "[QTextureAtlas] Image depth does not match. Original =" << m_image.depth() << ", Sub-Image =" << image.depth();
            continue;
        }
        int bpp = image.depth() / 8;

        // copy image contents into texture image
        // use image border pixels to fill the padding region
        for (int y = alloc.top(); y <= alloc.bottom(); y++) {
            const int ySrc = qBound(0, y - imgRect.top(), image.height()-1);

            const uchar *srcLine = image.scanLine(ySrc);
            const uchar *srcLastPx = &srcLine[bpp * (image.width()-1)];

            uchar *dstLine = m_image.scanLine(y);

            uchar *dstPadL = &dstLine[bpp * alloc.left()];
            uchar *dstPadR = &dstLine[bpp * imgRect.right()];
            uchar *dstImg  = &dstLine[bpp * imgRect.left()];

            // copy left and right padding pixels
            for (int pad = 0; pad < padding; pad++) {
                for (int px = 0; px < bpp; px++) {
                    dstPadL[bpp * pad + px] = srcLine[px];
                    dstPadR[bpp * pad + px] = srcLastPx[px];
                }
            }

            // copy image scanline
            memcpy(dstImg, srcLine, bpp * imgRect.width());
        }
    }

    return QByteArray(reinterpret_cast<const char*>(m_image.constBits()), m_image.byteCount());
}

TextureAtlasGenerator::TextureAtlasGenerator(const TextureAtlas *texAtlas)
    : m_data(texAtlas->data())
    , m_format(texAtlas->format())
    , m_pixelFormat(texAtlas->pixelFormat())
    , m_generation(texAtlas->currentGenerator())
    , m_atlasId(texAtlas->id())
{
}

TextureAtlasGenerator::~TextureAtlasGenerator()
{
}

Qt3DRender::QTextureDataPtr TextureAtlasGenerator::operator()()
{
    Qt3DRender::QTextureImageDataPtr texImage = Qt3DRender::QTextureImageDataPtr::create();
    texImage->setTarget(QOpenGLTexture::Target2D);
    texImage->setWidth(m_data->width());
    texImage->setHeight(m_data->height());
    texImage->setDepth(1);
    texImage->setFaces(1);
    texImage->setLayers(1);
    texImage->setMipLevels(1);
    texImage->setFormat(static_cast<QOpenGLTexture::TextureFormat>(m_format));
    texImage->setPixelFormat(m_pixelFormat);
    texImage->setPixelType(QOpenGLTexture::UInt8);

    const QByteArray bytes = m_data->createUpdatedImageData();
    texImage->setData(bytes, 1);

    Qt3DRender::QTextureDataPtr generatedData = Qt3DRender::QTextureDataPtr::create();
    generatedData->setTarget(Qt3DRender::QAbstractTexture::Target2D);
    generatedData->setFormat(m_format);
    generatedData->setWidth(m_data->width());
    generatedData->setHeight(m_data->height());
    generatedData->setDepth(1);
    generatedData->setLayers(1);
    generatedData->addImageData(texImage);

    return generatedData;
}

bool TextureAtlasGenerator::operator==(const Qt3DRender::QTextureGenerator &other) const
{
    const TextureAtlasGenerator *otherFunctor = functor_cast<TextureAtlasGenerator>(&other);
    return (otherFunctor != nullptr
            && otherFunctor->m_data == m_data
            && otherFunctor->m_atlasId == m_atlasId
            && otherFunctor->m_generation == m_generation);
}
