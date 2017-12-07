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
    Q_PROPERTY(Qt3DRender::QAbstractTexture *roughMetalHeightAo READ roughMetalHeightAo WRITE setRoughMetalHeightAo NOTIFY roughMetalHeightAoChanged)
    Q_PROPERTY(Qt3DRender::QAbstractTexture *normal READ normal WRITE setNormal NOTIFY normalChanged)

public:
    MahjongTileMaterial(Qt3DCore::QNode *parent = nullptr);

    Qt3DRender::QAbstractTexture *baseColor() const;
    Qt3DRender::QAbstractTexture *normal() const;
    Qt3DRender::QAbstractTexture *roughMetalHeightAo() const;

public slots:
    void setBaseColor(Qt3DRender::QAbstractTexture *baseColor);
    void setNormal(Qt3DRender::QAbstractTexture *normal);  
    void setRoughMetalHeightAo(Qt3DRender::QAbstractTexture * roughMetalHeightAo);

signals:
    void baseColorChanged(Qt3DRender::QAbstractTexture *baseColor);
    void normalChanged(Qt3DRender::QAbstractTexture *normal);
    void roughMetalHeightAoChanged(Qt3DRender::QAbstractTexture * roughMetalHeightAo);

private:
    Qt3DRender::QTexture2D *m_baseColorTexture;
    Qt3DRender::QTexture2D *m_roughMetalHeightAo;
    Qt3DRender::QTexture2D *m_normalTexture;
    Qt3DRender::QTexture2D *m_environmentIrradianceTexture;
    Qt3DRender::QTexture2D *m_environmentSpecularTexture;
    Qt3DRender::QParameter *m_baseColorParameter;
    Qt3DRender::QParameter *m_roughMetalHeightAoParameter;
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
