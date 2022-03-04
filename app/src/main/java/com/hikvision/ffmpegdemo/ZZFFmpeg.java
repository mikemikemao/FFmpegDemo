package com.hikvision.ffmpegdemo;

import java.util.Vector;

public class ZZFFmpeg {
    static {
        System.loadLibrary("learn-ffmpeg");
    }
    public static String GetFFmpegVersion() {
        return native_GetFFmpegVersion();
    }
    private static native String native_GetFFmpegVersion();

}
