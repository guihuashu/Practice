#include "widget.h"
#include <QApplication>
#include <iostream>
#include <QThread>
#include <thread>
#include <QPixmap>
#include <QDebug>
#include <thread>
using namespace std;

Widget *w;
//static int i;

class Task : public QRunnable
{
    void run()
    {
        w->update();
    }
};

void run()  // 不能再主线程中死循环, 否则没有事件循环(调用update不会刷新界面)
{
    //QThreadPool *pool = QThreadPool::globalInstance();
    //pool->setMaxThreadCount(100);
    //qDebug()<<pool->maxThreadCount();
    QPixmap pix1;
    QPixmap pix2;
    pix1.load(":new/prefix1/1.jpg");
    pix2.load(":new/prefix1/2..png");
    while (1) {
        // 画出第一帧
        w->setPix(pix1);
        w->update();
        QThread::sleep(1);

        // 画出第二帧
        w->setPix(pix2);
        w->update();
        QThread::sleep(1);

    }
}
int main(int argc, char *argv[])
{
    QApplication a(argc, NULL);

    w = new Widget();
    w->show();
    thread th(run);
    return a.exec();
}
