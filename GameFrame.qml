import QtQuick 2.0

Item {
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
