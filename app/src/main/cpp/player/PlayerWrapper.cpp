//
// Created by pirate on 2022/3/8.
//

#include "PlayerWrapper.h"
#include "FFMediaPlayer.h"

/**
  * 播放器初始化
  * @param url 视频文件路径
  * @param playerType 编解码方式 FFmpeg 或mediacodec
  *     public static final int FFMEDIA_PLAYER = 0;
  *     public static final int HWCODEC_PLAYER = 1;
  * @param renderType 渲染方式
  *     public static final int VIDEO_RENDER_OPENGL         = 0;
  *     public static final int VIDEO_RENDER_ANWINDOW       = 1;
  *     public static final int VIDEO_RENDER_3D_VR          = 2;
  * @param surface
  * @return
  */
void PlayerWrapper::Init(JNIEnv *jniEnv, jobject obj, char *url, int playerType, int renderType,
                         jobject surface) {
    switch (playerType) {
        case FFMEDIA_PLAYER:
            m_MediaPlayer = new FFMediaPlayer();
            break;
        case HWCODEC_PLAYER:
            //m_MediaPlayer = new HWCodecPlayer();
            break;
        default:
            break;
    }
    if(m_MediaPlayer)
        m_MediaPlayer->Init(jniEnv, obj, url, renderType, surface);
}

void PlayerWrapper::Play() {
    if(m_MediaPlayer) {
        m_MediaPlayer->Play();
    }
}

void PlayerWrapper::Stop() {
    if(m_MediaPlayer) {
        m_MediaPlayer->Stop();
    }
}

void PlayerWrapper::UnInit() {
    if(m_MediaPlayer) {
        m_MediaPlayer->UnInit();
        delete m_MediaPlayer;
        m_MediaPlayer = nullptr;
    }
}

long PlayerWrapper::GetMediaParams(int paramType) {
    if(m_MediaPlayer) {
        return m_MediaPlayer->GetMediaParams(paramType);
    }

    return 0;
}