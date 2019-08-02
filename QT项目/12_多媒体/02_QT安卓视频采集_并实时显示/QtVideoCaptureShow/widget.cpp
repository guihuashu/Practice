#include "widget.h"
#include "ui_widget.h"
#include <iostream>
#include <thread>
#include <QThread>

//using namespace std;

static FFM _ffm;
static AVFrame *_yuv420p = NULL;
static AVFrame *_rgb24 = NULL;
static QList <QImage *> imgList;


//public:
//    Task(QVideoFrame &frame, AVFrame *rgb24) {
//        th
//    }
//    void run()
//    {

//    }
//private:
//    QVideoFrame frame;
//    AVFrame *rgb24;
//};


void runPaint(QPainter *p, QImage img)
{
    p->drawImage(0,0,img);
}


Widget::~Widget()
{
    delete ui;
    delete _camera;
}


Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    imgList.clear();
    useCameraInfo = QCameraInfo::availableCameras().at(0);
    pool = QThreadPool::globalInstance();
    configVideoCamera();
}


void Widget::configVideoCamera()
{
    // 相机
    _camera = new QCamera(useCameraInfo);
    viewfinder = new QCameraViewfinder();   // 这个窗口在安卓中是不支持显示的
    viewfinder->close();
    _camera->setViewfinder(viewfinder);
    _probe = new QVideoProbe();
    _probe->setSource(_camera);
    // 在槽函数中捕获视频帧
    connect(_probe, &QVideoProbe::videoFrameProbed, this, &Widget::newVideoFrame);
    // 当相机成功加载后,在槽函数中设置相机
    connect(_camera, &QCamera::stateChanged, this, &Widget::stateChanged);

    // 设置相机
    _camera->setCaptureMode(QCamera::CaptureVideo);
    _camera->start();

}

int Widget::goNv21toRgb24(QVideoFrame &frame, AVFrame * &rgb24)
{
    char buf[100] = {0};
    if (frame.pixelFormat() != QVideoFrame::Format_NV21) {
        qWarning()<<"only support Format_NV21";
        return -1;
    }
    // 分配yuv420p
    if (!rgb24) {
        rgb24 = av_frame_alloc();
        //yuv420p->format = AV_PIX_FMT_YUV420P;
        rgb24->format = AV_PIX_FMT_RGB24;
        rgb24->width = frame.width();
        rgb24->height = frame.height();
        rgb24->pts = 0;
        if (av_frame_get_buffer(rgb24, 24))	{   // 32字节对其
            qWarning()<<"av_frame_get_buffer err";
            return -1;
        }
    }
#if 0
    int i=0;
    while (frame.bits(i)) {
        sprintf(buf, "frame.bits(%d)=%p, bytesPerLine=%d", \
                i, (unsigned char *)frame.bits(i), frame.bytesPerLine(i));
        qWarning()<<buf;
        i++;
    }
#endif
    return _ffm.NV21toRgb24(frame, rgb24);
}

void Widget::paintEvent(QPaintEvent *event)
{
    QPainter p(this);
    p.drawImage(0,0,_img);
}



void Widget::newVideoFrame(const QVideoFrame &frame)
{
    int ret;
    static int i=0;
    //if (frame.isValid())
        //qWarning()<<"newVideoFrame";
    QVideoFrame curFrame = frame;
    curFrame.map(QAbstractVideoBuffer::ReadWrite);


#ifdef ANDROID
    if (frame.pixelFormat() != QVideoFrame::Format_NV21) {
        qWarning()<<"only support Format_NV21";
        return;
    }
    //CUR;
    //std::thread th(run, curFrame, _rgb24);
    //th.detach();
    ret = goNv21toRgb24(curFrame, _rgb24);

    qInfo()<<"ret2= "<<ret;

    // _rgb24是交叉存取模型, 只有一个平面
    //ui->label->setPixmap(QPixmap::fromImage(img));
    //i++;
    //if (i == 5) {
    _img = QImage(_rgb24->data[0], _rgb24->width, _rgb24->height, QImage::Format_RGB888);
        //i = 0;
    update();
    //}
#endif
}

void Widget::timerend()
{
    //this->update();
}

void Widget::stateChanged(QCamera::State state)
{
    if (QCamera::ActiveState == state)
    {
        QList<QCameraViewfinderSettings> list = _camera->supportedViewfinderSettings();
        for (int i=0; i < list.size(); i++){
            QCameraViewfinderSettings set = list.at(i);
            if (set.resolution() == QSize(640,480) \
               &&  (set.maximumFrameRate() <=15) \
               &&  (set.pixelFormat() == QVideoFrame::Format_NV21)){
                qWarning()<<set.minimumFrameRate();
                qWarning()<<set.maximumFrameRate();
                qWarning()<<set.resolution().width()<<"x"<<set.resolution().height();
                _camera->setViewfinderSettings(set);
            }
        }
    }
}








