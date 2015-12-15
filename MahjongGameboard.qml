import com.bsquask.Mahjong 1.0
import QtQuick.Scene3D 2.0
import QtQuick 2.5
import Qt3D.Core 2.0

Item {
    id: gameboard

    property alias mahjongGame: gameScene

    Scene3D {
        id: sceneItem
        anchors.fill: gameboard
        entity: gameScene.rootEntity
        //aspects: "input"
    }

//    Configuration  {
//        controlledCamera: gameScene.camera
//    }

    MahjongGameScene {
        id: gameScene
        viewportSize: Qt.size(sceneItem.width, sceneItem.height);
    }
}
