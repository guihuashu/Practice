import QtQuick 2.9
import QtQuick.Window 2.2
import QtQuick.Controls 2.5
Window {
    objectName: qsTr("root")
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")
    Button{
        objectName: qsTr("button")
        id:button
        text: "Quit";
        anchors.centerIn: parent
    }
    TextField {
        id: textField
        objectName: qsTr("text")
        function changeText(string){
            textField.text = string;
        }
        font.pixelSize: 50;
        text: qsTr("text")
        onAccepted: {
            console.log("onAccepted");

        }
    }
}
