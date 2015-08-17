#ifndef MAHJONGTILEENTITY_H
#define MAHJONGTILEENTITY_H

#include <QtCore/QObject>
#include <QtGui/QVector3D>

#include <Qt3DCore/QEntity>

class MahjongBoardLayoutItem;

namespace Qt3D {
    class QMesh;
    class QTranslateTransform;
    class QRotateTransform;
    class QMaterial;
    class QScaleTransform;
}

class MahjongTileEntity : public Qt3D::QEntity
{
    Q_OBJECT
    Q_PROPERTY(QVector3D translate READ translate WRITE setTranslate NOTIFY translateChanged)
    Q_PROPERTY(QVector3D rotation READ rotation WRITE setRotation NOTIFY rotationChanged)
    Q_PROPERTY(QVector3D scale READ scale WRITE setScale NOTIFY scaleChanged)
    Q_PROPERTY(bool selected READ isSelected WRITE setSelected NOTIFY selectedChanged)
    Q_PROPERTY(QString faceValue READ faceValue WRITE setFaceValue NOTIFY faceValueChanged)
    Q_PROPERTY(bool visible READ visible WRITE setVisible NOTIFY visibleChanged)

public:
    MahjongTileEntity(Qt3D::QNode *parent = 0);

    bool isSelected() const;
    QString faceValue() const;
    QVector3D translate() const;
    QVector3D rotation() const;
    QVector3D scale() const;

    MahjongBoardLayoutItem *boardPosition() const;
    void setBoardPosition(MahjongBoardLayoutItem *position);

    bool visible() const;

public slots:
    void setSelected(bool selected);
    void setFaceValue(const QString &value);
    void setTranslate(QVector3D translate);
    void setRotation(QVector3D rotation);
    void setScale(QVector3D scale);
    void setVisible(bool visible);

signals:
    void selectedChanged(bool selected);
    void faceValueChanged(QString faceValue);
    void translateChanged(QVector3D translate);
    void rotationChanged(QVector3D rotation);
    void scaleChanged(QVector3D scale);
    void visibleChanged(bool visible);

private:
    MahjongBoardLayoutItem *m_boardPosition;
    QString m_faceValue;
    bool m_selected;

    Qt3D::QTranslateTransform *m_translate;
    Qt3D::QRotateTransform *m_rotationX;
    Qt3D::QRotateTransform *m_rotationY;
    Qt3D::QRotateTransform *m_rotationZ;
    Qt3D::QScaleTransform *m_scale;
    Qt3D::QMesh *m_mesh;
    Qt3D::QMaterial *m_material;
    bool m_visible;
};

#endif // MAHJONGTILEENTITY_H
