//
// Created by pirate on 2022/3/8.
//

#ifndef FFMPEGDEMO_AUDIODECODER_H
#define FFMPEGDEMO_AUDIODECODER_H


class AudioDecoder : public DecoderBase {
public:
    AudioDecoder(char *url){
        Init(url, AVMEDIA_TYPE_AUDIO);
    }

    virtual ~AudioDecoder(){
        UnInit();
    }

};


#endif //FFMPEGDEMO_AUDIODECODER_H
