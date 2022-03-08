//
// Created by pirate on 2022/3/8.
//

#ifndef FFMPEGDEMO_DECODERBASE_H
#define FFMPEGDEMO_DECODERBASE_H

extern "C" {
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libavutil/frame.h>
#include <libavutil/time.h>
#include <libavcodec/jni.h>
};
#include <thread>
#include "Decoder.h"
#define  LOG_TAG "DecoderBase"
#define MAX_PATH 2048

#include "LogUtil.h"
#define  LOG_TAG "DecoderBase"
using namespace std;

enum DecoderState {
    STATE_UNKNOWN,
    STATE_DECODING,
    STATE_PAUSE,
    STATE_STOP
};

class DecoderBase : public Decoder {
public:
    DecoderBase()
    {};
    virtual~ DecoderBase()
    {};
    //停止
    virtual void Stop();
protected:
    virtual int Init(const char *url, AVMediaType mediaType);
    virtual void UnInit();

private:
    //文件地址
    char       m_Url[MAX_PATH] = {0};
    //数据流的类型
    AVMediaType      m_MediaType = AVMEDIA_TYPE_UNKNOWN;
    //锁和条件变量
    mutex               m_Mutex;
    condition_variable  m_Cond;
    thread             *m_Thread = nullptr;
    //解码器状态
    volatile int  m_DecoderState = STATE_UNKNOWN;
};


#endif //FFMPEGDEMO_DECODERBASE_H
