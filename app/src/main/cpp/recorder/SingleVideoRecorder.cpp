//
// Created by pirate on 2022/3/8.
//

#include "SingleVideoRecorder.h"
SingleVideoRecorder::SingleVideoRecorder(const char *outUrl, int frameWidth, int frameHeight,
                                         long bitRate, int fps)
                                         :m_frameWidth(frameWidth),
                                          m_frameHeight(frameHeight),
                                          m_bitRate(bitRate),
                                          m_frameRate(fps)
                                         {
    LOGCATE("SingleVideoRecorder::SingleVideoRecorder outUrl=%s, [w,h]=[%d,%d], bitRate=%ld, fps=%d", outUrl, frameWidth, frameHeight, bitRate, fps);
    strcpy(m_outUrl, outUrl);
}

int SingleVideoRecorder::StartRecord() {
    LOGCATE("SingleVideoRecorder::StartRecord");
    int result = 0;
//    do{
//        result = avformat_alloc_output_context2(&m_pFormatCtx, nullptr, nullptr, m_outUrl);
//    }
    return 0;
}