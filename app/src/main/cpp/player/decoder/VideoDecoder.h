//
// Created by pirate on 2022/3/8.
//

#ifndef FFMPEGDEMO_VIDEODECODER_H
#define FFMPEGDEMO_VIDEODECODER_H


#include "DecoderBase.h"
#include "VideoRender.h"
#include "SingleVideoRecorder.h"
extern "C" {
#include <libavutil/imgutils.h>
#include <libswscale/swscale.h>
#include <libavcodec/jni.h>
};
#include "ImageDef.h"

class VideoDecoder : public DecoderBase{

public:
    VideoDecoder(char *string){
        Init(string, AVMEDIA_TYPE_VIDEO);
    }
    virtual ~VideoDecoder(){
        UnInit();
    }
    int GetVideoWidth()
    {
        return m_VideoWidth;
    }
    int GetVideoHeight()
    {
        return m_VideoHeight;
    }
    void SetVideoRender(VideoRender *videoRender)
    {
        m_VideoRender = videoRender;
    }

private:
    virtual void OnDecoderReady();
    virtual void OnDecoderDone();
    virtual void OnFrameAvailable(AVFrame *frame);
private:
    int m_VideoWidth = 0;
    int m_VideoHeight = 0;
    int m_RenderWidth = 0;
    int m_RenderHeight = 0;
    VideoRender *m_VideoRender = nullptr;
    SingleVideoRecorder *m_pVideoRecorder = nullptr;
    AVFrame *m_RGBAFrame = nullptr;
    const AVPixelFormat DST_PIXEL_FORMAT = AV_PIX_FMT_RGBA;
    uint8_t *m_FrameBuffer = nullptr;
    SwsContext *m_SwsContext = nullptr;

};


#endif //FFMPEGDEMO_VIDEODECODER_H
