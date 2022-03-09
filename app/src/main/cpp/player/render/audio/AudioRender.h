//
// Created by 字节流动 on 2020/6/19.
//

#ifndef LEARNFFMPEG_AUDIORENDER_H
#define LEARNFFMPEG_AUDIORENDER_H
#include <stdint.h>
#include "AudioRender.h"

class AudioRender {
public:
    virtual ~AudioRender()
    {}
    virtual void Init() = 0;
    virtual void ClearAudioCache() = 0;
    virtual void RenderAudioFrame(uint8_t *pData, int dataSize) = 0;
    virtual void UnInit() = 0;

};


#endif //LEARNFFMPEG_AUDIORENDER_H
