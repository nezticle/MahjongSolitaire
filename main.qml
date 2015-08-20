import QtQuick 2.5
import QtQuick.Window 2.2
import QtQuick.Controls 1.3
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

    MahjongGameboard {
        id: gameboard
        anchors.fill: parent
    }

    Button {
        text: "New Game"
        anchors.top: parent.top
        anchors.right: parent.right
        onClicked: {
            gameboard.mahjongGame.newGame();
        }
    }
}

