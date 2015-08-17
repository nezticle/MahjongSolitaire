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

#include <QtCore/QTime>
#include <QtCore/QDebug>

#include "tableentity.h"
#include "mahjongtileentity.h"
#include "mahjongboardlayoutitem.h"
#include "mahjongboardarea.h"

MahjongGameScene::MahjongGameScene(QObject *parent)
    : QObject(parent)
    , m_rootEntity(new Qt3D::QEntity())
    , m_viewportSize(QSize(800,600))
    , m_gameSeed(0)
    , m_tileWidth(0.74f)
    , m_tileHeight(1.0f)
    , m_tileDepth(0.3f)
    , m_firstTile(Q_NULLPTR)
    , m_tilesLeft(0)
    , m_hiddenNodeRoot(new QObject(this))
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

    //Entity which contains all MahjongTiles as children
    m_mahjongBoardArea = new MahjongBoardArea(tableSurface);
    //Set baseCenter and size for the board area
    m_mahjongBoardArea->setSize(QVector3D(0.9, 0.9, 0.2));

    //Create all of the tile items
    initTiles();
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

void MahjongGameScene::initTiles()
{
    //Create tiles
    for (int i = 0; i < 144; ++i) {
        //Create with no parent to prevent rendering
        MahjongTileEntity *tile = new MahjongTileEntity(Q_NULLPTR);
        tile->setParent(m_hiddenNodeRoot);
        m_tiles.append(tile);
    }
    int currentTarget = 0;
    for (int i = 0; i < 4; i++) {
        for (int j = 1; j <= 9; j++) {
            m_tiles[currentTarget]->setFaceValue("n" + QString::number(j)); currentTarget++;
            m_tiles[currentTarget]->setFaceValue("b" + QString::number(j)); currentTarget++;
            m_tiles[currentTarget]->setFaceValue("d" + QString::number(j)); currentTarget++;
        }
        for(int k = 1; k <= 3; k++) {
            m_tiles[currentTarget]->setFaceValue("z" + QString::number(k)); currentTarget++;
            m_tiles[currentTarget]->setFaceValue("w" + QString::number(k)); currentTarget++;
        }
        m_tiles[currentTarget]->setFaceValue("w" + QString::number(4)); currentTarget++;
    }
    for(int g = 1; g <= 4; g++ )
    {
        m_tiles[currentTarget]->setFaceValue("s" + QString::number(g)); currentTarget++;
        m_tiles[currentTarget]->setFaceValue("f" + QString::number(g)); currentTarget++;
    }
}

