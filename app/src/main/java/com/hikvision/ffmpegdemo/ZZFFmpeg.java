package com.hikvision.ffmpegdemo;

import android.view.Surface;

import java.util.Vector;

public class ZZFFmpeg {
    public static final int VIDEO_RENDER_OPENGL         = 0;
    public static final int VIDEO_RENDER_ANWINDOW       = 1;
    public static final int VIDEO_RENDER_3D_VR          = 2;

    public static final int FFMEDIA_PLAYER = 0;
    public static final int HWCODEC_PLAYER = 1;

    public static final int MSG_DECODER_INIT_ERROR      = 0;
    public static final int MSG_DECODER_READY           = 1;
    public static final int MSG_DECODER_DONE            = 2;
    public static final int MSG_REQUEST_RENDER          = 3;
    public static final int MSG_DECODING_TIME           = 4;
    static {
        System.loadLibrary("learn-ffmpeg");
    }
    //控制播放的句柄
    private long mNativePlayerHandle = 0;

   //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /**
     * FFMPEG
     * @return
     */
    public static String GetFFmpegVersion() {
        return native_getFFmpegVersion();
    }

    public void init(String url, int videoRenderType, Surface surface) {
        mNativePlayerHandle = native_Init(url, FFMEDIA_PLAYER, videoRenderType, surface);
    }

    public void play() {
        native_Play(mNativePlayerHandle);
    }

    public long getMediaParams(int paramType) {
        return native_GetMediaParams(mNativePlayerHandle, paramType);
    }

    private EventCallback mEventCallback = null;
    public void addEventCallback(EventCallback callback) {
        mEventCallback = callback;
    }


    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /**
     * opengl native
     * @return
     */
    public static native void native_OnSurfaceCreated();
    public static native void native_OnSurfaceChanged(int width, int height);
    public static native void native_OnDrawFrame();
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /**
     * FFmpegNative
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

    private native void native_Play(long playerHandle);


    private native long native_GetMediaParams(long playerHandle, int paramType);
    /**
     * JNI功能测试 传递vector
     * @param vector
     */
    public static native void native_vectorTest(Vector<String> vector);

    public interface EventCallback {
        void onPlayerEvent(int msgType, float msgValue);
    }

    private void playerEventCallback(int msgType, float msgValue) {
        if(mEventCallback != null)
            mEventCallback.onPlayerEvent(msgType, msgValue);

    }


}
