//
// Created by pirate on 2022/3/26.
//

#ifndef FFMPEGDEMO_AUDIOGLRENDER_H
#define FFMPEGDEMO_AUDIOGLRENDER_H

#include <render/BaseGLRender.h>
#include "thread"

class AudioGLRender : public BaseGLRender{
public:
    static AudioGLRender* GetInstance();
    static void ReleaseInstance();
private:
    void Init();
    void UnInit();
    AudioGLRender(){
        Init();
    }
    ~AudioGLRender(){
        UnInit();
    }
private:
    static AudioGLRender *m_pInstance;
    static std::mutex m_Mutex;
};


#endif //FFMPEGDEMO_AUDIOGLRENDER_H
