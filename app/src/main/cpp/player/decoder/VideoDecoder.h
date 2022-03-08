//
// Created by pirate on 2022/3/8.
//

#ifndef FFMPEGDEMO_VIDEODECODER_H
#define FFMPEGDEMO_VIDEODECODER_H


#include "DecoderBase.h"

class VideoDecoder : public DecoderBase{

public:
    VideoDecoder(char *string){
        Init(string, AVMEDIA_TYPE_VIDEO);
    }
    virtual ~VideoDecoder(){
        UnInit();
    }
};


#endif //FFMPEGDEMO_VIDEODECODER_H
