#include "mahjongboard.h"
#include "mahjongtile.h"
#include "mahjongboardlayoutitem.h"
#include "mahjongtilematerial.h"

#include <Qt3DCore/QTransform>
#include <Qt3DRender/QBuffer>
#include <Qt3DRender/QMesh>
#include <Qt3DRender/QAttribute>
#include <Qt3DRender/QTextureImage>

#include <QtCore/QTime>
#include <QtCore/QDebug>

MahjongBoard::MahjongBoard(Qt3DCore::QNode *parent)
    : Qt3DCore::QEntity(parent)
{
    //Transform
    m_transform = new Qt3DCore::QTransform(this);
    // Normalize for XxY instead of XxZ
    m_transform->setRotation(QQuaternion::fromAxisAndAngle(1.0f, 0.0f, 0.0f, -90.0f));
    addComponent(m_transform);

    // Setup Buffer containing Tile instance data
    m_tileInstanceBuffer = new Qt3DRender::QBuffer();
    m_tileInstanceBuffer->setParent(this);
    resetTileBufferData();

    // Setup Geometry Renderer for Tile
    m_tileMesh = new Qt3DRender::QMesh(this);
    m_tileMesh->setSource(QUrl("qrc:/models/MahjongTile_improved.obj"));
    m_tileMesh->setInstanceCount(m_tiles.count());
    connect(m_tileMesh, &Qt3DRender::QGeometryRenderer::geometryChanged, [=] () {
        // Setup Attributes for Tile instances (position, selected, face)
        setupTileInstanceAttributes();
    });
    addComponent(m_tileMesh);

    // Setup Material for rendering tile instances
    m_material = new MahjongTileMaterial(this);
    setupTextures();
    addComponent(m_material);
}

MahjongBoard::~MahjongBoard()
{
}

QVector3D MahjongBoard::translate() const
{
    return m_transform->translation();
}

float MahjongBoard::scale() const
{
    return m_transform->scale();
}

void MahjongBoard::newGame()
{
    m_gameSeed = QTime::currentTime().msecsSinceStartOfDay();
    initGame();
}

void MahjongBoard::setTranslate(QVector3D translate)
{
    if (m_transform->translation() == translate)
        return;

    m_transform->setTranslation(translate);
    emit translateChanged(translate);
    updateTileRenderer();
}

void MahjongBoard::setScale(float scale)
{
    if (m_transform->scale() == scale)
        return;

    m_transform->setScale(scale);
    emit scaleChanged(scale);
    updateTileRenderer();
}

void MahjongBoard::checkTileTouched(MahjongTile *tile)
{
    if (m_firstTile == nullptr) {
        //If the tile was the first selected
        if (canBegin(tile->boardPosition())) {
            //Tile is selectable
            m_firstTile = tile;
            tile->setSelected(true);
        } else {
            //not selectable
        }
    } else {
        //If a tile is already selected
        if (m_firstTile == tile) {
            //if the tile selected is already selected
            tile->setSelected(false);
            m_firstTile = nullptr;
        } else if (canRemove(tile)) {
            //tiles match, can be removed
            removeTiles(m_firstTile, tile);
            //Test Game Over or Victory conditions
            int possibleMoves = countCombinations();
            if (possibleMoves == 0) {
                if (m_tilesLeft == 0) {
                    //Victory
                    qDebug() << "you win";
                    //print("you win");
                    newGame();
                } else {
                    //Game Over
                    qDebug() << "game over";
                    //print("game over");
                    newGame();
                }
            }
            //print(possibleMoves + " possible moves left");
        } else {
            //Tiles don't match
            if (canBegin(tile->boardPosition())) {
                //But new tile can begin
                m_firstTile->setSelected(false);
                m_firstTile = tile;
                tile->setSelected(true);
            }
        }
    }
}

