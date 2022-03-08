//
// Created by pirate on 2022/3/8.
//

#ifndef FFMPEGDEMO_AUDIODECODER_H
#define FFMPEGDEMO_AUDIODECODER_H
#include "DecoderBase.h"

class AudioDecoder : public DecoderBase {
public:
    AudioDecoder(char *url){
        Init(url, AVMEDIA_TYPE_AUDIO);
    }

    virtual ~AudioDecoder(){
        UnInit();
    }

protected:
    virtual void OnDecoderReady();
    virtual void OnDecoderDone();

};


#endif //FFMPEGDEMO_AUDIODECODER_H
