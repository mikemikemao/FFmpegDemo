//
// Created by pirate on 2022/3/25.
//

#ifndef FFMPEGDEMO_OPENSLRENDER_H
#define FFMPEGDEMO_OPENSLRENDER_H
#include "LogUtil.h"
#include "AudioRender.h"
#include <SLES/OpenSLES.h>
#include <SLES/OpenSLES_Android.h>
#include <thread>
#include "queue"
#include "AudioGLRender.h"
#define MAX_QUEUE_BUFFER_SIZE 3

class OpenSLRender : public AudioRender {
public:
    OpenSLRender(){}
    virtual ~OpenSLRender(){}
    virtual void Init();
    virtual void UnInit();
    virtual void ClearAudioCache();
    virtual void RenderAudioFrame(uint8_t *pData, int dataSize);

private:
    int CreateEngine();
    int CreateOutputMixer();
    int CreateAudioPlayer();
    static void AudioPlayerCallback(SLAndroidSimpleBufferQueueItf bufferQueue, void *context);
    static void CreateSLWaitingThread(OpenSLRender *openSlRender);
    void StartRender();
    int GetAudioFrameQueueSize();
    void HandleAudioFrameQueue();

private:
    SLObjectItf m_EngineObj = nullptr;
    SLEngineItf m_EngineEngine = nullptr;
    SLObjectItf m_OutputMixObj = nullptr;//用SLObjectItf创建混音器接口对象
    SLObjectItf m_AudioPlayerObj = nullptr;
    SLPlayItf m_AudioPlayerPlay = nullptr;
    SLAndroidSimpleBufferQueueItf m_BufferQueue;
    SLVolumeItf m_AudioPlayerVolume = nullptr;
    std::thread *m_thread = nullptr;
    std::mutex   m_Mutex;
    std::condition_variable m_Cond;
    std::queue<AudioFrame *> m_AudioFrameQueue;
    volatile bool m_Exit = false;
};


#endif //FFMPEGDEMO_OPENSLRENDER_H
