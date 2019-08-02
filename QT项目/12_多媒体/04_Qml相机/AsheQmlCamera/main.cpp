#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <form.h>
#include <QDebug>
#include <QCamera>
#include <QThread>
#include <QApplication>
#include <QApplication>

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    //QGuiApplication app(argc, argv);
    QApplication app(argc, argv);
    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;



    Form *form = new Form(&engine);
    form->show();
    //QThread *th = QThread::create(runForm);
    //th->start();
    return app.exec();
}
