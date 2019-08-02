#ifndef VIDEOSURFACE_H
#define VIDEOSURFACE_H

#include <QAbstractVideoSurface>
#include <QVideoFrame>
#include <QVideoSurfaceFormat>
#include <QWidget>
#include <QCamera>
#include <QCameraInfo>
#include <QCameraViewfinderSettings>
#include <QVideoFrame>
#include <QCameraImageCapture>
#include <QCameraViewfinder>
#include <QThread>
#include <QMediaRecorder>


class VideoSurface : public QAbstractVideoSurface
{
    Q_OBJECT
public:
    VideoSurface(QList<QVideoFrame::PixelFormat> pixFmtList, QObject *parent = nullptr);

    // 每次采集到视频帧都会调用该函数

    // 用来返回所有支持的像素格式列表
    virtual QList<QVideoFrame::PixelFormat>
        supportedPixelFormats(QAbstractVideoBuffer::HandleType type = QAbstractVideoBuffer::NoHandle) const;

    virtual bool isFormatSupported(const QVideoSurfaceFormat &format) const;
    bool present(const QVideoFrame &frame);
    QList<QVideoFrame::PixelFormat> allFmtList() const;

signals:
    void newVideoFrame(const QVideoFrame &frame);

private:
    QList<QVideoFrame::PixelFormat> pixFmtList;
};



#endif // VIDEOSURFACE_H
