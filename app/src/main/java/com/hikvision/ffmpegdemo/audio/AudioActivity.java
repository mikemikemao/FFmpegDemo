package com.hikvision.ffmpegdemo.audio;

import android.content.res.AssetManager;
import android.media.AudioDeviceInfo;
import android.media.AudioManager;
import android.os.Build;
import android.os.Bundle;
import android.util.Log;
import android.view.View;

import androidx.annotation.RequiresApi;
import androidx.appcompat.app.AppCompatActivity;

import com.hikvision.ffmpegdemo.R;

/**
 * description ： TODO:类的作用
 * author : pirate
 * param
 * date : 2022/4/6 10:48
 */
public class AudioActivity extends AppCompatActivity implements View.OnClickListener{
    private static final String TAG = "AudioActivity";
    AssetManager assetManager;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_audio);
        findViewById(R.id.tv_playPCM).setOnClickListener(this);
        findViewById(R.id.tv_getAudioCurve).setOnClickListener(this);
        assetManager=getAssets();
    }


    @Override
    public void onClick(View v) {
        switch (v.getId()) {
            case R.id.tv_playPCM:
                break;
            case R.id.tv_getAudioCurve://API28 android9以上能用 以下用dumpsys media.audio_policy代替
                AudioManager audioManager = (AudioManager) getSystemService(this.AUDIO_SERVICE);
                int minIndex = 0;
                int maxIndex = 0;
                if (android.os.Build.VERSION.SDK_INT >= android.os.Build.VERSION_CODES.P) {
                    minIndex = audioManager.getStreamMinVolume (AudioManager.STREAM_MUSIC);
                    maxIndex = audioManager.getStreamMaxVolume (AudioManager.STREAM_MUSIC);
                    for(int i=minIndex+1; i<maxIndex; i++) {
                        float db = audioManager.getStreamVolumeDb(AudioManager.STREAM_MUSIC, i, AudioDeviceInfo.TYPE_WIRED_HEADSET);
                        Log.d(TAG, "volume db = " + db + "  at index= " + i);
                    }
                }else {
                    Log.d(TAG, "API28 android9以上能用 以下用dumpsys media.audio_policy代替");
                }


                break;
            default:
                break;
        }
    }

}
