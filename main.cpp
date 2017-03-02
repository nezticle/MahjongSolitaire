#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include <QtQuick>

#include "mahjonggamescene.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    app.setOrganizationName("Bsquask");
    app.setOrganizationDomain("bsquask.com");
    app.setApplicationName("MahjongSolitaire");

//    QSurfaceFormat format;
//    if (QOpenGLContext::openGLModuleType() == QOpenGLContext::LibGL) {
//        format.setVersion(4, 2);
//        format.setProfile(QSurfaceFormat::CoreProfile);
//    }
//    format.setDepthBufferSize( 24 );
//    format.setStencilBufferSize(8);
//    format.setSamples(0);
//    QSurfaceFormat::setDefaultFormat(format);

    qmlRegisterType<MahjongGameScene>("com.bsquask.Mahjong", 1, 0, "MahjongGameScene");

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    return app.exec();
}
