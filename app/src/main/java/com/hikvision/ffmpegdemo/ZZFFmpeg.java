package com.hikvision.ffmpegdemo;

import android.view.Surface;

import java.util.Vector;

public class ZZFFmpeg {
    public static final int VIDEO_RENDER_OPENGL         = 0;
    public static final int VIDEO_RENDER_ANWINDOW       = 1;
    public static final int VIDEO_RENDER_3D_VR          = 2;

    public static final int FFMEDIA_PLAYER = 0;
    public static final int HWCODEC_PLAYER = 1;
    static {
        System.loadLibrary("learn-ffmpeg");
    }
    //控制播放的句柄
    private long mNativePlayerHandle = 0;

    /**
     * 获取版本
     * @return
     */
    public static String GetFFmpegVersion() {
        return native_getFFmpegVersion();
    }



    public void init(String url, int videoRenderType, Surface surface) {
        mNativePlayerHandle = native_Init(url, FFMEDIA_PLAYER, videoRenderType, surface);
    }

    /**
     * 获取版本
     * @return
     */
    private static native String native_getFFmpegVersion();

    /**
     * 播放器初始化
     * @param url 视频文件路径
     * @param playerType 编解码方式 FFmpeg 或mediacodec
     *     public static final int FFMEDIA_PLAYER = 0;
     *     public static final int HWCODEC_PLAYER = 1;
     * @param renderType 渲染方式
     *     public static final int VIDEO_RENDER_OPENGL         = 0;
     *     public static final int VIDEO_RENDER_ANWINDOW       = 1;
     *     public static final int VIDEO_RENDER_3D_VR          = 2;
     * @param surface
     * @return
     */
    private native long native_Init(String url, int playerType, int renderType, Object surface);
    /**
     * JNI功能测试 传递vector
     * @param vector
     */
    public static native void native_vectorTest(Vector<String> vector);


}
