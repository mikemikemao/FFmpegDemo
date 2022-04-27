package com.hikvision.ffmpegdemo.opengl;

import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.os.Bundle;

import androidx.appcompat.app.AppCompatActivity;

import com.hikvision.ffmpegdemo.R;

import java.io.IOException;
import java.io.InputStream;
import java.nio.ByteBuffer;

/**
 * description ： TODO:类的作用
 * author : pirate
 * param
 * date : 2022/3/8 09:35
 */
public class GLMediaPlayerActivity extends AppCompatActivity {
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_gl_media_player);
    }
}
