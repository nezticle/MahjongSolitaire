import QtQuick 2.5
import QtQuick.Window 2.2
import Qt.labs.settings 1.0

Window {
    id: window
    visible: true
    width: 1280
    height: 720
    title: "Mahjong Solitaire"
    color: "black"

    Settings {
        property alias x: window.x
        property alias y: window.y
        property alias width: window.width
        property alias height: window.height
    }

    DebugFrame {
        anchors.fill: parent
    }

}

