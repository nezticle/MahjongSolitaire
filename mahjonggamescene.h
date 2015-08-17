#ifndef MAHJONGGAMESCENE_H
#define MAHJONGGAMESCENE_H

#include <QtCore/QObject>
#include <QtCore/QSize>

#include <Qt3DCore/QEntity>

class MahjongBoardLayoutItem;
class MahjongTileEntity;
class MahjongBoardArea;

namespace Qt3D {
    class QCamera;
}

class MahjongGameScene : public QObject
{
    Q_OBJECT
    Q_PROPERTY(Qt3D::QEntity* rootEntity READ rootEntity CONSTANT)
    Q_PROPERTY(QSize viewportSize READ viewportSize WRITE setViewportSize NOTIFY viewportSizeChanged)
public:
    explicit MahjongGameScene(QObject *parent = 0);
    ~MahjongGameScene();

    Qt3D::QEntity *rootEntity() const;
    QSize viewportSize() const;

signals:
    void viewportSizeChanged(QSize viewportSize);

public slots:
    void setViewportSize(QSize viewportSize);
    void newGame();

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

    Qt3D::QEntity* m_rootEntity;
    QSize m_viewportSize;
    Qt3D::QCamera* m_camera;

    //Mahjong Game Properties
    int m_gameSeed;
    QString m_layout;
    float m_tileWidth;
    float m_tileHeight;
    float m_tileDepth;

    QVector<MahjongTileEntity*> m_tiles;
    QVector<MahjongBoardLayoutItem*> m_boardTiles;

    MahjongTileEntity *m_firstTile;
    int m_tilesLeft;
    QString m_hints;

    MahjongBoardArea *m_mahjongBoardArea;
    Qt3D::QEntity *m_hiddenNodeRoot;
};

#endif // MAHJONGGAMESCENE_H
