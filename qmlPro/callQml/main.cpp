#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QDebug>
#include <like.h>

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    // 找到根对象
    QList<QObject *> list = engine.rootObjects();
    QObject *root;
    QObject *button;
    QObject *textField;
    Like like(&engine);

    //qInfo()<<list.size();
    for (int i=0; i <list.size();i++){
        QObject *obj = list.at(i);
        if (obj->objectName() == "root")
            root = obj;
    }
    QList<QObject *> children = root->children();
    for (int i=0; i <children.size();i++){
        QObject *obj = children.at(i);
        qDebug()<<obj->objectName();
        if (obj->objectName() == "button")
            button  = obj;
        else if (obj->objectName() == "text")
           textField =  obj;
    }
    QObject::connect(button, SIGNAL(clicked()), &like, SLOT(slot1()));
    qDebug()<<root->metaObject()->className();
    qDebug()<<textField->metaObject()->className();
    qDebug()<<button->metaObject()->className();

    // 调用QMl中对象的函数
    QMetaObject::invokeMethod(textField, "accepted");

    // 设置QMl中对象的属性
    textField->setProperty("text", "asdwq");
    return app.exec();
}
