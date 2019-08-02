#include "ffm.h"

const char *FFM::printConf()
{
    return avformat_configuration();
}
FFM::FFM()
{
    avcodec_register_all();
    av_register_all();
    avformat_network_init();
}

int FFM::NV21toRgb24(QVideoFrame &frame, AVFrame *rgb24)
{
    int ret;

    SwsNv21toRgb24 = sws_getCachedContext(SwsNv21toRgb24, \
        frame.width(), frame.height(), AV_PIX_FMT_NV21, \
        frame.width(), frame.height(), AV_PIX_FMT_RGB24, \
        SWS_BICUBIC, NULL, NULL, NULL);

    // 准备格式转换
    uint8_t *indata[AV_NUM_DATA_POINTERS] = { 0 };	// 数据源(R.G.B./Y.U.V)
    int	insize[AV_NUM_DATA_POINTERS] = { 0 };		// 数据源(R.G.B./Y.U.V)
    uint8_t **outdata;			// uint8_t*[AV_NUM_DATA_POINTERS]数组
    int *outsize;				// int[AV_NUM_DATA_POINTERS]数组
    int i=0;

    // Format_NV21是平面存取格式, 有多个平面
    while (frame.bits(i)) {
        indata[i] = (unsigned char *)frame.bits(i);
        insize[i] = frame.bytesPerLine(i);
        i++;
    }
    outdata = rgb24->data;						// 转换后帧的存储位置
    outsize = rgb24->linesize;					// 由系统内部进行计算和填充
    if (!SwsNv21toRgb24) {
        qWarning()<<"SwsNv21toYuv420p=NULL";
        return -1;
    }

    ret= sws_scale(SwsNv21toRgb24, indata, insize, 0, frame.height(), outdata, outsize);
#if 0
    if (vSwsCtx) {
        sws_freeContext(vSwsCtx);
        free(vSwsCtx);
        vSwsCtx=NULL;
    }
#endif
    return ret;
}

int FFM::NV21toRGB32(QVideoFrame &frame, AVFrame *rgb32)
{
    int ret;

    SwsNv21toRgb32 = sws_getCachedContext(SwsNv21toRgb32, \
        frame.width(), frame.height(), AV_PIX_FMT_NV21, \
        frame.width(), frame.height(), AV_PIX_FMT_RGB32, \
        SWS_BICUBIC, NULL, NULL, NULL);
//#endif
    //return 0;
    uint8_t *indata[AV_NUM_DATA_POINTERS] = { 0 };	// 数据源(R.G.B./Y.U.V)
    int	insize[AV_NUM_DATA_POINTERS] = { 0 };		// 数据源(R.G.B./Y.U.V)
    uint8_t **outdata;			// uint8_t*[AV_NUM_DATA_POINTERS]数组
    int *outsize;				// int[AV_NUM_DATA_POINTERS]数组
    int i=0;

    // Format_NV21是平面存取格式, 有多个平面
    while (frame.bits(i)) {
        indata[i] = (unsigned char *)frame.bits(i);
        insize[i] = frame.bytesPerLine(i);
        i++;
    }
    outdata = rgb32->data;						// 转换后帧的存储位置
    outsize = rgb32->linesize;					// 由系统内部进行计算和填充
    if (!SwsNv21toRgb24) {
        qWarning()<<"SwsNv21toYuv420p = NULL";
        return -1;
    }

    ret= sws_scale(SwsNv21toRgb24, indata, insize, 0, frame.height(), outdata, outsize);
    qDebug()<<"sws_scale end";
#if 0
    if (vSwsCtx) {
        sws_freeContext(vSwsCtx);
        free(vSwsCtx);
        vSwsCtx=NULL;
    }
#endif
}

int FFM::yuv420ptoRgb32(AVFrame *yuv420p, AVFrame *rgb32)
{
    SwsYuv420ptoRgb32 = sws_getCachedContext(SwsYuv420ptoRgb32, \
        yuv420p->width, yuv420p->height, AV_PIX_FMT_YUV420P, \
        yuv420p->width, yuv420p->height, AV_PIX_FMT_RGB32, \
        SWS_BICUBIC, NULL, NULL, NULL);
    if (!SwsYuv420ptoRgb32){
        qWarning()<<"SwsYuv420ptoRgb32=NULL";
        return -1;
    }


//    qWarning()<<yuv420p->width;
//    qWarning()<<yuv420p->height;
//    qWarning()<<yuv420p->data[0];
//    qWarning()<<yuv420p->data[1];
//    qWarning()<<yuv420p->linesize[0];
//    qWarning()<<yuv420p->linesize[1];

    unsigned char *rgb = new unsigned char[1920*1080*4];
    uint8_t *data[AV_NUM_DATA_POINTERS] = { 0 };
    int lines[AV_NUM_DATA_POINTERS] = { 0 };
    data[0] = rgb;
    lines[0] = 1920 *4;

    int ret= sws_scale(SwsYuv420ptoRgb32,
        yuv420p->data,		//输入数据
        yuv420p->linesize,	//输入行大小
        0,
        yuv420p->height,		//输入高度
        data,            //输出数据和大小
        lines);

    return ret;
}




