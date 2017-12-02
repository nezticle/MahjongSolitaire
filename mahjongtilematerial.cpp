#include "mahjongtilematerial.h"

#include <Qt3DRender/QFilterKey>
#include <Qt3DRender/QEffect>
#include <Qt3DRender/QAbstractTexture>
#include <Qt3DRender/QTexture>
#include <Qt3DRender/QTechnique>
#include <Qt3DRender/QShaderProgram>
#include <Qt3DRender/QParameter>
#include <Qt3DRender/QRenderPass>
#include <Qt3DRender/QGraphicsApiFilter>

MahjongTileMaterial::MahjongTileMaterial(Qt3DCore::QNode *parent)
    : QMaterial(parent)
    , m_baseColorTexture(new Qt3DRender::QTexture2DArray())
    , m_metalnessTexture(new Qt3DRender::QTexture2DArray())
    , m_roughnessTexture(new Qt3DRender::QTexture2DArray())
    , m_ambientOcclusionTexture(new Qt3DRender::QTexture2D())
    , m_normalTexture(new Qt3DRender::QTexture2D())
    , m_environmentIrradianceTexture(new Qt3DRender::QTexture2D())
    , m_environmentSpecularTexture(new Qt3DRender::QTexture2D())
    , m_baseColorParameter(new Qt3DRender::QParameter(QStringLiteral("baseColorMap"), m_baseColorTexture))
    , m_metalnessParameter(new Qt3DRender::QParameter(QStringLiteral("metalnessMap"), m_metalnessTexture))
    , m_roughnessParameter(new Qt3DRender::QParameter(QStringLiteral("roughnessMap"), m_roughnessTexture))
    , m_ambientOcclusionParameter(new Qt3DRender::QParameter(QStringLiteral("ambientOcclusionMap"), m_ambientOcclusionTexture))
    , m_normalParameter(new Qt3DRender::QParameter(QStringLiteral("normalMap"), m_normalTexture))
    , m_environmentIrradianceParameter(new Qt3DRender::QParameter(QStringLiteral("envLight.irradiance"), m_environmentIrradianceTexture))
    , m_environmentSpecularParameter(new Qt3DRender::QParameter(QStringLiteral("envLight.specular"), m_environmentSpecularTexture))
    , m_metalRoughEffect(new Qt3DRender::QEffect())
    , m_metalRoughGL3Technique(new Qt3DRender::QTechnique())
    , m_metalRoughGL3RenderPass(new Qt3DRender::QRenderPass())
    , m_metalRoughGL3Shader(new Qt3DRender::QShaderProgram())
    , m_filterKey(new Qt3DRender::QFilterKey)
{
    m_baseColorTexture->setMagnificationFilter(Qt3DRender::QAbstractTexture::Linear);
    m_baseColorTexture->setMinificationFilter(Qt3DRender::QAbstractTexture::LinearMipMapLinear);
    m_baseColorTexture->setWrapMode(Qt3DRender::QTextureWrapMode(Qt3DRender::QTextureWrapMode::Repeat));
    m_baseColorTexture->setGenerateMipMaps(true);
    m_baseColorTexture->setMaximumAnisotropy(16.0f);

    m_metalnessTexture->setMagnificationFilter(Qt3DRender::QAbstractTexture::Linear);
    m_metalnessTexture->setMinificationFilter(Qt3DRender::QAbstractTexture::LinearMipMapLinear);
    m_metalnessTexture->setWrapMode(Qt3DRender::QTextureWrapMode(Qt3DRender::QTextureWrapMode::Repeat));
    m_metalnessTexture->setGenerateMipMaps(true);
    m_metalnessTexture->setMaximumAnisotropy(16.0f);

    m_roughnessTexture->setMagnificationFilter(Qt3DRender::QAbstractTexture::Linear);
    m_roughnessTexture->setMinificationFilter(Qt3DRender::QAbstractTexture::LinearMipMapLinear);
    m_roughnessTexture->setWrapMode(Qt3DRender::QTextureWrapMode(Qt3DRender::QTextureWrapMode::Repeat));
    m_roughnessTexture->setGenerateMipMaps(true);
    m_roughnessTexture->setMaximumAnisotropy(16.0f);

    m_ambientOcclusionTexture->setMagnificationFilter(Qt3DRender::QAbstractTexture::Linear);
    m_ambientOcclusionTexture->setMinificationFilter(Qt3DRender::QAbstractTexture::LinearMipMapLinear);
    m_ambientOcclusionTexture->setWrapMode(Qt3DRender::QTextureWrapMode(Qt3DRender::QTextureWrapMode::Repeat));
    m_ambientOcclusionTexture->setGenerateMipMaps(true);
    m_ambientOcclusionTexture->setMaximumAnisotropy(16.0f);

    m_normalTexture->setMagnificationFilter(Qt3DRender::QAbstractTexture::Linear);
    m_normalTexture->setMinificationFilter(Qt3DRender::QAbstractTexture::LinearMipMapLinear);
    m_normalTexture->setWrapMode(Qt3DRender::QTextureWrapMode(Qt3DRender::QTextureWrapMode::Repeat));
    m_normalTexture->setGenerateMipMaps(true);
    m_normalTexture->setMaximumAnisotropy(16.0f);

    m_environmentIrradianceTexture->setMagnificationFilter(Qt3DRender::QAbstractTexture::Linear);
    m_environmentIrradianceTexture->setMinificationFilter(Qt3DRender::QAbstractTexture::LinearMipMapLinear);
    m_environmentIrradianceTexture->setWrapMode(Qt3DRender::QTextureWrapMode(Qt3DRender::QTextureWrapMode::Repeat));
    m_environmentIrradianceTexture->setGenerateMipMaps(true);
    m_environmentIrradianceTexture->setMaximumAnisotropy(16.0f);

    m_environmentSpecularTexture->setMagnificationFilter(Qt3DRender::QAbstractTexture::Linear);
    m_environmentSpecularTexture->setMinificationFilter(Qt3DRender::QAbstractTexture::LinearMipMapLinear);
    m_environmentSpecularTexture->setWrapMode(Qt3DRender::QTextureWrapMode(Qt3DRender::QTextureWrapMode::Repeat));
    m_environmentSpecularTexture->setGenerateMipMaps(true);
    m_environmentSpecularTexture->setMaximumAnisotropy(16.0f);

    connect(m_baseColorParameter, &Qt3DRender::QParameter::valueChanged, [=] (const QVariant &var) {
        emit baseColorChanged(var.value<Qt3DRender::QAbstractTexture *>());
    });
    connect(m_metalnessParameter, &Qt3DRender::QParameter::valueChanged, [=] (const QVariant &var) {
        emit metalnessChanged(var.value<Qt3DRender::QAbstractTexture *>());
    });
    connect(m_roughnessParameter, &Qt3DRender::QParameter::valueChanged, [=] (const QVariant &var) {
        emit roughnessChanged(var.value<Qt3DRender::QAbstractTexture *>());
    });
    connect(m_ambientOcclusionParameter, &Qt3DRender::QParameter::valueChanged, [=] (const QVariant &var) {
        emit ambientOcclusionChanged(var.value<Qt3DRender::QAbstractTexture *>());
    });
    connect(m_normalParameter, &Qt3DRender::QParameter::valueChanged, [=] (const QVariant &var) {
        emit normalChanged(var.value<Qt3DRender::QAbstractTexture *>());
    });

    m_metalRoughGL3Shader->setVertexShaderCode(Qt3DRender::QShaderProgram::loadSource(QUrl(QStringLiteral("qrc:/shaders/mahjongtile.vert"))));
    m_metalRoughGL3Shader->setFragmentShaderCode(Qt3DRender::QShaderProgram::loadSource(QUrl(QStringLiteral("qrc:/shaders/mahjongtile.frag"))));

    m_metalRoughGL3Technique->graphicsApiFilter()->setApi(Qt3DRender::QGraphicsApiFilter::OpenGL);
    m_metalRoughGL3Technique->graphicsApiFilter()->setMajorVersion(3);
    m_metalRoughGL3Technique->graphicsApiFilter()->setMinorVersion(1);
    m_metalRoughGL3Technique->graphicsApiFilter()->setProfile(Qt3DRender::QGraphicsApiFilter::CoreProfile);

    m_filterKey->setParent(this);
    m_filterKey->setName(QStringLiteral("renderingStyle"));
    m_filterKey->setValue(QStringLiteral("forward"));

    m_metalRoughGL3Technique->addFilterKey(m_filterKey);
    m_metalRoughGL3RenderPass->setShaderProgram(m_metalRoughGL3Shader);
    m_metalRoughGL3Technique->addRenderPass(m_metalRoughGL3RenderPass);
    m_metalRoughEffect->addTechnique(m_metalRoughGL3Technique);

    m_metalRoughEffect->addParameter(m_baseColorParameter);
    m_metalRoughEffect->addParameter(m_metalnessParameter);
    m_metalRoughEffect->addParameter(m_roughnessParameter);
    m_metalRoughEffect->addParameter(m_ambientOcclusionParameter);
    m_metalRoughEffect->addParameter(m_normalParameter);
    m_metalRoughEffect->addParameter(m_environmentIrradianceParameter);
    m_metalRoughEffect->addParameter(m_environmentSpecularParameter);

    setEffect(m_metalRoughEffect);
}

