#ifndef MAHJONGBOARD_H
#define MAHJONGBOARD_H

#include <Qt3DCore/QEntity>
#include <QtGui/QVector3D>

class MahjongBoardLayoutItem;
class MahjongTile;
class MahjongTileMaterial;

namespace Qt3DCore {
    class QTransform;
}

namespace Qt3DRender {
    class QMesh;
    class QAttribute;
    class QBuffer;
}

class MahjongBoard : public Qt3DCore::QEntity
{
    Q_OBJECT
    Q_PROPERTY(QVector3D translate READ translate WRITE setTranslate NOTIFY translateChanged)
    Q_PROPERTY(float scale READ scale WRITE setScale NOTIFY scaleChanged)
public:
    MahjongBoard(Qt3DCore::QNode *parent = 0);
    ~MahjongBoard();

    QVector3D translate() const;
    float scale() const;

    int gameSeed() const;

public slots:
    void newGame(int seed = 0);

    void setTranslate(QVector3D translate);
    void setScale(float scale);

    void checkTileTouched(MahjongTile *tile);

signals:
    void translateChanged(QVector3D translate);
    void scaleChanged(float scale);

private:
    void initTiles();
    void reset();
    void loadLayout();
    void initGame();
    void setupTiles();

    bool isOnLeft(MahjongBoardLayoutItem *tile1, MahjongBoardLayoutItem *tile2) const;
    bool isOnRight(MahjongBoardLayoutItem *tile1, MahjongBoardLayoutItem *tile2) const;
    bool isOnTop(MahjongBoardLayoutItem *tile1, MahjongBoardLayoutItem *tile2) const;

    bool canRemove(MahjongTile *tile) const;
    bool canBegin(MahjongBoardLayoutItem *tile) const;

    int countCombinations();

    void removeTiles(MahjongTile *tile1, MahjongTile *tile2);

    // Render Helpers
    void resetTileBufferData();
    void setupTileInstanceAttributes();
    void updateTileRenderer();
    void setupTextures();

    //Mahjong Game Properties
    int m_gameSeed = 0;
    QString m_layout;

    QVector<MahjongTile*> m_tiles;
    QVector<MahjongBoardLayoutItem*> m_boardTiles;

    MahjongTile *m_firstTile = nullptr;
    int m_tilesLeft = 0;
    QString m_hints;

    struct TileBufferLayout {
        QVector3D pos;
        int isSelected;
        int face;
    };

    Qt3DCore::QTransform *m_transform;
    Qt3DRender::QMesh *m_tileMesh;
    MahjongTileMaterial *m_material;
    Qt3DRender::QBuffer *m_tileInstanceBuffer;
};

#endif // MAHJONGBOARD_H
