package com.hikvision.ffmpegdemo;

import java.util.Vector;

public class ZZFFmpeg {
    static {
        System.loadLibrary("learn-ffmpeg");
    }

    /**
     * 获取版本
     * @return
     */
    public static String GetFFmpegVersion() {
        return native_getFFmpegVersion();
    }
    private static native String native_getFFmpegVersion();

    /**
     * JNI功能测试 传递vector
     * @param vector
     */
    public static native void native_vectorTest(Vector<String> vector);


}
