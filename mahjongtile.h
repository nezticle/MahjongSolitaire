#ifndef MAHJONGTILEENTITY_H
#define MAHJONGTILEENTITY_H

#include <QtCore/QObject>
#include <QtGui/QVector3D>

#include <Qt3DCore/QEntity>

namespace Qt3DCore {
    class QTransform;
}

namespace Qt3DRender {
    class QPickEvent;
}

class MahjongBoardLayoutItem;

class MahjongBoard;
class MahjongTile : public Qt3DCore::QEntity
{
    Q_OBJECT
    Q_PROPERTY(QVector3D translate READ translate WRITE setTranslate NOTIFY translateChanged)
    Q_PROPERTY(QVector3D scale READ scale WRITE setScale NOTIFY scaleChanged)
    Q_PROPERTY(bool selected READ isSelected WRITE setSelected NOTIFY selectedChanged)
    Q_PROPERTY(QString faceValue READ faceValue WRITE setFaceValue NOTIFY faceValueChanged)

public:
    enum TileFace {
        Empty = 0,
        Bamboo1,
        Bamboo2,
        Bamboo3,
        Bamboo4,
        Bamboo5,
        Bamboo6,
        Bamboo7,
        Bamboo8,
        Bamboo9,
        Character1,
        Character2,
        Character3,
        Character4,
        Character5,
        Character6,
        Character7,
        Character8,
        Character9,
        Coin1,
        Coin2,
        Coin3,
        Coin4,
        Coin5,
        Coin6,
        Coin7,
        Coin8,
        Coin9,
        Dragon1,
        Dragon2,
        Dragon3,
        Wind1,
        Wind2,
        Wind3,
        Wind4,
        Flower1,
        Flower2,
        Flower3,
        Flower4,
        Season1,
        Season2,
        Season3,
        Season4
    };

    MahjongTile(MahjongBoard *board);

    bool isSelected() const;
    QString faceValue() const;
    QVector3D translate() const;
    //QVector3D globalTranslate() const;
    QVector3D scale() const;
    //QVector3D globalScale() const;
    TileFace face() const;

    MahjongBoardLayoutItem *boardPosition() const;
    void setBoardPosition(MahjongBoardLayoutItem *position);

    static float tileWidth();
    static float tileHeight();
    static float tileDepth();

public slots:
    void setSelected(bool selected);
    void setFaceValue(const QString &value);
    void setTranslate(QVector3D translate);
    void setScale(QVector3D scale);

private slots:
    void processTouched(Qt3DRender::QPickEvent *event);

signals:
    void selectedChanged(bool selected);
    void faceValueChanged(QString faceValue);
    void translateChanged(QVector3D translate);
    void scaleChanged(QVector3D scale);

private:
    MahjongBoardLayoutItem *m_boardPosition = nullptr;
    QString m_faceValue;
    bool m_selected = false;
    MahjongBoard *m_board;
    Qt3DCore::QTransform *m_transform;

    static float s_tileWidth;
    static float s_tileHeight;
    static float s_tileDepth;
};

#endif // MAHJONGTILEENTITY_H
