//
// Created by pirate on 2022/3/8.
//

#ifndef FFMPEGDEMO_SINGLEVIDEORECORDER_H
#define FFMPEGDEMO_SINGLEVIDEORECORDER_H
#include "LogUtil.h"
#include "string.h"

class SingleVideoRecorder {
public:
    SingleVideoRecorder(const char* outUrl, int frameWidth, int frameHeight, long bitRate, int fps);
    ~SingleVideoRecorder(){};
    int StartRecord();
private:
    char m_outUrl[1024] = {0};
    int m_frameWidth;
    int m_frameHeight;
    int m_frameIndex = 0;
    long m_bitRate;
    int m_frameRate;
};


#endif //FFMPEGDEMO_SINGLEVIDEORECORDER_H
