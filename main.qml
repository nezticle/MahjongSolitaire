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

    MahjongGameboard {
        id: gameboard
        anchors.fill: parent
        inputSource: window
        focus: true;
    }

    Rectangle {
        anchors.top: parent.top
        anchors.right: parent.right
        height: 50
        width: 100
        MouseArea {
            anchors.fill: parent
            onClicked: gameboard.mahjongGame.newGame();
        }

        Text {
            id: name
            text: qsTr("New Game")
            anchors.centerIn: parent
        }
    }
}

