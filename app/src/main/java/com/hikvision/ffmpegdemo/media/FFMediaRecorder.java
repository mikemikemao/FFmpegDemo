package com.hikvision.ffmpegdemo.media;

import android.opengl.GLSurfaceView;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

/**
 * description ： TODO:类的作用
 * author : 海賊王　私失敗しないので
 * param
 * date : 2022/5/23 19:32
 */
public class FFMediaRecorder extends MediaRecorderContext implements GLSurfaceView.Renderer{
    private static final String TAG = "FFMediaRecorder";
    private GLSurfaceView mGLSurfaceView;

    public FFMediaRecorder() {
    }

    public void init(GLSurfaceView surfaceView) { //for Video
        mGLSurfaceView = surfaceView;
        mGLSurfaceView.setEGLContextClientVersion(2);
        mGLSurfaceView.setRenderer(this);
        mGLSurfaceView.setRenderMode(GLSurfaceView.RENDERMODE_WHEN_DIRTY);

        native_CreateContext();
        native_Init();
    }

    @Override
    public void onSurfaceCreated(GL10 gl, EGLConfig config) {

    }

    @Override
    public void onSurfaceChanged(GL10 gl, int width, int height) {

    }

    @Override
    public void onDrawFrame(GL10 gl) {

    }
}
