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

int FFM::NV21toYUV420p(QVideoFrame &frame, AVFrame *yuv420p)
{
    int ret;

    vSwsCtx = sws_getCachedContext(vSwsCtx, \
        frame.width(), frame.height(), AV_PIX_FMT_NV21, \
        frame.width(), frame.height(), AV_PIX_FMT_YUV420P, \
        SWS_BICUBIC, NULL, NULL, NULL);

    uint8_t *indata[AV_NUM_DATA_POINTERS] = { 0 };	// 数据源(R.G.B./Y.U.V)
    int	insize[AV_NUM_DATA_POINTERS] = { 0 };		// 数据源(R.G.B./Y.U.V)
    uint8_t **outdata;			// uint8_t*[AV_NUM_DATA_POINTERS]数组
    int *outsize;				// int[AV_NUM_DATA_POINTERS]数组

    indata[0] = frame.bits();						// 采集到的帧数据
    insize[0] = frame.bytesPerLine();               // 输入数据对其后一行的字节数
    outdata = yuv420p->data;						// 转换后帧的存储位置
    outsize = yuv420p->linesize;					// 由系统内部进行计算和填充

    ret= sws_scale(vSwsCtx, indata, insize, 0, frame.height(), outdata, outsize);

    sws_freeContext(vSwsCtx);
    free(vSwsCtx);
    return ret;
}




