#include "mahjonggamescene.h"

#include <QtCore/QDebug>

#include <Qt3DCore/QEntity>
#include <Qt3DCore/QAspectEngine>
#include <Qt3DRender/QCamera>

#include <Qt3DRender/QRenderAspect>
#include <Qt3DExtras/QForwardRenderer>
#include <Qt3DRender/QRenderSettings>
#include <Qt3DRender/QTextureImage>
#include <Qt3DRender/QMesh>
#include <Qt3DExtras/QDiffuseMapMaterial>
#include <Qt3DRender/QTextureImage>
#include <Qt3DRender/QDirectionalLight>

#include <Qt3DInput/QInputSettings>

#include "tableentity.h"
#include "mahjongboard.h"

MahjongGameScene::MahjongGameScene(QObject *parent)
    : QObject(parent)
    , m_rootEntity(new Qt3DCore::QEntity())
    , m_viewportSize(QSize(800,600))
{
    // Scene Camera
    m_camera = new Qt3DRender::QCamera(m_rootEntity);
    m_camera->setProjectionType(Qt3DRender::QCameraLens::PerspectiveProjection);
    m_camera->setAspectRatio(static_cast<float>(m_viewportSize.width()) / static_cast<float>(m_viewportSize.height()));
    m_camera->setUpVector(QVector3D(0.0f, 1.0f, 0.0f));
    m_camera->setViewCenter(QVector3D(0.0f, 0.0f, 0.0f));
    m_camera->setPosition(QVector3D(0.0f, -15.0f, 25.0f));
    //m_camera->setPosition(QVector3D(0.0f, 0.0f, 25.0f));

    // Forward Renderer FrameGraph
    Qt3DRender::QRenderSettings *frameGraphComponent = new Qt3DRender::QRenderSettings(m_rootEntity);
    Qt3DExtras::QForwardRenderer *forwardRenderer = new Qt3DExtras::QForwardRenderer();
    forwardRenderer->setCamera(m_camera);
    forwardRenderer->setClearColor(Qt::black);
    frameGraphComponent->setActiveFrameGraph(forwardRenderer);
    m_rootEntity->addComponent(frameGraphComponent);

    auto inputSettings = new Qt3DInput::QInputSettings(m_rootEntity);
    m_rootEntity->addComponent(inputSettings);

    TableEntity *tableSurface = new TableEntity(m_rootEntity);
    tableSurface->setX(0.0f);
    tableSurface->setY(0.0f);
    tableSurface->setZ(0.0f);
    tableSurface->setScale(18);

    m_mahjongBoard = new MahjongBoard(tableSurface);
    m_mahjongBoard->setScale(0.9f);

    // Scene Lighting
    auto *directionLightEntity = new Qt3DCore::QEntity(m_rootEntity);
    auto *directionalLight = new Qt3DRender::QDirectionalLight;
    directionLightEntity->addComponent(directionalLight);
    directionalLight->setWorldDirection(QVector3D(0.1f, 0.5f, -0.5f));
    directionalLight->setIntensity(1);
}

MahjongGameScene::~MahjongGameScene()
{

}

Qt3DCore::QEntity *MahjongGameScene::rootEntity() const
{
    return m_rootEntity;
}

QSize MahjongGameScene::viewportSize() const
{
    return m_viewportSize;
}

Qt3DRender::QCamera *MahjongGameScene::camera() const
{
    return m_camera;
}

void MahjongGameScene::setViewportSize(QSize viewportSize)
{
    if (m_viewportSize == viewportSize)
        return;

    m_viewportSize = viewportSize;
    if (m_camera != Q_NULLPTR)
        m_camera->setAspectRatio(static_cast<float>(m_viewportSize.width()) / static_cast<float>(m_viewportSize.height()));
    emit viewportSizeChanged(viewportSize);
}

void MahjongGameScene::newGame()
{
    m_mahjongBoard->newGame();
}

void MahjongGameScene::processInput(int x, int y)
{
    qDebug() << "Input event at(" << x << "," << y << ")";
}