void MahjongGameScene::loadLayout()
{
    //Reset the current layout information
    foreach (MahjongBoardLayoutItem *boardPosition, m_boardTiles) {
        delete boardPosition;
    }
    m_boardTiles.clear();

    m_boardTiles.append(new MahjongBoardLayoutItem(3, 0, 0));
    m_boardTiles.append(new MahjongBoardLayoutItem(5, 0, 0));
    m_boardTiles.append(new MahjongBoardLayoutItem(7, 0, 0));
    m_boardTiles.append(new MahjongBoardLayoutItem(9, 0, 0));
    m_boardTiles.append(new MahjongBoardLayoutItem(11, 0, 0));
    m_boardTiles.append(new MahjongBoardLayoutItem(13, 0, 0));
    m_boardTiles.append(new MahjongBoardLayoutItem(15, 0, 0));
    m_boardTiles.append(new MahjongBoardLayoutItem(17, 0, 0));
    m_boardTiles.append(new MahjongBoardLayoutItem(19, 0, 0));
    m_boardTiles.append(new MahjongBoardLayoutItem(21, 0, 0));
    m_boardTiles.append(new MahjongBoardLayoutItem(23, 0, 0));
    m_boardTiles.append(new MahjongBoardLayoutItem(25, 0, 0));
    m_boardTiles.append(new MahjongBoardLayoutItem(7, 2, 0));
    m_boardTiles.append(new MahjongBoardLayoutItem(9, 2, 0));
    m_boardTiles.append(new MahjongBoardLayoutItem(11, 2, 0));
    m_boardTiles.append(new MahjongBoardLayoutItem(13, 2, 0));
    m_boardTiles.append(new MahjongBoardLayoutItem(15, 2, 0));
    m_boardTiles.append(new MahjongBoardLayoutItem(17, 2, 0));
    m_boardTiles.append(new MahjongBoardLayoutItem(19, 2, 0));
    m_boardTiles.append(new MahjongBoardLayoutItem(21, 2, 0));
    m_boardTiles.append(new MahjongBoardLayoutItem(5, 4, 0));
    m_boardTiles.append(new MahjongBoardLayoutItem(7, 4, 0));
    m_boardTiles.append(new MahjongBoardLayoutItem(9, 4, 0));
    m_boardTiles.append(new MahjongBoardLayoutItem(11, 4, 0));
    m_boardTiles.append(new MahjongBoardLayoutItem(13, 4, 0));
    m_boardTiles.append(new MahjongBoardLayoutItem(15, 4, 0));
    m_boardTiles.append(new MahjongBoardLayoutItem(17, 4, 0));
    m_boardTiles.append(new MahjongBoardLayoutItem(19, 4, 0));
    m_boardTiles.append(new MahjongBoardLayoutItem(21, 4, 0));
    m_boardTiles.append(new MahjongBoardLayoutItem(23, 4, 0));
    m_boardTiles.append(new MahjongBoardLayoutItem(1, 7, 0));
    m_boardTiles.append(new MahjongBoardLayoutItem(3, 6, 0));
    m_boardTiles.append(new MahjongBoardLayoutItem(5, 6, 0));
    m_boardTiles.append(new MahjongBoardLayoutItem(7, 6, 0));
    m_boardTiles.append(new MahjongBoardLayoutItem(9, 6, 0));
    m_boardTiles.append(new MahjongBoardLayoutItem(11, 6, 0));
    m_boardTiles.append(new MahjongBoardLayoutItem(13, 6, 0));
    m_boardTiles.append(new MahjongBoardLayoutItem(15, 6, 0));
    m_boardTiles.append(new MahjongBoardLayoutItem(17, 6, 0));
    m_boardTiles.append(new MahjongBoardLayoutItem(19, 6, 0));
    m_boardTiles.append(new MahjongBoardLayoutItem(21, 6, 0));
    m_boardTiles.append(new MahjongBoardLayoutItem(23, 6, 0));
    m_boardTiles.append(new MahjongBoardLayoutItem(25, 6, 0));
    m_boardTiles.append(new MahjongBoardLayoutItem(3, 8, 0));
    m_boardTiles.append(new MahjongBoardLayoutItem(5, 8, 0));
    m_boardTiles.append(new MahjongBoardLayoutItem(7, 8, 0));
    m_boardTiles.append(new MahjongBoardLayoutItem(9, 8, 0));
    m_boardTiles.append(new MahjongBoardLayoutItem(11, 8, 0));
    m_boardTiles.append(new MahjongBoardLayoutItem(13, 8, 0));
    m_boardTiles.append(new MahjongBoardLayoutItem(15, 8, 0));
    m_boardTiles.append(new MahjongBoardLayoutItem(17, 8, 0));
    m_boardTiles.append(new MahjongBoardLayoutItem(19, 8, 0));
    m_boardTiles.append(new MahjongBoardLayoutItem(21, 8, 0));
    m_boardTiles.append(new MahjongBoardLayoutItem(23, 8, 0));
    m_boardTiles.append(new MahjongBoardLayoutItem(25, 8, 0));
    m_boardTiles.append(new MahjongBoardLayoutItem(27, 7, 0));
    m_boardTiles.append(new MahjongBoardLayoutItem(29, 7, 0));
    m_boardTiles.append(new MahjongBoardLayoutItem(5, 10, 0));
    m_boardTiles.append(new MahjongBoardLayoutItem(7, 10, 0));
    m_boardTiles.append(new MahjongBoardLayoutItem(9, 10, 0));
    m_boardTiles.append(new MahjongBoardLayoutItem(11, 10, 0));
    m_boardTiles.append(new MahjongBoardLayoutItem(13, 10, 0));
    m_boardTiles.append(new MahjongBoardLayoutItem(15, 10, 0));
    m_boardTiles.append(new MahjongBoardLayoutItem(17, 10, 0));
    m_boardTiles.append(new MahjongBoardLayoutItem(19, 10, 0));
    m_boardTiles.append(new MahjongBoardLayoutItem(21, 10, 0));
    m_boardTiles.append(new MahjongBoardLayoutItem(23, 10, 0));
    m_boardTiles.append(new MahjongBoardLayoutItem(7, 12, 0));
    m_boardTiles.append(new MahjongBoardLayoutItem(9, 12, 0));
    m_boardTiles.append(new MahjongBoardLayoutItem(11, 12, 0));
    m_boardTiles.append(new MahjongBoardLayoutItem(13, 12, 0));
    m_boardTiles.append(new MahjongBoardLayoutItem(15, 12, 0));
    m_boardTiles.append(new MahjongBoardLayoutItem(17, 12, 0));
    m_boardTiles.append(new MahjongBoardLayoutItem(19, 12, 0));
    m_boardTiles.append(new MahjongBoardLayoutItem(21, 12, 0));
    m_boardTiles.append(new MahjongBoardLayoutItem(3, 14, 0));
    m_boardTiles.append(new MahjongBoardLayoutItem(5, 14, 0));
    m_boardTiles.append(new MahjongBoardLayoutItem(7, 14, 0));
    m_boardTiles.append(new MahjongBoardLayoutItem(9, 14, 0));
    m_boardTiles.append(new MahjongBoardLayoutItem(11, 14, 0));
    m_boardTiles.append(new MahjongBoardLayoutItem(13, 14, 0));
    m_boardTiles.append(new MahjongBoardLayoutItem(15, 14, 0));
    m_boardTiles.append(new MahjongBoardLayoutItem(17, 14, 0));
    m_boardTiles.append(new MahjongBoardLayoutItem(19, 14, 0));
    m_boardTiles.append(new MahjongBoardLayoutItem(21, 14, 0));
    m_boardTiles.append(new MahjongBoardLayoutItem(23, 14, 0));
    m_boardTiles.append(new MahjongBoardLayoutItem(25, 14, 0));
    m_boardTiles.append(new MahjongBoardLayoutItem(9, 2, 1));
    m_boardTiles.append(new MahjongBoardLayoutItem(11, 2, 1));
    m_boardTiles.append(new MahjongBoardLayoutItem(13, 2, 1));
    m_boardTiles.append(new MahjongBoardLayoutItem( 15, 2, 1));
    m_boardTiles.append(new MahjongBoardLayoutItem(17, 2, 1));
    m_boardTiles.append(new MahjongBoardLayoutItem(19, 2, 1));
    m_boardTiles.append(new MahjongBoardLayoutItem(9, 4, 1));
    m_boardTiles.append(new MahjongBoardLayoutItem(11, 4, 1));
    m_boardTiles.append(new MahjongBoardLayoutItem(13, 4, 1));
    m_boardTiles.append(new MahjongBoardLayoutItem(15, 4, 1));
    m_boardTiles.append(new MahjongBoardLayoutItem(17, 4, 1));
    m_boardTiles.append(new MahjongBoardLayoutItem(19, 4, 1));
    m_boardTiles.append(new MahjongBoardLayoutItem(9, 6, 1));
    m_boardTiles.append(new MahjongBoardLayoutItem(11, 6, 1));
    m_boardTiles.append(new MahjongBoardLayoutItem(13, 6, 1));
    m_boardTiles.append(new MahjongBoardLayoutItem(15, 6, 1));
    m_boardTiles.append(new MahjongBoardLayoutItem(17, 6, 1));
    m_boardTiles.append(new MahjongBoardLayoutItem(19, 6, 1));
    m_boardTiles.append(new MahjongBoardLayoutItem(9, 8, 1));
    m_boardTiles.append(new MahjongBoardLayoutItem(11, 8, 1));
    m_boardTiles.append(new MahjongBoardLayoutItem(13, 8, 1));
    m_boardTiles.append(new MahjongBoardLayoutItem(15, 8, 1));
    m_boardTiles.append(new MahjongBoardLayoutItem(17, 8, 1));
    m_boardTiles.append(new MahjongBoardLayoutItem(19, 8, 1));
    m_boardTiles.append(new MahjongBoardLayoutItem(9, 10, 1));
    m_boardTiles.append(new MahjongBoardLayoutItem(11, 10, 1));
    m_boardTiles.append(new MahjongBoardLayoutItem(13, 10, 1));
    m_boardTiles.append(new MahjongBoardLayoutItem(15, 10, 1));
    m_boardTiles.append(new MahjongBoardLayoutItem(17, 10, 1));
    m_boardTiles.append(new MahjongBoardLayoutItem(19, 10, 1));
    m_boardTiles.append(new MahjongBoardLayoutItem(9, 12, 1));
    m_boardTiles.append(new MahjongBoardLayoutItem(11, 12, 1));
    m_boardTiles.append(new MahjongBoardLayoutItem(13, 12, 1));
    m_boardTiles.append(new MahjongBoardLayoutItem(15, 12, 1));
    m_boardTiles.append(new MahjongBoardLayoutItem(17, 12, 1));
    m_boardTiles.append(new MahjongBoardLayoutItem(19, 12, 1));
    m_boardTiles.append(new MahjongBoardLayoutItem(11, 4, 2));
    m_boardTiles.append(new MahjongBoardLayoutItem(13, 4, 2));
    m_boardTiles.append(new MahjongBoardLayoutItem(15, 4, 2));
    m_boardTiles.append(new MahjongBoardLayoutItem(17, 4, 2));
    m_boardTiles.append(new MahjongBoardLayoutItem(11, 6, 2));
    m_boardTiles.append(new MahjongBoardLayoutItem(13, 6, 2));
    m_boardTiles.append(new MahjongBoardLayoutItem(15, 6, 2));
    m_boardTiles.append(new MahjongBoardLayoutItem(17, 6, 2));
    m_boardTiles.append(new MahjongBoardLayoutItem(11, 8, 2));
    m_boardTiles.append(new MahjongBoardLayoutItem(13, 8, 2));
    m_boardTiles.append(new MahjongBoardLayoutItem(15, 8, 2));
    m_boardTiles.append(new MahjongBoardLayoutItem(17, 8, 2));
    m_boardTiles.append(new MahjongBoardLayoutItem(11, 10, 2));
    m_boardTiles.append(new MahjongBoardLayoutItem(13, 10, 2));
    m_boardTiles.append(new MahjongBoardLayoutItem(15, 10, 2));
    m_boardTiles.append(new MahjongBoardLayoutItem(17, 10, 2));
    m_boardTiles.append(new MahjongBoardLayoutItem(13, 6, 3));
    m_boardTiles.append(new MahjongBoardLayoutItem(15, 6, 3));
    m_boardTiles.append(new MahjongBoardLayoutItem(13, 8, 3));
    m_boardTiles.append(new MahjongBoardLayoutItem(15, 8, 3));
    m_boardTiles.append(new MahjongBoardLayoutItem(14, 7, 4));
}

