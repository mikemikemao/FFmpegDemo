//
// Created by pirate on 2022/3/8.
//

#ifndef FFMPEGDEMO_FFMEDIAPLAYER_H
#define FFMPEGDEMO_FFMEDIAPLAYER_H
#include "MediaPlayer.h"
#include "VideoDecoder.h"
#include "AudioDecoder.h"

class FFMediaPlayer : public MediaPlayer {

public:
    FFMediaPlayer(){};
    virtual ~FFMediaPlayer(){};

    virtual void Init(JNIEnv *jniEnv, jobject obj, char *url, int renderType, jobject surface);

private:
    VideoDecoder *m_VideoDecoder = nullptr;
    AudioDecoder *m_AudioDecoder = nullptr;
};


#endif //FFMPEGDEMO_FFMEDIAPLAYER_H
