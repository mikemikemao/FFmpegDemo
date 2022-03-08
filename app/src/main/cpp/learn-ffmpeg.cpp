/**
 *
 * Created by 公众号：字节流动 on 2021/3/16.
 * https://github.com/githubhaohao/LearnFFmpeg
 * 最新文章首发于公众号：字节流动，有疑问或者技术交流可以添加微信 Byte-Flow ,领取视频教程, 拉你进技术交流群
 *
 * */

#include <jni.h>
#include "util/LogUtil.h"
#include <vector>
#include <string>
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

#define  LOG_TAG "learn_ffmpeg"

JNIEXPORT jstring
JNICALL Java_com_hikvision_ffmpegdemo_ZZFFmpeg_native_1getFFmpegVersion
        (JNIEnv *env, jclass cls)
{
    char strBuffer[1024 * 4] = {0};
    strcat(strBuffer,av_version_info());
    return env->NewStringUTF(strBuffer);
}




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
