package com.hikvision.ffmpegdemo.media;

/**
 * description ： TODO:类的作用
 * author : 海賊王　私失敗しないので
 * param
 * date : 2022/5/23 19:33
 */
public class MediaRecorderContext {

    protected native void native_CreateContext();

    protected native void native_DestroyContext();

    protected native int native_Init();
}
