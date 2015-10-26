#ifndef TABLEENTITY_H
#define TABLEENTITY_H

#include <Qt3DCore/QEntity>

namespace Qt3DCore {
    class QTranslateTransform;
    class QRotateTransform;
    class QScaleTransform;
}

namespace Qt3DRender {
    class QMesh;
}

class TableEntity : public Qt3DCore::QEntity
{
    Q_OBJECT
    Q_PROPERTY(float x READ x WRITE setX NOTIFY xChanged)
    Q_PROPERTY(float y READ y WRITE setY NOTIFY yChanged)
    Q_PROPERTY(float z READ z WRITE setZ NOTIFY zChanged)
    Q_PROPERTY(float rotationX READ rotationX WRITE setRotationX NOTIFY rotationXChanged)
    Q_PROPERTY(float rotationY READ rotationY WRITE setRotationY NOTIFY rotationYChanged)
    Q_PROPERTY(float rotationZ READ rotationZ WRITE setRotationZ NOTIFY rotationZChanged)
    Q_PROPERTY(float scale READ scale WRITE setScale NOTIFY scaleChanged)
public:
    TableEntity(Qt3DCore::QNode *parent = 0);

    float x() const;
    float y() const;
    float z() const;

    float rotationX() const;
    float rotationY() const;
    float rotationZ() const;

    float scale() const;

public slots:
    void setX(float x);
    void setY(float y);
    void setZ(float z);

    void setRotationX(float rotationX);
    void setRotationY(float rotationY);
    void setRotationZ(float rotationZ);

    void setScale(float scale);

signals:
    void xChanged(float x);
    void yChanged(float y);
    void zChanged(float z);

    void rotationXChanged(float rotationX);
    void rotationYChanged(float rotationY);
    void rotationZChanged(float rotationZ);
    void scaleChanged(float scale);

private:
    Qt3DCore::QTranslateTransform *m_translate;
    Qt3DCore::QRotateTransform *m_rotationX;
    Qt3DCore::QRotateTransform *m_rotationY;
    Qt3DCore::QRotateTransform *m_rotationZ;
    Qt3DCore::QScaleTransform *m_scale;
    Qt3DRender::QMesh *m_mesh;
};

#endif // TABLEENTITY_H
