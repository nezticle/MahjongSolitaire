#ifndef MAHJONGTILEMATERIAL_H
#define MAHJONGTILEMATERIAL_H

#include <Qt3DRender/QMaterial>

namespace Qt3DRender {
    class QTexture2DArray;
    class QTexture2D;
    class QParameter;
    class QEffect;
    class QTechnique;
    class QRenderPass;
    class QShaderProgram;
    class QFilterKey;
}

class MahjongTileMaterial : public Qt3DRender::QMaterial
{
    Q_OBJECT
    Q_PROPERTY(Qt3DRender::QAbstractTexture *baseColor READ baseColor WRITE setBaseColor NOTIFY baseColorChanged)
    Q_PROPERTY(Qt3DRender::QAbstractTexture *metalness READ metalness WRITE setMetalness NOTIFY metalnessChanged)
    Q_PROPERTY(Qt3DRender::QAbstractTexture *roughness READ roughness WRITE setRoughness NOTIFY roughnessChanged)
    Q_PROPERTY(Qt3DRender::QAbstractTexture *ambientOcclusion READ ambientOcclusion WRITE setAmbientOcclusion NOTIFY ambientOcclusionChanged)
    Q_PROPERTY(Qt3DRender::QAbstractTexture *normal READ normal WRITE setNormal NOTIFY normalChanged)


public:
    MahjongTileMaterial(Qt3DCore::QNode *parent = nullptr);

    Qt3DRender::QAbstractTexture *baseColor() const;
    Qt3DRender::QAbstractTexture *metalness() const;
    Qt3DRender::QAbstractTexture *roughness() const;
    Qt3DRender::QAbstractTexture *ambientOcclusion() const;
    Qt3DRender::QAbstractTexture *normal() const;

public slots:
    void setBaseColor(Qt3DRender::QAbstractTexture *baseColor);
    void setMetalness(Qt3DRender::QAbstractTexture *metalness);
    void setRoughness(Qt3DRender::QAbstractTexture *roughness);
    void setAmbientOcclusion(Qt3DRender::QAbstractTexture *ambientOcclusion);
    void setNormal(Qt3DRender::QAbstractTexture *normal);

signals:
    void baseColorChanged(Qt3DRender::QAbstractTexture *baseColor);
    void metalnessChanged(Qt3DRender::QAbstractTexture *metalness);
    void roughnessChanged(Qt3DRender::QAbstractTexture *roughness);
    void ambientOcclusionChanged(Qt3DRender::QAbstractTexture *ambientOcclusion);
    void normalChanged(Qt3DRender::QAbstractTexture *normal);
private:
    Qt3DRender::QTexture2DArray *m_baseColorTexture;
    Qt3DRender::QTexture2DArray *m_metalnessTexture;
    Qt3DRender::QTexture2DArray *m_roughnessTexture;
    Qt3DRender::QTexture2D *m_ambientOcclusionTexture;
    Qt3DRender::QTexture2D *m_normalTexture;
    Qt3DRender::QTexture2D *m_environmentIrradianceTexture;
    Qt3DRender::QTexture2D *m_environmentSpecularTexture;
    Qt3DRender::QParameter *m_baseColorParameter;
    Qt3DRender::QParameter *m_metalnessParameter;
    Qt3DRender::QParameter *m_roughnessParameter;
    Qt3DRender::QParameter *m_ambientOcclusionParameter;
    Qt3DRender::QParameter *m_normalParameter;
    Qt3DRender::QParameter *m_environmentIrradianceParameter;
    Qt3DRender::QParameter *m_environmentSpecularParameter;
    Qt3DRender::QEffect *m_metalRoughEffect;
    Qt3DRender::QTechnique *m_metalRoughGL3Technique;
    Qt3DRender::QRenderPass *m_metalRoughGL3RenderPass;
    Qt3DRender::QShaderProgram *m_metalRoughGL3Shader;
    Qt3DRender::QFilterKey *m_filterKey;
};

#endif // MAHJONGTILEMATERIAL_H
