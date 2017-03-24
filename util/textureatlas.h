#ifndef TEXTUREATLAS_H
#define TEXTUREATLAS_H

#include <Qt3DRender/qabstracttexture.h>
#include <Qt3DRender/qtexturegenerator.h>
#include <QtCore/QSharedPointer>

#include "areaallocator.h"

// Used to store texture info within atlas
struct AtlasTexture
{
    QRect position;
    int padding = 0;
};

class TextureAtlasData
{
public:
    TextureAtlasData(int w, int h, QImage::Format fmt);
    ~TextureAtlasData();

    int width() const { return m_image.width(); }
    int height() const { return m_image.height(); }

    void addImage(const AtlasTexture &texture, const QImage &image);
    QByteArray createUpdatedImageData();

private:
    struct Update {
        AtlasTexture textureInfo;
        QImage image;
    };

    QMutex m_mutex;
    QImage m_image;
    QVector<Update> m_updates;
};

typedef QSharedPointer<TextureAtlasData> TextureAtlasDataPtr;

class TextureAtlas;
class TextureAtlasGenerator : public Qt3DRender::QTextureGenerator
{
public:
    TextureAtlasGenerator(const TextureAtlas *texAtlas);
    ~TextureAtlasGenerator();
    Qt3DRender::QTextureDataPtr operator()() Q_DECL_OVERRIDE;
    bool operator==(const QTextureGenerator &other) const Q_DECL_OVERRIDE;

    QT3D_FUNCTOR(TextureAtlasGenerator)

private:
    TextureAtlasDataPtr m_data;
    Qt3DRender::QAbstractTexture::TextureFormat m_format;
    QOpenGLTexture::PixelFormat m_pixelFormat;
    int m_generation;
    Qt3DCore::QNodeId m_atlasId;
};
typedef QSharedPointer<TextureAtlasGenerator> TextureAtlasGeneratorPtr;

class TextureAtlas : public Qt3DRender::QAbstractTexture
{
    Q_OBJECT
public:
    typedef int TextureId;
    static Q_CONSTEXPR TextureId InvalidTexture = -1;

    TextureAtlas(Qt3DCore::QNode *parent = nullptr);
    ~TextureAtlas();

    QOpenGLTexture::PixelFormat pixelFormat() const;
    void setPixelFormat(QOpenGLTexture::PixelFormat fmt);

    TextureId addImage(const QImage &image, int padding);
    void removeImage(TextureId id);

    int imageCount() const;

    bool hasImage(TextureId id) const;
    QRect imagePosition(TextureId id) const;
    QRectF imageTexCoords(TextureId id) const;
    int imagePadding(TextureId id) const;

    TextureAtlasDataPtr data() const { return m_data; }
    int currentGenerator() const { return m_currGen; }

private:
    TextureAtlas::TextureId m_currId = 1;  // IDs for new sub-textures
    int m_currGen = 0;

    TextureAtlasDataPtr m_data;
    QScopedPointer<AreaAllocator> m_allocator;
    QOpenGLTexture::PixelFormat m_pixelFormat;
    QHash<TextureAtlas::TextureId, AtlasTexture> m_textures;

};

#endif // TEXTUREATLAS_H