void MahjongGameScene::initGame()
{
    qsrand(m_gameSeed);

    loadLayout();

    //Assert that Layout and Tiles are the same size
    Q_ASSERT(m_tiles.count() == m_boardTiles.count());

    //Shuffle the tiles
    QVector<int> shuffleIndex;
    for (int i = 0; i < m_tiles.count(); ++i)
        shuffleIndex.append(i);

    for (int i = 0; i < m_tiles.count(); ++i) {
        int indexToSwap = qrand() % ((m_tiles.count()) - i) + i;
        int oldValue = shuffleIndex[i];
        shuffleIndex[i] = shuffleIndex[indexToSwap];
        shuffleIndex[indexToSwap] = oldValue;
    }

    //Place the now sorted tiles in the m_boardTiles structure
    for (int i = 0; i < m_tiles.count(); ++i) {
        MahjongTileEntity *tile = m_tiles[shuffleIndex[i]];
        m_boardTiles[i]->setTile(tile);
        tile->setBoardPosition(m_boardTiles[i]);
        //Set visible by setting paren
        tile->setParent(m_mahjongBoardArea);
    }

    //Move tiles into their calculated positions
    setupTitles();
}

void MahjongGameScene::setupTitles()
{
    m_firstTile = Q_NULLPTR;
    m_tilesLeft = m_boardTiles.count(); //should be 144

    float tileWidthMultiplier = m_tileWidth / 2.0f;
    float tileHeightMultiplier = m_tileHeight / 2.0f;
    float tileDepthMultiplier = m_tileDepth / 2.0f;

    QRect gameboardGeometry;
    gameboardGeometry.setWidth(tileWidthMultiplier * 32.0f);
    gameboardGeometry.setHeight(tileHeightMultiplier * 16.0f);
    gameboardGeometry.setX(-gameboardGeometry.width() / 2.0f);
    gameboardGeometry.setY(-gameboardGeometry.height() / 2.0f);

    foreach (MahjongBoardLayoutItem *boardItem, m_boardTiles) {
        QVector3D position;
        position.setX(((boardItem->x() * tileWidthMultiplier) + tileWidthMultiplier) + gameboardGeometry.x());
        position.setY(((boardItem->y() * tileHeightMultiplier) + tileHeightMultiplier) + gameboardGeometry.y());
        position.setZ((boardItem->d() * tileDepthMultiplier * 2) + tileDepthMultiplier);
        boardItem->tile()->setTranslate(position);
    }
}

