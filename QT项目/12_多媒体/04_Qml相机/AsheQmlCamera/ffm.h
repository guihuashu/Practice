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

class FFM{
public:
    FFM();
    const char *printConf();
    int NV21toYUV420p(QVideoFrame &frame, AVFrame *yuv420p);
public:
    SwsContext *vSwsCtx = NULL;

};
#endif // FFM_H





