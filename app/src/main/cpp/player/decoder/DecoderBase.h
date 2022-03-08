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

enum DecoderMsg {
    MSG_DECODER_INIT_ERROR,
    MSG_DECODER_READY,
    MSG_DECODER_DONE,
    MSG_REQUEST_RENDER,
    MSG_DECODING_TIME
};

class DecoderBase : public Decoder {
public:
    DecoderBase()
    {};
    virtual~ DecoderBase()
    {};
    //开始播放
    virtual void Start();
    virtual float GetDuration()
    {
        //ms to s
        return m_Duration * 1.0f / 1000;
    }
    //停止
    virtual void Stop();
    virtual void SetMessageCallback(void* context, MessageCallback callback)
    {
        m_MsgContext = context;
        m_MsgCallback = callback;
    }
protected:
    void * m_MsgContext = nullptr;
    MessageCallback m_MsgCallback = nullptr;
    virtual int Init(const char *url, AVMediaType mediaType);
    virtual void UnInit();
    virtual void OnDecoderReady() = 0;
    virtual void OnDecoderDone() = 0;
    AVCodecContext *GetCodecContext() {
        return m_AVCodecContext;
    }
private:
    //启动解码线程
    void StartDecodingThread();
    void DoAVDecoding(DecoderBase *decoder);
    int InitFFDecoder();
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
    //总时长 ms
    long             m_Duration = 0;
    //封装格式上下文
    AVFormatContext *m_AVFormatContext = nullptr;
    //解码器上下文
    AVCodecContext  *m_AVCodecContext = nullptr;
    //解码器
    AVCodec         *m_AVCodec = nullptr;
    //编码的数据包
    AVPacket        *m_Packet = nullptr;
    //解码的帧
    AVFrame         *m_Frame = nullptr;
    //数据流索引
    int              m_StreamIndex = -1;

};


#endif //FFMPEGDEMO_DECODERBASE_H
