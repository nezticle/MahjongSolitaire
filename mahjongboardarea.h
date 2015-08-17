#ifndef MAHJONGBOARDAREA_H
#define MAHJONGBOARDAREA_H

#include <QtGui/QVector3D>
#include <Qt3DCore/QEntity>

namespace Qt3D {
    class QTranslateTransform;
    class QCuboidMesh;
}

class MahjongBoardArea : public Qt3D::QEntity
{
    Q_OBJECT
    Q_PROPERTY(QVector3D baseCenter READ baseCenter WRITE setBaseCenter NOTIFY baseCenterChanged)
    Q_PROPERTY(QVector3D size READ size WRITE setSize NOTIFY sizeChanged)
public:
    MahjongBoardArea(Qt3D::QNode *parent = 0);
    QVector3D baseCenter() const;
    QVector3D size() const;

public slots:
    void setBaseCenter(QVector3D baseCenter);
    void setSize(QVector3D size);

signals:
    void baseCenterChanged(QVector3D baseCenter);
    void sizeChanged(QVector3D size);

private:
    QVector3D m_baseCenter;
    QVector3D m_size;
    Qt3D::QTranslateTransform *m_translation;
    Qt3D::QCuboidMesh *m_mesh;
};

#endif // MAHJONGBOARDAREA_H
