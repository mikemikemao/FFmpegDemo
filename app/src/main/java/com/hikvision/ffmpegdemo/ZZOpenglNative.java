package com.hikvision.ffmpegdemo;

/**
 * description ： TODO:类的作用
 * author : 海賊王　私失敗しないので
 * param
 * date : 2022/4/27 16:06
 */
public class ZZOpenglNative {
    /**
     * opengl native
     * @return
     */
    public static final int SAMPLE_TYPE  =  200;
    public static final int SAMPLE_TYPE_TRIANGLE                = SAMPLE_TYPE;
    public static final int SAMPLE_TYPE_TEXTURE_MAP             = SAMPLE_TYPE + 1;
    public static final int SAMPLE_TYPE_NV21_MAP                = SAMPLE_TYPE + 2;

    public static native void native_OnSurfaceCreated();
    public static native void native_OnSurfaceChanged(int width, int height);
    public static native void native_OnDrawFrame();
    public static native void native_SetParamsInt(int paramType, int value0, int value1);
    public static native void native_SetImageData(int format, int width, int height, byte[] bytes);
}
