#ifndef MAHJONGGAMESCENE_H
#define MAHJONGGAMESCENE_H

#include <QtCore/QObject>
#include <QtCore/QSize>

#include <Qt3DCore/QEntity>

class MahjongBoardLayoutItem;
class MahjongTile;
class MahjongBoard;
class QQuickWindow;

namespace Qt3DRender {
    class QCamera;
}

namespace Qt3DInput {
    class QInputSettings;
}

class MahjongGameScene : public QObject
{
    Q_OBJECT
    Q_PROPERTY(Qt3DCore::QEntity* rootEntity READ rootEntity CONSTANT)
    Q_PROPERTY(QSize viewportSize READ viewportSize WRITE setViewportSize NOTIFY viewportSizeChanged)
    Q_PROPERTY(Qt3DRender::QCamera* camera READ camera CONSTANT)
    Q_PROPERTY(QQuickWindow* inputSource READ inputSource WRITE setInputSource NOTIFY inputSourceChanged)
public:
    explicit MahjongGameScene(QObject *parent = 0);

    Qt3DCore::QEntity *rootEntity() const;
    QSize viewportSize() const;
    Qt3DRender::QCamera *camera() const;
    QQuickWindow* inputSource() const;

signals:
    void viewportSizeChanged(QSize viewportSize);
    void inputSourceChanged(QQuickWindow* inputSource);

public slots:
    void setViewportSize(QSize viewportSize);
    void newGame();
    void setInputSource(QQuickWindow* inputSource);

private:
    Qt3DCore::QEntity* m_rootEntity;
    QSize m_viewportSize;
    Qt3DRender::QCamera* m_camera;
    MahjongBoard *m_mahjongBoard;
    Qt3DInput::QInputSettings *m_inputSettings;
    QQuickWindow* m_inputSource = nullptr;
};

#endif // MAHJONGGAMESCENE_H
