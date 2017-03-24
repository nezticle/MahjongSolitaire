#ifndef MAHJONGTILEMATERIAL_H
#define MAHJONGTILEMATERIAL_H

#include <Qt3DRender/QMaterial>

namespace Qt3DRender {

class QFilterKey;
class QEffect;
class QAbstractTexture;
class QTechnique;
class QParameter;
class QShaderProgram;
class QRenderPass;

} // namespace Qt3DRender

class MahjongTileMaterial : public Qt3DRender::QMaterial
{
    Q_OBJECT
public:
    MahjongTileMaterial(Qt3DCore::QNode *parent = nullptr);
    ~MahjongTileMaterial();

private:
    Qt3DRender::QEffect *m_mahjongTileEffect;
    Qt3DRender::QAbstractTexture *m_diffuseTexture;
    Qt3DRender::QParameter *m_selectedParameter;
    Qt3DRender::QParameter *m_tileDiffuseParameter;
    Qt3DRender::QParameter *m_tileFaceParameter;
    Qt3DRender::QTechnique *m_diffuseMapGL3Technique;
    Qt3DRender::QTechnique *m_diffuseMapGL2Technique;
    Qt3DRender::QTechnique *m_diffuseMapES2Technique;
    Qt3DRender::QRenderPass *m_diffuseMapGL3RenderPass;
    Qt3DRender::QRenderPass *m_diffuseMapGL2RenderPass;
    Qt3DRender::QRenderPass *m_diffuseMapES2RenderPass;
    Qt3DRender::QShaderProgram *m_diffuseMapGL3Shader;
    Qt3DRender::QShaderProgram *m_diffuseMapGL2ES2Shader;
    Qt3DRender::QFilterKey *m_filterKey;
};

#endif // MAHJONGTILEMATERIAL_H
