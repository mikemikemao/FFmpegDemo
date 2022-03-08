//
// Created by pirate on 2022/3/8.
//

#ifndef FFMPEGDEMO_MEDIAPLAYER_H
#define FFMPEGDEMO_MEDIAPLAYER_H
#include <jni.h>

class MediaPlayer {
public:
    MediaPlayer(){};
    virtual ~MediaPlayer(){};
    virtual void Init(JNIEnv *jniEnv, jobject obj, char *url, int renderType, jobject surface) = 0;
    //目前还不知道什么用。。。。。。。
    JavaVM *m_JavaVM = nullptr;
    jobject m_JavaObj = nullptr;
};


#endif //FFMPEGDEMO_MEDIAPLAYER_H
