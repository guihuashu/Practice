import QtQuick 2.9
import QtQuick.Window 2.2
import Qt.labs.platform 1.1
import QtQuick.Controls 2.5

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")
    BusyIndicator{
        id:busyIndicator
        anchors.centerIn: parent
        visible: false
    }
    Button {
        id :openBt
        text: "Open"
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.leftMargin: 4
        anchors.bottomMargin:  4
        opacity: 1
        onClicked: {
            console.log("onClicked")
            fileDialog.open()
        }
        z:3
    }
    Text{
        id: statusText
        visible: false
        anchors.centerIn: busyIndicator.anchors.centerIn
    }
    Text {
        id: pathText
        text: qsTr("Path")
        visible: true
        anchors.left: openBt.right
        anchors.leftMargin: 50
        anchors.verticalCenter : openBt.verticalCenter
        color: "red"
    }
    Text {
        id: pathShowText
        //text: qsTr("PIC PATH")
        visible: true
        anchors.left: pathText.right
        anchors.leftMargin: 5
        anchors.verticalCenter : openBt.verticalCenter

        color: parent.color
    }
    FileDialog{
        id: fileDialog
        nameFilters: ["Img(*.jpg *.png)"]
        onAccepted: {
            img.source = fileDialog.currentFile
            pathShowText.text = img.source;
        }
        onRejected: {
            console.log("onRejected")
        }
    }
    Image {
        id: img
        //anchors.fill:parent
        anchors.bottom: openBt.top
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: parent.top
        anchors.bottomMargin: 3
        asynchronous: true

        onStatusChanged: {
            statusText.text = String(img.progress)
            if (img.progress === 0) {
                busyIndicator.running = false
                busyIndicator.visible = true
                statusText.visible = true
            }
            else if (img.progress === 1){
                busyIndicator.running = false
                busyIndicator.visible = false
                statusText.visible = false
            }
            else {
                busyIndicator.running = true
                busyIndicator.visible = true
                statusText.visible = true
            }
        }
    }
}
