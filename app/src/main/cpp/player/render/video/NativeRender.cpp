//
// Created by pirate on 2022/3/8.
//

#include "NativeRender.h"
NativeRender::NativeRender(JNIEnv *env, jobject surface): VideoRender(VIDEO_RENDER_ANWINDOW)
{
    m_NativeWindow = ANativeWindow_fromSurface(env, surface);
}
