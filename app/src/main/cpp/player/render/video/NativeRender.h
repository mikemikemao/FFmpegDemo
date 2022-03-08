//
// Created by pirate on 2022/3/8.
//

#ifndef FFMPEGDEMO_NATIVERENDER_H
#define FFMPEGDEMO_NATIVERENDER_H
#include "VideoRender.h"
#include <android/native_window.h>
#include <android/native_window_jni.h>
#include <jni.h>
#include "LogUtil.h"
#include "ImageDef.h"
#include "string.h"
class NativeRender : public VideoRender {
public:
    NativeRender(JNIEnv *env, jobject surface);
    virtual ~NativeRender();
    virtual void Init(int videoWidth, int videoHeight, int *dstSize) = 0;
    void RenderVideoFrame(NativeImage *pImage);

private:
    ANativeWindow *m_NativeWindow = nullptr;
    ANativeWindow_Buffer m_NativeWindowBuffer;
    int m_DstWidth;
    int m_DstHeight;

};


#endif //FFMPEGDEMO_NATIVERENDER_H
