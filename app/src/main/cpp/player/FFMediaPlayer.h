//
// Created by pirate on 2022/3/8.
//

#ifndef FFMPEGDEMO_FFMEDIAPLAYER_H
#define FFMPEGDEMO_FFMEDIAPLAYER_H
#include "MediaPlayer.h"
#include "VideoDecoder.h"
#include "AudioDecoder.h"
#include "NativeRender.h"
#include "OpenSLRender.h"

class FFMediaPlayer : public MediaPlayer {

public:
    FFMediaPlayer(){};
    virtual ~FFMediaPlayer(){};

    virtual void Init(JNIEnv *jniEnv, jobject obj, char *url, int renderType, jobject surface);
    virtual void Play() ;
    virtual long GetMediaParams(int paramType);
    static void PostMessage(void *context, int msgType, float msgCode);

private:
    virtual JNIEnv *GetJNIEnv(bool *isAttach);
    virtual jobject GetJavaObj();
    virtual JavaVM *GetJavaVM();


private:
    VideoDecoder *m_VideoDecoder = nullptr;
    AudioDecoder *m_AudioDecoder = nullptr;

    VideoRender *m_VideoRender = nullptr;
    AudioRender *m_AudioRender = nullptr;
};


#endif //FFMPEGDEMO_FFMEDIAPLAYER_H
