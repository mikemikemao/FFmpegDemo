//
// Created by pirate on 2022/3/8.
//

#ifndef FFMPEGDEMO_PLAYERWRAPPER_H
#define FFMPEGDEMO_PLAYERWRAPPER_H
#include <jni.h>
#include "MediaPlayer.h"

static const int FFMEDIA_PLAYER = 0;
static const int HWCODEC_PLAYER = 1;

class PlayerWrapper {
public:
    PlayerWrapper(){};
    virtual ~PlayerWrapper(){};
    void Init(JNIEnv *jniEnv, jobject obj, char *url, int playerType, int renderType, jobject surface);
    void Play();
    void Stop();
    void UnInit();
    long GetMediaParams(int paramType);
private:
    //FFMediaPlayer HWCodecPlayer的父类
    MediaPlayer* m_MediaPlayer = nullptr;
};


#endif //FFMPEGDEMO_PLAYERWRAPPER_H
