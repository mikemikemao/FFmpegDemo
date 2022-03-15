package com.hikvision.ffmpegdemo.cam;

import android.os.Bundle;
import android.util.Log;

import androidx.appcompat.app.AppCompatActivity;

import com.hikvision.ffmpegdemo.R;
import com.hikvision.ffmpegdemo.ZZFFmpeg;

/**
 * description ： TODO:类的作用
 * author : pirate
 * param
 * date : 2022/3/15 14:32
 */
public class V4L2CamActivity  extends AppCompatActivity {
    private static String TAG = "V4L2CamActivity";
    ZZFFmpeg zzfFmpeg;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_v4l2_cam);
        zzfFmpeg = new ZZFFmpeg();
        Resolution resolution = new Resolution();
        zzfFmpeg.native_GetV4l2CamSolution();
        Log.d(TAG, "resolution width="+ resolution.getWidth() +"height=" + resolution.getHeight());

    }


}
