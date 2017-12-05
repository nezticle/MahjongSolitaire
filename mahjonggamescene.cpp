#include "mahjonggamescene.h"

#include <QtCore/QDebug>

#include <QtQuick/QQuickWindow>

#include <Qt3DCore/QEntity>
#include <Qt3DCore/QAspectEngine>
#include <Qt3DRender/QCamera>

#include <Qt3DRender/QRenderAspect>
#include <Qt3DExtras/QForwardRenderer>
#include <Qt3DRender/QRenderSettings>
#include <Qt3DRender/QDirectionalLight>
#include <Qt3DRender/QEnvironmentLight>
#include <Qt3DExtras/QSkyboxEntity>
//#include <Qt3DExtras/QOrbitCameraController>
#include <Qt3DRender/QPickingSettings>
#include <Qt3DRender/QTexture>
#include <Qt3DRender/QTextureImage>

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
    m_camera->setFieldOfView(45);
    m_camera->setUpVector(QVector3D(0.0f, 1.0f, 0.0f));
    m_camera->setViewCenter(QVector3D(0.0f, 0.0f, 0.0f));
    m_camera->setPosition(QVector3D(0.0f, -15.0f, 25.0f));
    m_camera->setExposure(1.0f);
    //m_camera->setPosition(QVector3D(50.0f, -100.0f, 100.0f));

//    // XXX Orbit Debug Camera
//    auto orbitCamera = new Qt3DExtras::QOrbitCameraController(m_rootEntity);
//    orbitCamera->setCamera(m_camera);
//    orbitCamera->setLinearSpeed(10);
//    orbitCamera->setLookSpeed(240);

    // Forward Renderer
    Qt3DRender::QRenderSettings *renderSettingsComponent = new Qt3DRender::QRenderSettings(m_rootEntity);
    Qt3DExtras::QForwardRenderer *forwardRenderer = new Qt3DExtras::QForwardRenderer();
    forwardRenderer->setCamera(m_camera);
    forwardRenderer->setClearColor(Qt::black);
    renderSettingsComponent->setActiveFrameGraph(forwardRenderer);
    auto pickingSettings = renderSettingsComponent->pickingSettings();
    pickingSettings->setPickResultMode(Qt3DRender::QPickingSettings::NearestPick);
    m_rootEntity->addComponent(renderSettingsComponent);

    m_inputSettings = new Qt3DInput::QInputSettings(m_rootEntity);
    m_rootEntity->addComponent(m_inputSettings);

    // Setup Scene
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


    Qt3DRender::QTextureWrapMode wrapMode;
    wrapMode.setX(Qt3DRender::QTextureWrapMode::ClampToEdge);
    wrapMode.setY(Qt3DRender::QTextureWrapMode::ClampToEdge);

    auto irradianceCubeMap = new Qt3DRender::QTextureLoader(m_rootEntity);
    irradianceCubeMap->setSource(QUrl("qrc:/textures/environment/memphis_skyline_cube_irradiance.dds"));
    irradianceCubeMap->setGenerateMipMaps(false);
    irradianceCubeMap->setMinificationFilter(Qt3DRender::QAbstractTexture::LinearMipMapLinear);
    irradianceCubeMap->setMagnificationFilter(Qt3DRender::QAbstractTexture::Linear);
    irradianceCubeMap->setWrapMode(wrapMode);
    auto specularCubeMap = new Qt3DRender::QTextureLoader(m_rootEntity);
    specularCubeMap->setSource(QUrl("qrc:/textures/environment/memphis_skyline_cube_specular.dds"));
    specularCubeMap->setGenerateMipMaps(false);
    specularCubeMap->setMinificationFilter(Qt3DRender::QAbstractTexture::LinearMipMapLinear);
    specularCubeMap->setMagnificationFilter(Qt3DRender::QAbstractTexture::Linear);
    specularCubeMap->setWrapMode(wrapMode);

    // Setup Skybox
    auto skybox = new Qt3DExtras::QSkyboxEntity(m_rootEntity);
    skybox->setBaseName("qrc:/textures/environment/memphis_skyline_cube_irradiance");
    skybox->setExtension(".dds");

    // Setup Environment Map
    auto environmentLightEntity = new Qt3DCore::QEntity(m_rootEntity);
    auto environmentLight = new Qt3DRender::QEnvironmentLight(environmentLightEntity);
    environmentLightEntity->addComponent(environmentLight);
    environmentLight->setIrradiance(irradianceCubeMap);
    environmentLight->setSpecular(specularCubeMap);
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

QQuickWindow *MahjongGameScene::inputSource() const
{
    return m_inputSource;
}

int MahjongGameScene::seed() const
{
    return m_seed;
}

void MahjongGameScene::setViewportSize(QSize viewportSize)
{
    if (m_viewportSize == viewportSize)
        return;

    m_viewportSize = viewportSize;
    if (m_camera != nullptr)
        m_camera->setAspectRatio(static_cast<float>(m_viewportSize.width()) / static_cast<float>(m_viewportSize.height()));
    emit viewportSizeChanged(viewportSize);
}

void MahjongGameScene::newGame()
{
    m_mahjongBoard->newGame();
    // Update current gameseed
    setSeed(m_mahjongBoard->gameSeed());
}

void MahjongGameScene::setInputSource(QQuickWindow *inputSource)
{
    if (m_inputSource == inputSource)
        return;

    m_inputSource = inputSource;
    emit inputSourceChanged(inputSource);
    m_inputSettings->setEventSource(inputSource);
}

void MahjongGameScene::setSeed(int seed)
{
    if (m_seed == seed)
        return;

    m_seed = seed;
    emit seedChanged(m_seed);
}


void MahjongGameScene::reset()
{
    m_mahjongBoard->newGame(m_seed);
}
