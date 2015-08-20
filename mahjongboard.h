#ifndef MAHJONGBOARD_H
#define MAHJONGBOARD_H

#include <Qt3DCore/QEntity>
#include <QtGui/QVector3D>

class MahjongBoardLayoutItem;
class MahjongTileEntity;

namespace Qt3D {
    class QTranslateTransform;
    class QScaleTransform;
}

class MahjongBoard : public Qt3D::QEntity
{
    Q_OBJECT
    Q_PROPERTY(QVector3D translate READ translate WRITE setTranslate NOTIFY translateChanged)
    Q_PROPERTY(float scale READ scale WRITE setScale NOTIFY scaleChanged)
public:
    MahjongBoard(Qt3D::QNode *parent = 0);
    ~MahjongBoard();

    QVector3D translate() const;
    float scale() const;

public slots:
    void newGame();

    void setTranslate(QVector3D translate);
    void setScale(float scale);

signals:
    void translateChanged(QVector3D translate);
    void scaleChanged(float scale);

private:
    void initTiles();
    void loadLayout();
    void initGame();
    void setupTitles();

    bool isOnLeft(MahjongBoardLayoutItem *tile1, MahjongBoardLayoutItem *tile2);
    bool isOnRight(MahjongBoardLayoutItem *tile1, MahjongBoardLayoutItem *tile2);
    bool isOnTop(MahjongBoardLayoutItem *tile1, MahjongBoardLayoutItem *tile2);

    bool canRemove(MahjongTileEntity *tile);
    bool canBegin(MahjongBoardLayoutItem *tile);

    int countCombinations();

    void removeTiles(MahjongTileEntity *tile1, MahjongTileEntity *tile2);

    //Mahjong Game Properties
    int m_gameSeed;
    QString m_layout;

    QVector<MahjongTileEntity*> m_tiles;
    QVector<MahjongBoardLayoutItem*> m_boardTiles;

    MahjongTileEntity *m_firstTile;
    int m_tilesLeft;
    QString m_hints;

    Qt3D::QEntity *m_hiddenNodeRoot;

    Qt3D::QTranslateTransform *m_translate;
    Qt3D::QScaleTransform *m_scale;

};

#endif // MAHJONGBOARD_H
