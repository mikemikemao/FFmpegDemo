package com.hikvision.ffmpegdemo;

import android.os.Bundle;
import android.util.Log;
import android.view.SurfaceHolder;

import androidx.annotation.NonNull;
import androidx.annotation.Nullable;
import androidx.appcompat.app.AppCompatActivity;

import com.hikvision.ffmpegdemo.media.MySurfaceView;

import java.util.Vector;

/**
 * description ： TODO:类的作用
 * author : pirate
 * param
 * date : 2022/3/2 16:59
 */
public class NativeMediaPlayerActivity extends AppCompatActivity implements SurfaceHolder.Callback {
    private static String TAG = "NativeMediaPlayerActivity";
    private MySurfaceView mSurfaceView = null;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_media_player);
        mSurfaceView = findViewById(R.id.surface_view);
        mSurfaceView.getHolder().addCallback(this);
    }

    @Override
    public void surfaceCreated(@NonNull SurfaceHolder holder) {

    }

    @Override
    public void surfaceChanged(@NonNull SurfaceHolder holder, int format, int width, int height) {

    }

    @Override
    public void surfaceDestroyed(@NonNull SurfaceHolder holder) {

    }
}
