#include "diffusealphamaterial.h"

#include <QtCore/QUrl>
#include <QtGui/QVector3D>
#include <QtGui/QVector4D>

#include <Qt3DRenderer/QEffect>
#include <Qt3DRenderer/QTechnique>
#include <Qt3DRenderer/QShaderProgram>
#include <Qt3DRenderer/QParameter>
#include <Qt3DRenderer/QRenderPass>
#include <Qt3DRenderer/QOpenGLFilter>

#include <Qt3DRenderer/QCullFace>
#include <Qt3DRenderer/QDepthTest>
#include <Qt3DRenderer/QBlendEquation>
#include <Qt3DRenderer/QBlendStateSeparate>

DiffuseAlphaMaterial::DiffuseAlphaMaterial(QNode *parent)
    : QMaterial(parent)
    , m_diffuse(QColor(Qt::white))
    , m_diffuseAlphaEffect(new Qt3D::QEffect())
    , m_diffuseParameter(new Qt3D::QParameter(QStringLiteral("diffuseColor"), QColor(Qt::white)))
    , m_lightPositionParameter(new Qt3D::QParameter(QStringLiteral("lightPosition"), QVector4D(1.0f, 1.0f, 0.0f, 1.0f)))
    , m_lightIntensityParameter(new Qt3D::QParameter(QStringLiteral("lightIntensity"), QVector3D(1.0f, 1.0f, 1.0f)))
    , m_diffuseAlphaGL3Technique(new Qt3D::QTechnique)
    , m_diffuseAlphaGL2Technique(new Qt3D::QTechnique)
    , m_diffuseAlphaES2Technique(new Qt3D::QTechnique)
    , m_diffuseAlphaGL3RenderPass(new Qt3D::QRenderPass)
    , m_diffuseAlphaGL2RenderPass(new Qt3D::QRenderPass)
    , m_diffuseAlphaES2RenderPass(new Qt3D::QRenderPass)
    , m_diffuseAlphaGL3Shader(new Qt3D::QShaderProgram)
    , m_diffuseAlphaGL2ES2Shader(new Qt3D::QShaderProgram)
{
    m_diffuseAlphaGL3Shader->setVertexShaderCode(Qt3D::QShaderProgram::loadSource(QUrl(QStringLiteral("qrc:/shaders/wireframe_gl3.vert"))));
    m_diffuseAlphaGL3Shader->setFragmentShaderCode(Qt3D::QShaderProgram::loadSource(QUrl(QStringLiteral("qrc:/shaders/wireframe_gl3.frag"))));
    m_diffuseAlphaGL2ES2Shader->setVertexShaderCode(Qt3D::QShaderProgram::loadSource(QUrl(QStringLiteral("qrc:/shaders/wireframe_es2.vert"))));
    m_diffuseAlphaGL2ES2Shader->setFragmentShaderCode(Qt3D::QShaderProgram::loadSource(QUrl(QStringLiteral("qrc:/shaders/wireframe_es2.frag"))));

    m_diffuseAlphaGL3Technique->openGLFilter()->setApi(Qt3D::QOpenGLFilter::Desktop);
    m_diffuseAlphaGL3Technique->openGLFilter()->setMajorVersion(3);
    m_diffuseAlphaGL3Technique->openGLFilter()->setMinorVersion(1);
    m_diffuseAlphaGL3Technique->openGLFilter()->setProfile(Qt3D::QOpenGLFilter::Core);

    m_diffuseAlphaGL2Technique->openGLFilter()->setApi(Qt3D::QOpenGLFilter::Desktop);
    m_diffuseAlphaGL2Technique->openGLFilter()->setMajorVersion(2);
    m_diffuseAlphaGL2Technique->openGLFilter()->setMinorVersion(0);
    m_diffuseAlphaGL2Technique->openGLFilter()->setProfile(Qt3D::QOpenGLFilter::None);

    m_diffuseAlphaES2Technique->openGLFilter()->setApi(Qt3D::QOpenGLFilter::ES);
    m_diffuseAlphaES2Technique->openGLFilter()->setMajorVersion(2);
    m_diffuseAlphaES2Technique->openGLFilter()->setMinorVersion(0);
    m_diffuseAlphaES2Technique->openGLFilter()->setProfile(Qt3D::QOpenGLFilter::None);

    m_diffuseAlphaGL3RenderPass->setShaderProgram(m_diffuseAlphaGL3Shader);
    m_diffuseAlphaGL2RenderPass->setShaderProgram(m_diffuseAlphaGL2ES2Shader);
    m_diffuseAlphaES2RenderPass->setShaderProgram(m_diffuseAlphaGL2ES2Shader);

    Qt3D::QCullFace *cullFace = new Qt3D::QCullFace;
    cullFace->setMode(Qt3D::QCullFace::Back);
    m_diffuseAlphaGL3RenderPass->addRenderState(cullFace);
    m_diffuseAlphaGL2RenderPass->addRenderState(cullFace);
    m_diffuseAlphaES2RenderPass->addRenderState(cullFace);

    Qt3D::QDepthTest *depthTest = new Qt3D::QDepthTest;
    depthTest->setFunc(Qt3D::QDepthTest::Less);
    m_diffuseAlphaGL3RenderPass->addRenderState(depthTest);
    m_diffuseAlphaGL2RenderPass->addRenderState(depthTest);
    m_diffuseAlphaES2RenderPass->addRenderState(depthTest);

    Qt3D::QBlendEquation *blendEquation = new Qt3D::QBlendEquation;
    blendEquation->setMode(Qt3D::QBlendEquation::FuncAdd);
    m_diffuseAlphaGL3RenderPass->addRenderState(blendEquation);
    m_diffuseAlphaGL2RenderPass->addRenderState(blendEquation);
    m_diffuseAlphaES2RenderPass->addRenderState(blendEquation);

    Qt3D::QBlendStateSeparate *blendSeperate = new Qt3D::QBlendStateSeparate;
    blendSeperate->setSrcRGB(Qt3D::QBlendState::One);
    blendSeperate->setDstRGB(Qt3D::QBlendState::One);
    blendSeperate->setSrcAlpha(Qt3D::QBlendState::OneMinusSrcAlpha);
    blendSeperate->setDstAlpha(Qt3D::QBlendState::OneMinusSrcAlpha);
    m_diffuseAlphaGL3RenderPass->addRenderState(blendSeperate);
    m_diffuseAlphaGL2RenderPass->addRenderState(blendSeperate);
    m_diffuseAlphaES2RenderPass->addRenderState(blendSeperate);

    m_diffuseAlphaGL3Technique->addPass(m_diffuseAlphaGL3RenderPass);
    m_diffuseAlphaGL2Technique->addPass(m_diffuseAlphaGL2RenderPass);
    m_diffuseAlphaES2Technique->addPass(m_diffuseAlphaES2RenderPass);

    m_diffuseAlphaEffect->addTechnique(m_diffuseAlphaGL3Technique);
    m_diffuseAlphaEffect->addTechnique(m_diffuseAlphaGL2Technique);
    m_diffuseAlphaEffect->addTechnique(m_diffuseAlphaES2Technique);

    m_diffuseAlphaEffect->addParameter(m_diffuseParameter);
    m_diffuseAlphaEffect->addParameter(m_lightPositionParameter);
    m_diffuseAlphaEffect->addParameter(m_lightIntensityParameter);

    setEffect(m_diffuseAlphaEffect);
}

QColor DiffuseAlphaMaterial::diffuse() const
{
    return m_diffuse;
}

void DiffuseAlphaMaterial::setDiffuse(QColor diffuse)
{
    if (m_diffuse == diffuse)
        return;

    m_diffuse = diffuse;
    m_diffuseParameter->setValue(m_diffuse);
    emit diffuseChanged(diffuse);
}

