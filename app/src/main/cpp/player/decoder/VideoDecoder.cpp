//
// Created by pirate on 2022/3/8.
//

#include "VideoDecoder.h"


void VideoDecoder::OnDecoderReady() {
    LOGCATE("VideoDecoder::OnDecoderReady");
    m_VideoWidth = GetCodecContext()->width;
    m_VideoHeight = GetCodecContext()->height;

    if (m_MsgContext && m_MsgCallback)
        m_MsgCallback(m_MsgContext, MSG_DECODER_READY, 0);

    if (m_VideoRender != nullptr) {
        int dstSize[2] = {0};
        m_VideoRender->Init(m_VideoWidth, m_VideoHeight, dstSize);
        m_RenderWidth = dstSize[0];
        m_RenderHeight = dstSize[1];
    }
    if(m_VideoRender->GetRenderType() == VIDEO_RENDER_ANWINDOW) {
        int fps = 25;
        long videoBitRate = m_RenderWidth * m_RenderHeight * fps * 0.2; //码率怎么算？？？？？
        m_pVideoRecorder = new SingleVideoRecorder("/sdcard/learnffmpeg_output.mp4", m_RenderWidth, m_RenderHeight, videoBitRate, fps);
        m_pVideoRecorder->StartRecord();
    }
}