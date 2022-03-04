package com.hikvision.ffmpegdemo.media;

import android.content.Context;
import android.util.AttributeSet;
import android.view.SurfaceView;

/**
 * description ： TODO:类的作用
 * author : pirate
 * param
 * date : 2022/3/2 18:51
 */
public class MySurfaceView extends SurfaceView {
    private static final String TAG = "MySurfaceView";
    private int mRatioWidth = 0;
    private int mRatioHeight = 0;
    public MySurfaceView(Context context) {
        super(context);
    }

    public MySurfaceView(Context context, AttributeSet attrs) {
        super(context, attrs);
    }

    public MySurfaceView(Context context, AttributeSet attrs, int defStyleAttr) {
        super(context, attrs, defStyleAttr);
    }

}
