#ifndef FFM_H
#define FFM_H
extern "C" {
    #include <libavformat/avformat.h>
    //#include <libavdevice/avdevice.h>
    #include <libavcodec/avcodec.h>
    #include <libavcodec/mediacodec.h>
    #include <libavutil/avutil.h>
    #include <libavutil/dict.h>
    #include <libswscale/swscale.h>
    #include <libswresample/swresample.h>
    #include <libavutil/time.h>
}
#include <QVideoFrame>
#include <QPainter>
#include <QImage>
#include <QDebug>


#define CUR qInfo()<<__FILE__<<","<<__LINE__

class FFM{
public:
    FFM();
    const char *printConf();
    int NV21toRgb24(QVideoFrame &frame, AVFrame *yuv420p);
    int NV21toRGB32(QVideoFrame &frame, AVFrame *rgb32);
    int yuv420ptoRgb32(AVFrame *yuv420p, AVFrame *rgb32);
public:
    SwsContext *SwsNv21toRgb24 = NULL;
    SwsContext *SwsNv21toRgb32 = NULL;
    SwsContext *SwsYuv420ptoRgb32 = NULL;
};
#endif // FFM_H