Qt3DRender::QAbstractTexture *MahjongTileMaterial::baseColor() const
{
    return m_baseColorParameter->value().value<Qt3DRender::QAbstractTexture *>();
}

Qt3DRender::QAbstractTexture *MahjongTileMaterial::metalness() const
{
    return m_metalnessParameter->value().value<Qt3DRender::QAbstractTexture *>();
}

Qt3DRender::QAbstractTexture *MahjongTileMaterial::roughness() const
{
    return m_roughnessParameter->value().value<Qt3DRender::QAbstractTexture *>();
}

Qt3DRender::QAbstractTexture *MahjongTileMaterial::ambientOcclusion() const
{
    return m_ambientOcclusionParameter->value().value<Qt3DRender::QAbstractTexture *>();
}

Qt3DRender::QAbstractTexture *MahjongTileMaterial::normal() const
{
    return m_normalParameter->value().value<Qt3DRender::QAbstractTexture *>();
}

void MahjongTileMaterial::setBaseColor(Qt3DRender::QAbstractTexture *baseColor)
{
    m_baseColorParameter->setValue(QVariant::fromValue(baseColor));
}

void MahjongTileMaterial::setMetalness(Qt3DRender::QAbstractTexture *metalness)
{
    m_metalnessParameter->setValue(QVariant::fromValue(metalness));
}

void MahjongTileMaterial::setRoughness(Qt3DRender::QAbstractTexture *roughness)
{
    m_roughnessParameter->setValue(QVariant::fromValue(roughness));
}

void MahjongTileMaterial::setAmbientOcclusion(Qt3DRender::QAbstractTexture *ambientOcclusion)
{
    m_ambientOcclusionParameter->setValue(QVariant::fromValue(ambientOcclusion));
}

void MahjongTileMaterial::setNormal(Qt3DRender::QAbstractTexture *normal)
{
    m_normalParameter->setValue(QVariant::fromValue(normal));
}
