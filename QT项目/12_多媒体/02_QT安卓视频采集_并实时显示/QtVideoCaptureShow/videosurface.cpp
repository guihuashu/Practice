#include "videosurface.h"
#include <QDebug>

VideoSurface::VideoSurface(QList<QVideoFrame::PixelFormat> pixFmtList, QObject *parent)
    : QAbstractVideoSurface(parent)
{
    this->pixFmtList = pixFmtList;
#ifdef ANDROID
//    this->pixFmtList.append(QVideoFrame::Format_RGB32);
//    this->pixFmtList.append(QVideoFrame::Format_ARGB32);
//    this->pixFmtList.append(QVideoFrame::Format_ARGB32_Premultiplied);
//    this->pixFmtList.append(QVideoFrame::Format_RGB565);
//    this->pixFmtList.append(QVideoFrame::Format_RGB555);
//    this->pixFmtList.append(QVideoFrame::Format_YV12);
//    this->pixFmtList.append(QVideoFrame::Format_NV21);
#endif

}

bool VideoSurface::present(const QVideoFrame &frame)
{
    qDebug()<<"new QVideoFrame";
    emit newVideoFrame(frame);      // 触发新帧数据信号
    return true;
}


QList<QVideoFrame::PixelFormat>
VideoSurface::supportedPixelFormats(QAbstractVideoBuffer::HandleType type) const
{/*
    if (type == QAbstractVideoBuffer::NoHandle) {
        //return QList<QVideoFrame::PixelFormat>()<< QVideoFrame::Format_RGB32<< QVideoFrame::Format_ARGB32<< QVideoFrame::Format_ARGB32_Premultiplied<< QVideoFrame::Format_RGB565<< QVideoFrame::Format_RGB555;
        return QList<QVideoFrame::PixelFormat>()<< QVideoFrame::Format_YV12 <<QVideoFrame::Format_NV21;
    } else {
        return QList<QVideoFrame::PixelFormat>();
    }*/
    //return QList<QVideoFrame::PixelFormat>()<< QVideoFrame::Format_YV12 <<QVideoFrame::Format_NV21;
    //return pixFmtList;
    //Q_UNUSED(type);
    // 表示我这个类支持所有格式
    QList<QVideoFrame::PixelFormat> listPixelFormats;
        listPixelFormats.clear();
        listPixelFormats << QVideoFrame::Format_ARGB32
            << QVideoFrame::Format_ARGB32_Premultiplied
            << QVideoFrame::Format_RGB32
            << QVideoFrame::Format_RGB24
            << QVideoFrame::Format_RGB565
            << QVideoFrame::Format_RGB555
            << QVideoFrame::Format_ARGB8565_Premultiplied
            << QVideoFrame::Format_BGRA32
            << QVideoFrame::Format_BGRA32_Premultiplied
            << QVideoFrame::Format_BGR32
            << QVideoFrame::Format_BGR24
            << QVideoFrame::Format_BGR565
            << QVideoFrame::Format_BGR555
            << QVideoFrame::Format_BGRA5658_Premultiplied
            << QVideoFrame::Format_AYUV444
            << QVideoFrame::Format_AYUV444_Premultiplied
            << QVideoFrame::Format_YUV444
            << QVideoFrame::Format_YUV420P
            << QVideoFrame::Format_YV12
            << QVideoFrame::Format_UYVY
            << QVideoFrame::Format_YUYV
            << QVideoFrame::Format_NV12
            << QVideoFrame::Format_NV21
            << QVideoFrame::Format_IMC1
            << QVideoFrame::Format_IMC2
            << QVideoFrame::Format_IMC3
            << QVideoFrame::Format_IMC4
            << QVideoFrame::Format_Y8
            << QVideoFrame::Format_Y16
            << QVideoFrame::Format_Jpeg
            << QVideoFrame::Format_CameraRaw
            << QVideoFrame::Format_AdobeDng;
        return listPixelFormats;

}

bool VideoSurface::isFormatSupported(const QVideoSurfaceFormat &format) const
{
//    if ((format.pixelFormat() == QVideoFrame::Format_NV21)
//            ||  (format.pixelFormat() == QVideoFrame::Format_YV12)){
//        return true;
//    }
    return true;
}

