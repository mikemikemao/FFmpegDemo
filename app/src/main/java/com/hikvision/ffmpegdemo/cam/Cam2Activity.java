package com.hikvision.ffmpegdemo.cam;

import android.os.Bundle;

import androidx.annotation.Nullable;
import androidx.appcompat.app.AppCompatActivity;

import com.hikvision.ffmpegdemo.R;

/**
 * description ： TODO:类的作用
 * author : 海賊王　私失敗しないので
 * param
 * date : 2022/5/17 16:19
 */
public class Cam2Activity extends AppCompatActivity {
    private static String TAG = "Cam2Activity";

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_v4l2_cam);
    }
}
