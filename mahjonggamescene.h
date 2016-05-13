#ifndef MAHJONGGAMESCENE_H
#define MAHJONGGAMESCENE_H

#include <QtCore/QObject>
#include <QtCore/QSize>

#include <Qt3DCore/QEntity>

class MahjongBoardLayoutItem;
class MahjongTileEntity;
class MahjongBoard;

namespace Qt3DRender {
    class QCamera;
}

class MahjongGameScene : public QObject
{
    Q_OBJECT
    Q_PROPERTY(Qt3DCore::QEntity* rootEntity READ rootEntity CONSTANT)
    Q_PROPERTY(QSize viewportSize READ viewportSize WRITE setViewportSize NOTIFY viewportSizeChanged)
    Q_PROPERTY(Qt3DRender::QCamera* camera READ camera CONSTANT)
public:
    explicit MahjongGameScene(QObject *parent = 0);
    ~MahjongGameScene();

    Qt3DCore::QEntity *rootEntity() const;
    QSize viewportSize() const;
    Qt3DRender::QCamera *camera() const;

signals:
    void viewportSizeChanged(QSize viewportSize);

public slots:
    void setViewportSize(QSize viewportSize);
    void newGame();
    void processInput(int x, int y);

private:
    Qt3DCore::QEntity* m_rootEntity;
    QSize m_viewportSize;
    Qt3DRender::QCamera* m_camera;
    MahjongBoard *m_mahjongBoard;
};

#endif // MAHJONGGAMESCENE_H
