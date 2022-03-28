/**
 *
 * Created by 公众号：字节流动 on 2021/3/16.
 * https://github.com/githubhaohao/LearnFFmpeg
 * 最新文章首发于公众号：字节流动，有疑问或者技术交流可以添加微信 Byte-Flow ,领取视频教程, 拉你进技术交流群
 *
 * */

#include <jni.h>
#define  LOG_TAG "learn_ffmpeg"
#include "util/LogUtil.h"
#include <vector>
#include <string>
#include "PlayerWrapper.h"
extern "C" {
#include <libavcodec/version.h>
#include <libavcodec/avcodec.h>
#include <libavformat/version.h>
#include <libavutil/version.h>
#include <libavfilter/version.h>
#include <libswresample/version.h>
#include <libswscale/version.h>
};

#ifdef __cplusplus
extern "C" {
#endif



///////////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * ffmpeg
 *
 */

JNIEXPORT jstring
JNICALL Java_com_hikvision_ffmpegdemo_ZZFFmpeg_native_1getFFmpegVersion
        (JNIEnv *env, jclass cls)
{
    char strBuffer[1024 * 4] = {0};
    strcat(strBuffer,av_version_info());
    return env->NewStringUTF(strBuffer);
}

/*
 * Class:     com_byteflow_learnffmpeg_media_FFMediaPlayer
 * Method:    native_Init
 * Signature: (JLjava/lang/String;Ljava/lang/Object;)J
 */
JNIEXPORT jlong
JNICALL Java_com_hikvision_ffmpegdemo_ZZFFmpeg_native_1Init
        (JNIEnv *env, jobject obj, jstring jurl, int playerType, jint renderType, jobject surface)
{
    const char* url = env->GetStringUTFChars(jurl, nullptr);
    PlayerWrapper *player = new PlayerWrapper();
    player->Init(env, obj, const_cast<char *>(url), playerType, renderType, surface);
    env->ReleaseStringUTFChars(jurl, url);
    return reinterpret_cast<jlong>(player);
}

/*
 * Class:     com_byteflow_learnffmpeg_media_FFMediaPlayer
 * Method:    native_Play
 * Signature: (J)V
 */
JNIEXPORT void
JNICALL Java_com_hikvision_ffmpegdemo_ZZFFmpeg_native_1Play
        (JNIEnv *env, jobject obj, jlong player_handle)
{
    if(player_handle != 0)
    {
        PlayerWrapper *pPlayerWrapper = reinterpret_cast<PlayerWrapper *>(player_handle);
        pPlayerWrapper->Play();
    }

}


/*
 * Class:     com_byteflow_learnffmpeg_media_FFMediaPlayer
 * Method:    native_Play
 * Signature: (J)V
 */
JNIEXPORT void
JNICALL Java_com_hikvision_ffmpegdemo_ZZFFmpeg_native_1Stop
        (JNIEnv *env, jobject obj, jlong player_handle)
{
    if(player_handle != 0)
    {
        PlayerWrapper *pPlayerWrapper = reinterpret_cast<PlayerWrapper *>(player_handle);
        pPlayerWrapper->Stop();
    }

}

/*
 * Class:     com_byteflow_learnffmpeg_media_FFMediaPlayer
 * Method:    native_Play
 * Signature: (J)V
 */
JNIEXPORT void
JNICALL Java_com_hikvision_ffmpegdemo_ZZFFmpeg_native_1UnInit
        (JNIEnv *env, jobject obj, jlong player_handle)
{
    if(player_handle != 0)
    {
        PlayerWrapper *pPlayerWrapper = reinterpret_cast<PlayerWrapper *>(player_handle);
        pPlayerWrapper->UnInit();
        delete pPlayerWrapper;

    }

}

JNIEXPORT jlong
JNICALL Java_com_hikvision_ffmpegdemo_ZZFFmpeg_native_1GetMediaParams(JNIEnv *env, jobject thiz,
                                                                         jlong player_handle,
                                                                         jint param_type) {
    long value = 0;
    if(player_handle != 0)
    {
        PlayerWrapper *ffMediaPlayer = reinterpret_cast<PlayerWrapper *>(player_handle);
        value = ffMediaPlayer->GetMediaParams(param_type);
    }
    return value;
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * opengl
 *
 */
#include "MyGLRenderContext.h"

JNIEXPORT void
JNICALL Java_com_hikvision_ffmpegdemo_ZZFFmpeg_native_1OnSurfaceCreated
        (JNIEnv *env, jclass cls)
{
    MyGLRenderContext::GetInstance()->OnSurfaceCreated();
}

JNIEXPORT void
JNICALL Java_com_hikvision_ffmpegdemo_ZZFFmpeg_native_1OnSurfaceChanged
        (JNIEnv *env, jclass cls,jint width,jint height)
{
    MyGLRenderContext::GetInstance()->OnSurfaceChanged(width, height);
}

JNIEXPORT void
JNICALL Java_com_hikvision_ffmpegdemo_ZZFFmpeg_native_1OnDrawFrame
        (JNIEnv *env, jclass cls)
{
    MyGLRenderContext::GetInstance()->OnDrawFrame();
}

#include "v4l2/V4L2Device.h"
JNIEXPORT void
        JNICALL Java_com_hikvision_ffmpegdemo_ZZFFmpeg_native_1GetV4l2CamSolution
(JNIEnv *env, jclass cls,jobject jResolution)
{
    V4L2Device v4l2Device;
    V4L2Device::Resolution resolution;
    resolution = v4l2Device.sensorResolution();
    LOGCATD("resolution width =%d height =%d ",resolution.width,resolution.height);
    jclass objectClass = env->FindClass("com/hikvision/ffmpegdemo/cam/Resolution");
    jmethodID objectClassSetWidth = env->GetStaticMethodID(objectClass, "setWidth", "(I)V");
    jmethodID objectClassSetHeight = env->GetStaticMethodID(objectClass, "setHeight", "(I)V");
    env->CallStaticVoidMethod(objectClass,objectClassSetWidth,resolution.width);
    env->CallStaticVoidMethod(objectClass,objectClassSetHeight,resolution.height);

}







///////////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * test
 *
 */

JNIEXPORT void
JNICALL Java_com_hikvision_ffmpegdemo_ZZFFmpeg_native_1vectorTest
        (JNIEnv *env, jclass cls,jobject vector)
{
    jclass vectorString = env->GetObjectClass(vector);
    //获取成员变量
    jmethodID vectorStringAdd = env->GetMethodID(vectorString, "get", "(I)Ljava/lang/Object;");
    //调用方法
    jobject stringObj=env->CallObjectMethod(vector,vectorStringAdd,0);
    jstring string_class = reinterpret_cast<jstring>(stringObj);
    const char *szComPath;
    szComPath = env->GetStringUTFChars(string_class,0);
    LOGCATD("%s_______%s", __FUNCTION__,szComPath);

}

#ifdef __cplusplus
}
#endif
