#include "mahjongboard.h"
#include "mahjongtileentity.h"
#include "mahjongboardlayoutitem.h"

#include <Qt3DCore/QTransform>
#include <Qt3DCore/QTranslateTransform>
#include <Qt3dCore/QScaleTransform>

#include <QtCore/QTime>
#include <QtCore/QDebug>

MahjongBoard::MahjongBoard(Qt3D::QNode *parent)
    : Qt3D::QEntity(parent)
    , m_gameSeed(0)
    , m_tileWidth(0.74f)
    , m_tileHeight(1.0f)
    , m_tileDepth(0.3f)
    , m_firstTile(Q_NULLPTR)
    , m_tilesLeft(0)
    , m_hiddenNodeRoot(new Qt3D::QEntity())
{
    //Transform
    Qt3D::QTransform *transform = new Qt3D::QTransform(this);
    m_translate = new Qt3D::QTranslateTransform;
    transform->addTransform(m_translate);
    m_scale = new Qt3D::QScaleTransform;
    transform->addTransform(m_scale);
    addComponent(transform);

    //Create all of the tile items
    initTiles();
}

MahjongBoard::~MahjongBoard()
{
    delete m_hiddenNodeRoot;
}

QVector3D MahjongBoard::translate() const
{
    return m_translate->translation();
}

float MahjongBoard::scale() const
{
    return m_scale->scale();
}

void MahjongBoard::newGame()
{
    m_gameSeed = QTime::currentTime().msecsSinceStartOfDay();
    initGame();
}

void MahjongBoard::setTranslate(QVector3D translate)
{
    if (m_translate->translation() == translate)
        return;

    m_translate->setTranslation(translate);
    emit translateChanged(translate);
}

void MahjongBoard::setScale(float scale)
{
    if (m_scale->scale() == scale)
        return;

    m_scale->setScale(scale);
    emit scaleChanged(scale);
}

void MahjongBoard::initTiles()
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

void MahjongBoard::loadLayout()
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

void MahjongBoard::initGame()
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
        //Set visible by setting parent
        tile->setParent(this);
    }

    //Move tiles into their calculated positions
    setupTitles();
}

void MahjongBoard::setupTitles()
{
    m_firstTile = Q_NULLPTR;
    m_tilesLeft = m_boardTiles.count(); //should be 144

//    QRectF gameboardGeometry;
//    QRectF boardAreaRect;
//    boardAreaRect.setWidth(m_mahjongBoardArea->size().x());
//    boardAreaRect.setHeight(m_mahjongBoardArea->size().y());
//    boardAreaRect.setTopLeft(QPointF(-(boardAreaRect.width() / 2.0f) + m_mahjongBoardArea->baseCenter().x(),
//                             -(boardAreaRect.height() / 2.0f) + m_mahjongBoardArea->baseCenter().y()));

//    const float targetRatio = 3.0f / 2.0f;
//    const float currentRatio = boardAreaRect.width() / boardAreaRect.height();

//    if (currentRatio > targetRatio) {
//        gameboardGeometry.setWidth(3.0f * boardAreaRect.height());
//        gameboardGeometry.setHeight(boardAreaRect.height());
//    } else {
//        gameboardGeometry.setWidth(boardAreaRect.width());
//        gameboardGeometry.setHeight(2.0f * boardAreaRect.width());
//    }
//    gameboardGeometry.setX(((boardAreaRect.width() - gameboardGeometry.width()) / 2.0f) + boardAreaRect.x());
//    gameboardGeometry.setY(((boardAreaRect.height() - gameboardGeometry.height()) / 2.0)+ boardAreaRect.y());

//    float tileWidthMultiplier = gameboardGeometry.width() / 32.0f;
//    float tileHeightMultiplier = gameboardGeometry.height() / 16.0f;


//    float tileWidthMultiplier = m_tileWidth / 2.0f;
//    float tileHeightMultiplier = m_tileHeight / 2.0f;
//    float tileDepthMultiplier = m_tileDepth / 2.0f;

//    QRect gameboardGeometry;
//    gameboardGeometry.setWidth(tileWidthMultiplier * 32.0f);
//    gameboardGeometry.setHeight(tileHeightMultiplier * 16.0f);
//    gameboardGeometry.setX(-gameboardGeometry.width() / 2.0f);
//    gameboardGeometry.setY(-gameboardGeometry.height() / 2.0f);

//    //Determine tile scale factor
//    //(multiply gameboardGeometry by what to fit inside of m_mahjongBoardArea)

//    foreach (MahjongBoardLayoutItem *boardItem, m_boardTiles) {
//        QVector3D position;
//        position.setX(((boardItem->x() * tileWidthMultiplier) + tileWidthMultiplier) + gameboardGeometry.x());
//        position.setY(((boardItem->y() * tileHeightMultiplier) + tileHeightMultiplier) + gameboardGeometry.y());
//        position.setZ((boardItem->d() * tileDepthMultiplier * 2) + tileDepthMultiplier);
//        boardItem->tile()->setTranslate(position);
//    }
}

bool MahjongBoard::isOnLeft(MahjongBoardLayoutItem *tile1, MahjongBoardLayoutItem *tile2)
{
    return ((tile1->x() - 2 == tile2->x()) &&
            (tile1->y() == tile2->y() || tile1->y() + 1 == tile2->y() || tile1->y() - 1 == tile2->y()) &&
            (tile1->d() == tile2->d()));
}

bool MahjongBoard::isOnRight(MahjongBoardLayoutItem *tile1, MahjongBoardLayoutItem *tile2)
{
    return ((tile1->x() + 2 == tile2->x()) &&
            (tile1->y() == tile2->y() || tile1->y() + 1 == tile2->y() || tile1->y() - 1 == tile2->y()) &&
            (tile1->d() == tile2->d()));
}

bool MahjongBoard::isOnTop(MahjongBoardLayoutItem *tile1, MahjongBoardLayoutItem *tile2)
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

bool MahjongBoard::canRemove(MahjongTileEntity *tile)
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

bool MahjongBoard::canBegin(MahjongBoardLayoutItem *tile)
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

int MahjongBoard::countCombinations()
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

void MahjongBoard::removeTiles(MahjongTileEntity *tile1, MahjongTileEntity *tile2)
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
