package com.hikvision.ffmpegdemo.cam;

/**
 * description ： TODO:类的作用
 * author : 海賊王　私失敗しないので
 * param
 * date : 2022/5/17 16:38
 */
public interface Camera2FrameCallback {
    void onPreviewFrame(byte[] data, int width, int height);
    void onCaptureFrame(byte[] data, int width, int height);
}