void MahjongGameScene::newGame()
{
    m_gameSeed = QTime::currentTime().msecsSinceStartOfDay();
    initGame();
}

bool MahjongGameScene::isOnLeft(MahjongBoardLayoutItem *tile1, MahjongBoardLayoutItem *tile2)
{
    return ((tile1->x() - 2 == tile2->x()) &&
            (tile1->y() == tile2->y() || tile1->y() + 1 == tile2->y() || tile1->y() - 1 == tile2->y()) &&
            (tile1->d() == tile2->d()));
}

bool MahjongGameScene::isOnRight(MahjongBoardLayoutItem *tile1, MahjongBoardLayoutItem *tile2)
{
    return ((tile1->x() + 2 == tile2->x()) &&
            (tile1->y() == tile2->y() || tile1->y() + 1 == tile2->y() || tile1->y() - 1 == tile2->y()) &&
            (tile1->d() == tile2->d()));
}

bool MahjongGameScene::isOnTop(MahjongBoardLayoutItem *tile1, MahjongBoardLayoutItem *tile2)
{
    return ((tile1->d() + 1 == tile2->d()) &&
            ((tile1->x() == tile2->x() && tile1->y() == tile2->y()) ||
             (tile1->x() == tile2->x() && tile1->y() - 1 == tile2->y()) ||
             (tile1->x() == tile2->x() && tile1->y() + 1 == tile2->y()) ||
             (tile1->x() - 1 == tile2->x() && tile1->y() == tile2->y()) ||
             (tile1->x() - 1 == tile2->x() && tile1->y() - 1 == tile2->y()) ||
             (tile1->x() - 1 == tile2->x() && tile1->y() + 1 == tile2->y()) ||
             (tile1->x() + 1 == tile2->x() && tile1->y() == tile2->y()) ||
             (tile1->x() + 1 == tile2->x() && tile1->y() - 1 == tile2->y()) ||
             (tile1->x() + 1 == tile2->x() && tile1->y() + 1 == tile2->y())));
}

