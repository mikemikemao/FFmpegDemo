package com.hikvision.ffmpegdemo.cam;

/**
 * description ： TODO:类的作用
 * author : pirate
 * param
 * date : 2022/3/15 15:26
 */
public class Resolution {
    private static int width;
    private static int height;
    public int getHeight() {
        return height;
    }
    public int getWidth() {
        return width;
    }
    public static void setHeight(int height) {
        Resolution.height = height;
    }

    public static void setWidth(int width) {
        Resolution.width = width;
    }
};
