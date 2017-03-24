#include "mahjongtilematerial.h"
#include <Qt3DRender/qfilterkey.h>
#include <Qt3DRender/qmaterial.h>
#include <Qt3DRender/qeffect.h>
#include <Qt3DRender/qtexture.h>
#include <Qt3DRender/qtechnique.h>
#include <Qt3DRender/qshaderprogram.h>
#include <Qt3DRender/qparameter.h>
#include <Qt3DRender/qrenderpass.h>
#include <Qt3DRender/qgraphicsapifilter.h>
#include <QUrl>
#include <QVector3D>
#include <QVector4D>

using namespace Qt3DRender;

MahjongTileMaterial::MahjongTileMaterial(Qt3DCore::QNode *parent)
    : QMaterial (parent)
    , m_mahjongTileEffect(new QEffect())
    , m_selectedParameter(new QParameter(QStringLiteral("isSelected"), false))
//    , m_tileDiffuseParameter(new QParameter(QStringLiteral("tileUV"), QVector2D(0.0f, 0.0f)))
//    , m_tileFaceParameter(new QParameter(QStringLiteral("tilefaceUV"), QVector2D(0.0f, 0.0f)))
    , m_diffuseMapGL3Technique(new QTechnique())
    , m_diffuseMapGL2Technique(new QTechnique())
    , m_diffuseMapES2Technique(new QTechnique())
    , m_diffuseMapGL3RenderPass(new QRenderPass())
    , m_diffuseMapGL2RenderPass(new QRenderPass())
    , m_diffuseMapES2RenderPass(new QRenderPass())
    , m_diffuseMapGL3Shader(new QShaderProgram())
    , m_diffuseMapGL2ES2Shader(new QShaderProgram())
    , m_filterKey(new QFilterKey())
{

}

MahjongTileMaterial::~MahjongTileMaterial()
{

}
