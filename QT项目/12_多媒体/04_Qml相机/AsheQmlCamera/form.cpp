#include "form.h"
#include "ui_form.h"

Form::Form(QQmlApplicationEngine *engine,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Form)
{
    ui->setupUi(this);

    _paintWidget = new PaintWidget(ui->page_2);
    _engine = engine;
    QList<QObject *> objs = _engine->rootObjects();
    qDebug()<<objs.size();
    for (int i=0; i < objs.size(); i++) {
        if (objs.at(i)->objectName() == "root"){
            _root  = objs.at(i);
            break;
        }
    }

    // 设置相机
    _qmlCamera = _root->findChild<QObject *>("QmlCamera");
    _camera = qvariant_cast<QCamera*>(_qmlCamera->property("mediaObject"));
    _proble = new QVideoProbe();
    _proble->setSource(_camera);
    connect(_proble, &QVideoProbe::videoFrameProbed, this, &Form::newVideoFrame);

    dump(ffm.printConf());





    qDebug()<<_root;
    qDebug()<<_qmlCamera;
    qDebug()<<_camera;
    qDebug()<<_proble;
}

Form::~Form()
{
    delete ui;
}

QImage Form::videoFrameToImg(QVideoFrame &frame)
{
    dump(QString("QVideoFrame fmt: %1").arg(frame.pixelFormat()));
    // 如果安卓摄像头采集格式为Format_NV21或者Format_YV12, 将会失败
    QImage::Format fmt = QVideoFrame::imageFormatFromPixelFormat(frame.pixelFormat());
    dump(QString("QImage fmt: %1").arg(fmt));
    if (fmt != QImage::Format_Invalid)
        return QImage(frame.bits(), frame.width(), frame.width(), fmt);
    else {
        int nbytes = frame.mappedBytes();
        return QImage::fromData(frame.bits(), nbytes);
    }
}

void Form::newVideoFrame(const QVideoFrame &frame)
{
    QVideoFrame f = frame;
    char buf[100] = {0};
    if (!f.map(QAbstractVideoBuffer::ReadWrite)) {
        dump("frame map err");
        return;
    }
    dump(QString("mappedBytes: %1").arg(f.mappedBytes()));
    if (!f.isValid()){
        dump("f.isValid()");
        return;
    }
#if 0
    QImage img = videoFrameToImg(f);
    if (img.isNull()){
        dump("img.isNull");
        return;
    }
    _paintWidget->paintFrame(img);
#endif
    if (f.pixelFormat() != QVideoFrame::Format_NV21) {
        dump(QString("cannot support fmt: %1").arg(f.pixelFormat()));
        return;
    }


}

void Form::dump(QString s)
{
    ui->textBrowser->append(s);
}