bool MahjongGameScene::canRemove(MahjongTileEntity *tile)
{
    bool isRight = false;
    bool isLeft = false;
    bool isTop = false;
    bool isRemoveable = false;

    QString w1 = tile->faceValue();
    QString w2 = m_firstTile->faceValue();
    QString w1_name = w1.mid(0, 1);
    QString w2_name = w2.mid(0, 1);

    foreach (MahjongBoardLayoutItem *boardTile, m_boardTiles) {
        if (isOnLeft(tile->boardPosition(), boardTile))
            isLeft = true;
        if (isOnRight(tile->boardPosition(), boardTile))
            isRight = true;
        if (isOnTop(tile->boardPosition(), boardTile))
            isTop = true;
    }

    if (!isTop && ((!isLeft && !isRight) || (isLeft && !isRight) || (!isLeft && isRight)))
    {
        if (w2_name == "n" || w2_name == "b" || w2_name == "d" || w2_name == "w" || w2_name == "z")
        {
            if (w1 == w2)
            {
                isRemoveable = true;
            }
        }
        else if (w2_name == "s")
        {
            if (w1_name == "s")
            {
                isRemoveable = true;
            }
        }
        else if (w2_name == "f")
        {
            if (w1_name == "f")
            {
                isRemoveable = true;
            }
        }
    }

    return isRemoveable;
}

