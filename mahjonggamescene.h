#ifndef MAHJONGGAMESCENE_H
#define MAHJONGGAMESCENE_H

#include <QtCore/QObject>
#include <QtCore/QSize>

#include <Qt3DCore/QEntity>

class MahjongBoardLayoutItem;
class MahjongTileEntity;
class MahjongBoard;

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
    void processInput(int x, int y);

private:
    Qt3D::QEntity* m_rootEntity;
    QSize m_viewportSize;
    Qt3D::QCamera* m_camera;
    MahjongBoard *m_mahjongBoard;
};

#endif // MAHJONGGAMESCENE_H
