import QtQuick 2.9
import QtQuick.Window 2.2
import QtMultimedia 5.8

Window {
    objectName: "root";
    //visible: true;
    visible: false;
    width: 640;
    height: 480;
    title: qsTr("Hello World");

    Camera {
        objectName: "QmlCamera"
        id: camera
    }
    VideoOutput {
        objectName: "VideoOutput"
        source: camera
        anchors.fill: parent
        focus : visible // to receive focus and capture key events when visible
    }
}
