package com.hikvision.ffmpegdemo.audio;

import android.os.Bundle;
import android.view.View;

import androidx.appcompat.app.AppCompatActivity;

import com.hikvision.ffmpegdemo.R;

/**
 * description ： TODO:类的作用
 * author : pirate
 * param
 * date : 2022/4/6 10:48
 */
public class AudioActivity extends AppCompatActivity implements View.OnClickListener{

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        findViewById(R.id.tv_playPCM).setOnClickListener(this);
    }

    @Override
    public void onClick(View v) {
        switch (v.getId()) {
            case R.id.tv_playPCM:
                break;
            default:
                break;
        }
    }

}
