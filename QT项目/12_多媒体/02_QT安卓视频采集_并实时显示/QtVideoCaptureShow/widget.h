#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QCamera>
#include <QCameraInfo>
#include <QVideoFrame>
#include <QCameraViewfinder>
#include <QThread>
#include <QPainter>
#include <QTimer>
#include <QVideoProbe>
#include <QDebug>
#include "ffm.h"
#include <QPixmap>
#include <QList>
#include <QThreadPool>
#include <QCameraViewfinderSettings>
namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = nullptr);
    ~Widget();
    void configVideoCamera();
    int goNv21toRgb24(QVideoFrame &frame, AVFrame * &rgb24);
    virtual void paintEvent(QPaintEvent *event);
public slots:
    // 采集到新帧数据
    void newVideoFrame(const QVideoFrame &frame);
    void timerend();
    void stateChanged(QCamera::State state);
private:
    Ui::Widget *ui;
    QCamera *_camera;
    QCameraInfo useCameraInfo;
    QCameraViewfinder *viewfinder;
    QVideoProbe *_probe;
    QImage _img;
    QTimer *timer;
    QThreadPool *pool;
};

#endif // WIDGET_H
