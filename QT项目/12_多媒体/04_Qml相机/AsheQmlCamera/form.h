#ifndef FORM_H
#define FORM_H

#include <QWidget>
#include <QVideoProbe>
#include <QCamera>
#include <QVideoProbe>
#include <QQmlApplicationEngine>
#include <QPainter>
#include <paintwidget.h>
#include <ffm.h>
namespace Ui {
class Form;
}



class Form : public QWidget
{
    Q_OBJECT

public:
    explicit Form(QQmlApplicationEngine *engine, QWidget *parent = nullptr);
    ~Form();
    void dump(QString s);
    QImage videoFrameToImg(QVideoFrame &frame);

public slots:
    void newVideoFrame(const QVideoFrame &frame);

private:
    Ui::Form *ui;
    QVideoProbe *_probe;
    QObject *_root = NULL;
    QObject *_qmlVideoOutput = NULL;
    QObject *_qmlCamera = NULL;
    QCamera *_camera = NULL;
    QQmlApplicationEngine *_engine=NULL;
    QVideoProbe *_proble = NULL;
    PaintWidget *_paintWidget;
    AVFrame *yuv420p;
    FFM ffm;
};

#endif // FORM_H
