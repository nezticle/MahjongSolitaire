#include "mahjonggamescene.h"

#include <Qt3DCore/QEntity>
#include <Qt3DCore/QAspectEngine>
#include <Qt3DCore/QCamera>
#include <Qt3DCore/QTransform>
#include <Qt3DCore/QTranslateTransform>

#include <Qt3DRenderer/QRenderAspect>
#include <Qt3DRenderer/QForwardRenderer>
#include <Qt3DRenderer/QFrameGraph>
#include <Qt3DRenderer/QTextureImage>
#include <Qt3DRenderer/QMesh>
#include <Qt3DRenderer/QDiffuseMapMaterial>
#include <Qt3DRenderer/QTextureImage>

#include "tableentity.h"
#include "mahjongboard.h"

MahjongGameScene::MahjongGameScene(QObject *parent)
    : QObject(parent)
    , m_rootEntity(new Qt3D::QEntity())
    , m_viewportSize(QSize(800,600))
{
    // Scene Camera
    m_camera = new Qt3D::QCamera(m_rootEntity);
    m_camera->setProjectionType(Qt3D::QCameraLens::PerspectiveProjection);
    m_camera->setAspectRatio((float)m_viewportSize.width() / (float)m_viewportSize.height());
    m_camera->setUpVector(QVector3D(0.0f, 1.0f, 0.0f));
    m_camera->setViewCenter(QVector3D(0.0f, 0.0f, 0.0f));
    m_camera->setPosition(QVector3D(0.0f, -15.f, 25.0f));

    // Forward Renderer FrameGraph
    Qt3D::QFrameGraph *frameGraphComponent = new Qt3D::QFrameGraph(m_rootEntity);
    Qt3D::QForwardRenderer *forwardRenderer = new Qt3D::QForwardRenderer();
    forwardRenderer->setCamera(m_camera);
    forwardRenderer->setClearColor(QColor(Qt::black));
    frameGraphComponent->setActiveFrameGraph(forwardRenderer);
    m_rootEntity->addComponent(frameGraphComponent);

    TableEntity *tableSurface = new TableEntity(m_rootEntity);
    tableSurface->setX(0.0f);
    tableSurface->setY(0.0f);
    tableSurface->setZ(0.0f);
    tableSurface->setScale(13);

    m_mahjongBoard = new MahjongBoard(tableSurface);
}

MahjongGameScene::~MahjongGameScene()
{

}

Qt3D::QEntity *MahjongGameScene::rootEntity() const
{
    return m_rootEntity;
}

QSize MahjongGameScene::viewportSize() const
{
    return m_viewportSize;
}

void MahjongGameScene::setViewportSize(QSize viewportSize)
{
    if (m_viewportSize == viewportSize)
        return;

    m_viewportSize = viewportSize;
    if (m_camera != Q_NULLPTR)
        m_camera->setAspectRatio((float)m_viewportSize.width() / (float)m_viewportSize.height());
    emit viewportSizeChanged(viewportSize);
}

void MahjongGameScene::newGame()
{
    m_mahjongBoard->newGame();
}

