import QtQuick 2.0
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3

Item {
    id: item1
    width: 1208
    height: 720

    Rectangle {
        id: toolArea
        width: 250
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 0
        anchors.top: parent.top
        anchors.topMargin: 0
        anchors.left: parent.left
        anchors.leftMargin: 0
        color: "white"

        ColumnLayout {
            id: columnLayout
            anchors.right: parent.right
            anchors.left: parent.left
            anchors.top: parent.top
            anchors.rightMargin: 8
            anchors.leftMargin: 8
            anchors.topMargin: 8

            Label {
                id: label
                text: qsTr("Mahjong Debug")
                font.family: "Tahoma"
                font.pointSize: 24
                Layout.alignment: Qt.AlignHCenter | Qt.AlignTop
            }

            GroupBox {
                id: gameControls
                width: 200
                height: 200
                Layout.alignment: Qt.AlignHCenter | Qt.AlignTop
                Layout.fillWidth: true
                title: qsTr("Game Controls")

                ColumnLayout {
                    id: columnLayout1
                    anchors.fill: parent

                    RowLayout {
                        id: rowLayout1
                        width: 100
                        height: 100
                        Layout.fillWidth: true

                        Button {
                            id: newGameButton
                            text: qsTr("New Game")
                            Layout.fillWidth: true
                            Layout.alignment: Qt.AlignHCenter | Qt.AlignTop
                            onClicked: {
                                mahjongGameboard.mahjongGame.newGame();
                            }
                        }

                        Button {
                            id: resetButton
                            text: qsTr("Reset")
                            onClicked: {
                                mahjongGameboard.mahjongGame.reset();
                            }
                        }
                    }

                    RowLayout {
                        id: rowLayout
                        width: 100
                        height: 100
                        Layout.fillWidth: true

                        Label {
                            id: label1
                            text: qsTr("Game Seed")
                        }

                        TextField {
                            id: textField
                            text: mahjongGameboard.mahjongGame.seed
                            horizontalAlignment: Text.AlignRight
                            inputMask: "0000000000"
                            placeholderText: "(seed)"
                            Layout.fillWidth: true
                        }
                    }

                }
            }

            GroupBox {
                id: cameraControls
                width: 200
                height: 200
                Layout.alignment: Qt.AlignHCenter | Qt.AlignTop
                Layout.fillWidth: true
                title: qsTr("Camera Controls")

                ColumnLayout {
                    id: columnLayout2
                    anchors.bottom: parent.bottom
                    anchors.bottomMargin: 0
                    anchors.right: parent.right
                    anchors.left: parent.left
                    anchors.top: parent.top

                    GroupBox {
                        id: groupBox
                        Layout.fillWidth: true
                        title: qsTr("Position")

                        ColumnLayout {
                            id: columnLayout3
                            anchors.right: parent.right
                            anchors.rightMargin: 0
                            anchors.left: parent.left
                            anchors.leftMargin: 0
                            anchors.top: parent.top
                            anchors.topMargin: 0

                            RowLayout {
                                id: rowLayout4
                                Label {
                                    id: label4
                                    width: 50
                                    text: qsTr("X  ") + xPosSlider.value
                                    elide: Text.ElideRight
                                    Layout.maximumWidth: 50
                                    Layout.minimumWidth: 50
                                }

                                Slider {
                                    id: xPosSlider
                                    stepSize: 0.01
                                    value: mahjongGameboard.mahjongGame.camera.position.x
                                    to: 200
                                    from: -200
                                    Layout.fillWidth: true
                                    onValueChanged: {
                                        mahjongGameboard.mahjongGame.camera.position.x = value
                                    }
                                }
                                Layout.fillWidth: true
                            }

                            RowLayout {
                                id: rowLayout5
                                Label {
                                    id: label5
                                    width: 50
                                    text: qsTr("Y  ") + yPosSlider.value
                                    Layout.maximumWidth: 50
                                    Layout.minimumWidth: 50
                                    elide: Text.ElideRight
                                }

                                Slider {
                                    id: yPosSlider
                                    stepSize: 0.01
                                    value: mahjongGameboard.mahjongGame.camera.position.y
                                    to: 200
                                    from: -200
                                    Layout.fillWidth: true
                                    onValueChanged: {
                                        mahjongGameboard.mahjongGame.camera.position.y = value
                                    }
                                }
                                Layout.fillWidth: true
                            }

                            RowLayout {
                                id: rowLayout6
                                Label {
                                    id: label6
                                    width: 50
                                    text: qsTr("Z  ") + zPosSlider.value
                                    Layout.maximumWidth: 50
                                    Layout.minimumWidth: 50
                                    elide: Text.ElideRight
                                }

                                Slider {
                                    id: zPosSlider
                                    stepSize: 0.01
                                    value: mahjongGameboard.mahjongGame.camera.position.z
                                    from: -200
                                    to: 200
                                    Layout.fillWidth: true
                                    onValueChanged: {
                                        mahjongGameboard.mahjongGame.camera.position.z = value
                                    }
                                }
                                Layout.fillWidth: true
                            }



                        }
                    }

                    GroupBox {
                        id: groupBox1
                        width: 200
                        height: 200
                        Layout.fillWidth: true
                        title: qsTr("Field of View")

                        RowLayout {
                            id: rowLayout2
                            anchors.fill: parent

                            Label {
                                id: label2
                                text: fovSlider.value
                                Layout.minimumWidth: 50
                                elide: Text.ElideRight
                            }

                            Slider {
                                id: fovSlider
                                value: mahjongGameboard.mahjongGame.camera.fieldOfView
                                from: 10
                                stepSize: 1
                                to: 180
                                Layout.fillWidth: true
                                onValueChanged: {
                                    mahjongGameboard.mahjongGame.camera.fieldOfView = value;
                                }
                            }
                        }
                    }

                    GroupBox {
                        id: groupBox2
                        width: 200
                        height: 200
                        Layout.fillWidth: true
                        title: qsTr("Exposure")

                        RowLayout {
                            id: rowLayout3
                            anchors.fill: parent

                            Label {
                                id: label3
                                text: exposureSlider.value
                                Layout.preferredWidth: 50
                                elide: Text.ElideRight
                            }

                            Slider {
                                id: exposureSlider
                                stepSize: 0.01
                                value: mahjongGameboard.mahjongGame.camera.exposure
                                to: 3
                                from: 0.5
                                Layout.fillWidth: true
                                onValueChanged: {
                                    mahjongGameboard.mahjongGame.camera.exposure = value
                                }
                            }
                        }
                    }
                }
            }

            GroupBox {
                id: renderControls
                width: 200
                height: 200
                Layout.fillWidth: true
                title: qsTr("Render Controls")
            }

        }
    }

    Item {
        id: gameArea
        anchors.right: parent.right
        anchors.rightMargin: 0
        anchors.left: toolArea.right
        anchors.leftMargin: 0
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 0
        anchors.top: parent.top
        anchors.topMargin: 0

        MahjongGameboard {
            id: mahjongGameboard
            anchors.fill: parent
        }
    }

}
