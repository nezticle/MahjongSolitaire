#include "mahjonggamescene.h"

#include <QtCore/QDebug>

#include <Qt3DCore/QEntity>
#include <Qt3DCore/QAspectEngine>
#include <Qt3DCore/QCamera>
#include <Qt3DCore/QTransform>
#include <Qt3DCore/QTranslateTransform>

#include <Qt3DRender/QRenderAspect>
#include <Qt3DRender/QForwardRenderer>
#include <Qt3DRender/QFrameGraph>
#include <Qt3DRender/QTextureImage>
#include <Qt3DRender/QMesh>
#include <Qt3DRender/QDiffuseMapMaterial>
#include <Qt3DRender/QTextureImage>

#include "tableentity.h"
#include "mahjongboard.h"

MahjongGameScene::MahjongGameScene(QObject *parent)
    : QObject(parent)
    , m_rootEntity(new Qt3DCore::QEntity())
    , m_viewportSize(QSize(800,600))
{
    // Scene Camera
    m_camera = new Qt3DCore::QCamera(m_rootEntity);
    m_camera->setProjectionType(Qt3DCore::QCameraLens::PerspectiveProjection);
    m_camera->setAspectRatio((float)m_viewportSize.width() / (float)m_viewportSize.height());
    m_camera->setUpVector(QVector3D(0.0f, 1.0f, 0.0f));
    m_camera->setViewCenter(QVector3D(0.0f, 0.0f, 0.0f));
    m_camera->setPosition(QVector3D(0.0f, -15.f, 25.0f));

    // Forward Renderer FrameGraph
    Qt3DRender::QFrameGraph *frameGraphComponent = new Qt3DRender::QFrameGraph(m_rootEntity);
    Qt3DRender::QForwardRenderer *forwardRenderer = new Qt3DRender::QForwardRenderer();
    forwardRenderer->setCamera(m_camera);
    forwardRenderer->setClearColor(QColor(Qt::black));
    frameGraphComponent->setActiveFrameGraph(forwardRenderer);
    m_rootEntity->addComponent(frameGraphComponent);

    TableEntity *tableSurface = new TableEntity(m_rootEntity);
    tableSurface->setX(0.0f);
    tableSurface->setY(0.0f);
    tableSurface->setZ(0.0f);
    tableSurface->setScale(18);

    m_mahjongBoard = new MahjongBoard(tableSurface);
    m_mahjongBoard->setScale(0.9);
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

void MahjongGameScene::processInput(int x, int y)
{
    qDebug() << "Input event at(" << x << "," << y << ")";
}

