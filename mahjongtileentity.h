#ifndef MAHJONGTILEENTITY_H
#define MAHJONGTILEENTITY_H

#include <QtCore/QObject>
#include <QtGui/QVector3D>

#include <Qt3DCore/QEntity>

class MahjongBoardLayoutItem;
class MahjongTilefaceEntity;

namespace Qt3DCore {
    class QTransform;
}

namespace Qt3DRender {
    class QMesh;
    class QMaterial;
    class QPickEvent;
}

class MahjongBoard;
class MahjongTileEntity : public Qt3DCore::QEntity
{
    Q_OBJECT
    Q_PROPERTY(QVector3D translate READ translate WRITE setTranslate NOTIFY translateChanged)
    Q_PROPERTY(QVector3D scale READ scale WRITE setScale NOTIFY scaleChanged)
    Q_PROPERTY(bool selected READ isSelected WRITE setSelected NOTIFY selectedChanged)
    Q_PROPERTY(QString faceValue READ faceValue WRITE setFaceValue NOTIFY faceValueChanged)
    Q_PROPERTY(bool visible READ visible WRITE setVisible NOTIFY visibleChanged)

public:
    MahjongTileEntity(MahjongBoard *board);

    bool isSelected() const;
    QString faceValue() const;
    QVector3D translate() const;
    QVector3D scale() const;

    MahjongBoardLayoutItem *boardPosition() const;
    void setBoardPosition(MahjongBoardLayoutItem *position);

    bool visible() const;

    static float tileWidth();
    static float tileHeight();
    static float tileDepth();

public slots:
    void setSelected(bool selected);
    void setFaceValue(const QString &value);
    void setTranslate(QVector3D translate);
    void setScale(QVector3D scale);
    void setVisible(bool visible);

private slots:
    void processTouched(Qt3DRender::QPickEvent*event);

signals:
    void selectedChanged(bool selected);
    void faceValueChanged(QString faceValue);
    void translateChanged(QVector3D translate);
    void scaleChanged(QVector3D scale);
    void visibleChanged(bool visible);

private:

    MahjongBoardLayoutItem *m_boardPosition;
    QString m_faceValue;
    bool m_selected;

    Qt3DCore::QTransform *m_transform;
    bool m_visible;
    MahjongTilefaceEntity *m_tileFace;
    MahjongBoard *m_board;


    static float s_tileWidth;
    static float s_tileHeight;
    static float s_tileDepth;
};

#endif // MAHJONGTILEENTITY_H