bool MahjongGameScene::canBegin(MahjongBoardLayoutItem *tile)
{
    bool isRight = false;
    bool isLeft = false;
    bool isTop = false;

    foreach (MahjongBoardLayoutItem *boardTile, m_boardTiles) {
        if (isOnLeft(tile, boardTile))
            isLeft = true;
        if (isOnRight(tile, boardTile))
            isRight = true;
        if (isOnTop(tile, boardTile))
            isTop = true;
    }

    return ((!isTop) && ((!isLeft && !isRight) || (isLeft && !isRight) || (!isLeft && isRight)));
}

int MahjongGameScene::countCombinations()
{
    m_hints = QString();
    int combinations = 0;
    QVector<MahjongBoardLayoutItem*> possiblePairsArray;

    foreach (MahjongBoardLayoutItem *tile, m_boardTiles) {
        if (canBegin(tile))
            possiblePairsArray.append(tile);
    }

    for (int r = 0; r < possiblePairsArray.count(); r++)
    {
        for (int j = 0; j < r; j++)
        {
            bool compatible = false;
            MahjongBoardLayoutItem *w1 = possiblePairsArray[j];
            MahjongBoardLayoutItem *w2 = possiblePairsArray[r];
            QString w1_name = w1->tile()->faceValue().mid(0,1);
            QString w2_name = w2->tile()->faceValue().mid(0,1);
            if (w2_name == "n" || w2_name == "b" || w2_name == "d" || w2_name == "w" || w2_name == "z")
            {
                if (w1->tile()->faceValue() == w2->tile()->faceValue())
                    compatible = true;
            }
            else if (w2_name == "s")
            {
                if (w1_name == "s")
                    compatible = true;
            }
            else if (w2_name == "f")
            {
                if (w1_name == "f")
                    compatible = true;
            }
            if (compatible)
            {
                combinations++;
                m_hints += w2->tile()->faceValue() + " ";
            }
        }
    }

    qDebug() << m_hints;

    return combinations;
}

void MahjongGameScene::removeTiles(MahjongTileEntity *tile1, MahjongTileEntity *tile2)
{
    MahjongBoardLayoutItem *tile1Position = tile1->boardPosition();
    MahjongBoardLayoutItem *tile2Position = tile2->boardPosition();
    m_boardTiles.removeOne(tile1Position);
    m_boardTiles.removeOne(tile2Position);
    tile1->setBoardPosition(Q_NULLPTR);
    tile2->setBoardPosition(Q_NULLPTR);

    m_firstTile = Q_NULLPTR;
    m_tilesLeft -= 2;
    tile1->setSelected(false);
    tile2->setSelected(false);
    tile1->setParent(m_hiddenNodeRoot);
    tile2->setParent(m_hiddenNodeRoot);
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

