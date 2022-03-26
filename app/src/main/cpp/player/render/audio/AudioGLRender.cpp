//
// Created by pirate on 2022/3/26.
//

#include "AudioGLRender.h"

AudioGLRender* AudioGLRender::m_pInstance = nullptr;
std::mutex AudioGLRender::m_Mutex;