void MahjongBoard::initTiles()
{
    // Delete previous tiles if available
    qDeleteAll(m_tiles);
    m_tiles.clear();

    // Create new tiles
    for (int i = 0; i < 144; ++i) {
        m_tiles.append(new MahjongTile(this));
    }

    // Initialize the standard "deck" of tiles
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

void MahjongBoard::reset()
{
    initTiles();
    m_firstTile = nullptr;
    updateTileRenderer();
}

void MahjongBoard::loadLayout()
{
    //Reset the current layout information
    qDeleteAll(m_boardTiles);
    m_boardTiles.clear();

    //### TODO add additional layout loader (probably on bitbucket)
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

void MahjongBoard::initGame()
{
    // XXX Replace with new Random classes
    // Try and pick a random function that produces the same
    // values across machines so we can reuse the seeds.
    // Also by using our own random instead of the global qrand
    // we can make sure nothing else is consuming random values
    // (ex. particle systems)
    qsrand(m_gameSeed);

    reset();

    loadLayout();

    // Assert that Layout and Tiles are the same size
    Q_ASSERT(m_tiles.count() == m_boardTiles.count());

    m_tilesLeft = m_boardTiles.count(); // should be 144

    // Shuffle the tiles
    QVector<int> shuffleIndex;
    for (int i = 0; i < m_tiles.count(); ++i)
        shuffleIndex.append(i);

    for (int i = 0; i < m_tiles.count(); ++i) {
        int indexToSwap = qrand() % ((m_tiles.count()) - i) + i;
        int oldValue = shuffleIndex[i];
        shuffleIndex[i] = shuffleIndex[indexToSwap];
        shuffleIndex[indexToSwap] = oldValue;
    }

    // Place the now sorted tiles in the m_boardTiles structure
    for (int i = 0; i < m_tiles.count(); ++i) {
        MahjongTile *tile = m_tiles[shuffleIndex[i]];
        m_boardTiles[i]->setTile(tile);
        tile->setBoardPosition(m_boardTiles[i]);
    }

    // Move tiles into their calculated positions
    setupTiles();

    updateTileRenderer();
}

void MahjongBoard::setupTiles()
{
    const float tileWidthMultiplier = MahjongTile::tileWidth() / 2.0f;
    const float tileHeightMultiplier = MahjongTile::tileHeight() / 2.0f;
    const float tileDepthMultiplier = MahjongTile::tileDepth() / 2.0f;

    const float gameboardWidth = tileWidthMultiplier * 32.0f;
    const float gameboardHeight = tileHeightMultiplier * 16.0f;
    const QRectF gameboardGeometry(-gameboardWidth / 2.0f,
                                   -gameboardHeight / 2.0f,
                                   gameboardWidth,
                                   gameboardHeight);

    for (auto boardItem : m_boardTiles) {
        // Set position of tile to match position in layout structure
        const QVector3D position(((boardItem->x() * tileWidthMultiplier) + tileWidthMultiplier) + gameboardGeometry.x(),
                                 ((boardItem->y() * tileHeightMultiplier) + tileHeightMultiplier) + gameboardGeometry.y(),
                                 (boardItem->d() * tileDepthMultiplier * 2) + tileDepthMultiplier);
        boardItem->tile()->setTranslate(position);
    }
}

bool MahjongBoard::isOnLeft(MahjongBoardLayoutItem *tile1, MahjongBoardLayoutItem *tile2) const
{
    return ((tile1->x() - 2 == tile2->x()) &&
            (tile1->y() == tile2->y() || tile1->y() + 1 == tile2->y() || tile1->y() - 1 == tile2->y()) &&
            (tile1->d() == tile2->d()));
}

bool MahjongBoard::isOnRight(MahjongBoardLayoutItem *tile1, MahjongBoardLayoutItem *tile2) const
{
    return ((tile1->x() + 2 == tile2->x()) &&
            (tile1->y() == tile2->y() || tile1->y() + 1 == tile2->y() || tile1->y() - 1 == tile2->y()) &&
            (tile1->d() == tile2->d()));
}

bool MahjongBoard::isOnTop(MahjongBoardLayoutItem *tile1, MahjongBoardLayoutItem *tile2) const
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

bool MahjongBoard::canRemove(MahjongTile *tile) const
{
    // XXX Try and refactor this to not depend on string comparison
    const QString w1 = tile->faceValue();
    const QString w2 = m_firstTile->faceValue();
    const QString w1_name = w1.mid(0, 1);
    const QString w2_name = w2.mid(0, 1);

    bool isRight = false;
    bool isLeft = false;
    bool isTop = false;
    bool isRemoveable = false;
    for (const auto boardTile : m_boardTiles) {
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

bool MahjongBoard::canBegin(MahjongBoardLayoutItem *tile) const
{
    bool isRight = false;
    bool isLeft = false;
    bool isTop = false;

    for (const auto boardTile : m_boardTiles) {
        if (isOnLeft(tile, boardTile))
            isLeft = true;
        if (isOnRight(tile, boardTile))
            isRight = true;
        if (isOnTop(tile, boardTile))
            isTop = true;
    }

    return ((!isTop) && ((!isLeft && !isRight) || (isLeft && !isRight) || (!isLeft && isRight)));
}

int MahjongBoard::countCombinations()
{
    QVector<MahjongBoardLayoutItem*> possiblePairsArray;
    for (const auto tile : m_boardTiles) {
        if (canBegin(tile))
            possiblePairsArray.append(tile);
    }

    int combinations = 0;
    m_hints.clear();
    for (int r = 0; r < possiblePairsArray.count(); r++)
    {
        for (int j = 0; j < r; j++)
        {
            bool compatible = false;
            const MahjongBoardLayoutItem *w1 = possiblePairsArray[j];
            const MahjongBoardLayoutItem *w2 = possiblePairsArray[r];
            const QString w1_name = w1->tile()->faceValue().mid(0,1);
            const QString w2_name = w2->tile()->faceValue().mid(0,1);
            if (w2_name == "n" || w2_name == "b" || w2_name == "d" || w2_name == "w" || w2_name == "z") {
                if (w1->tile()->faceValue() == w2->tile()->faceValue())
                    compatible = true;
            } else if (w2_name == "s") {
                if (w1_name == "s")
                    compatible = true;
            } else if (w2_name == "f") {
                if (w1_name == "f")
                    compatible = true;
            } if (compatible) {
                combinations++;
                m_hints += w2->tile()->faceValue() + " ";
            }
        }
    }

    return combinations;
}

void MahjongBoard::removeTiles(MahjongTile *tile1, MahjongTile *tile2)
{
    MahjongBoardLayoutItem *tile1Position = tile1->boardPosition();
    MahjongBoardLayoutItem *tile2Position = tile2->boardPosition();
    m_boardTiles.removeOne(tile1Position);
    m_boardTiles.removeOne(tile2Position);
    m_tiles.removeOne(tile1);
    m_tiles.removeOne(tile2);
    delete tile1;
    delete tile2;
    updateTileRenderer();
    m_firstTile = nullptr;
    m_tilesLeft -= 2;
}

void MahjongBoard::resetTileBufferData()
{
    QByteArray byteArray;
    byteArray.resize(m_tiles.count() * sizeof(TileBufferLayout));
    TileBufferLayout *data = reinterpret_cast<TileBufferLayout *>(byteArray.data());
    for (const auto tile : m_tiles) {
        data->pos = tile->translate();
        data->isSelected = tile->isSelected();
        data->face = tile->face();
        ++data;
    }
    m_tileInstanceBuffer->setData(byteArray);
}

void MahjongBoard::setupTileInstanceAttributes()
{
    // (position, selected, face)
    auto positionAttribute = new Qt3DRender::QAttribute(m_tileMesh);
    positionAttribute->setName(QStringLiteral("pos"));
    positionAttribute->setAttributeType(Qt3DRender::QAttribute::VertexAttribute);
    positionAttribute->setVertexBaseType(Qt3DRender::QAttribute::Float);
    positionAttribute->setVertexSize(3);
    positionAttribute->setDivisor(1);
    positionAttribute->setBuffer(m_tileInstanceBuffer);
    positionAttribute->setByteOffset(0);
    positionAttribute->setByteStride(sizeof(TileBufferLayout));
    m_tileMesh->geometry()->addAttribute(positionAttribute);

    auto selectedAttribute = new Qt3DRender::QAttribute(m_tileMesh);
    selectedAttribute->setName("isSelected");
    selectedAttribute->setAttributeType(Qt3DRender::QAttribute::VertexAttribute);
    selectedAttribute->setVertexBaseType(Qt3DRender::QAttribute::Int);
    selectedAttribute->setVertexSize(1);
    selectedAttribute->setDivisor(1);
    selectedAttribute->setByteOffset(sizeof(QVector3D));
    selectedAttribute->setByteStride(sizeof(TileBufferLayout));
    selectedAttribute->setBuffer(m_tileInstanceBuffer);
    m_tileMesh->geometry()->addAttribute(selectedAttribute);

    auto faceAttribute = new Qt3DRender::QAttribute(m_tileMesh);
    faceAttribute->setName("faceId");
    faceAttribute->setAttributeType(Qt3DRender::QAttribute::VertexAttribute);
    faceAttribute->setVertexBaseType(Qt3DRender::QAttribute::Int);
    faceAttribute->setVertexSize(1);
    faceAttribute->setDivisor(1);
    faceAttribute->setByteOffset(sizeof(QVector3D) + sizeof(int));
    faceAttribute->setByteStride(sizeof(TileBufferLayout));
    faceAttribute->setBuffer(m_tileInstanceBuffer);
    m_tileMesh->geometry()->addAttribute(faceAttribute);
}

void MahjongBoard::updateTileRenderer()
{
    resetTileBufferData();
    m_tileMesh->setInstanceCount(m_tiles.count());
}

void MahjongBoard::setupTextures()
{
    // base color (array)
    auto baseColorTexture = new Qt3DRender::QTextureImage;
    baseColorTexture->setSource(QUrl(QString("qrc:/textures/tiles/MahjongTile_improved_DefaultMaterial_BaseColor.png")));
    m_material->baseColor()->addTextureImage(baseColorTexture);

    // metalness (array)
    auto metalnessTexture = new Qt3DRender::QTextureImage;
    metalnessTexture->setSource(QUrl(QString("qrc:/textures/tiles/MahjongTile_improved_DefaultMaterial_Metallic.png")));
    m_material->metalness()->addTextureImage(metalnessTexture);

    // roughness (array)
    auto roughnessTexture = new Qt3DRender::QTextureImage;
    roughnessTexture->setSource(QUrl(QString("qrc:/textures/tiles/MahjongTile_improved_DefaultMaterial_Roughness.png")));
    m_material->roughness()->addTextureImage(roughnessTexture);

    // ambient Occulusion
    auto aoTexture = new Qt3DRender::QTextureImage;
    aoTexture->setSource(QUrl(QString("qrc:/textures/tiles/MahjongTile_improved_DefaultMaterial_Mixed_AO.png")));
    m_material->ambientOcclusion()->addTextureImage(aoTexture);

    // normal
    auto normalTexture = new Qt3DRender::QTextureImage;
    normalTexture->setSource(QUrl(QString("qrc:/textures/tiles/MahjongTile_improved_DefaultMaterial_Normal.png")));
    m_material->normal()->addTextureImage(normalTexture);
}
