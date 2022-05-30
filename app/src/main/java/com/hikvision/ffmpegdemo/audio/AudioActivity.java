package com.hikvision.ffmpegdemo.audio;

import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.content.IntentFilter;
import android.content.res.AssetManager;
import android.media.AudioDeviceInfo;
import android.media.AudioManager;
import android.os.Build;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.Toast;

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
    HeadsetDetectReceiver mHeadsetDetectReceiver;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_audio);
        findViewById(R.id.tv_playPCM).setOnClickListener(this);
        findViewById(R.id.tv_getAudioCurve).setOnClickListener(this);
        assetManager=getAssets();
        //注册
        mHeadsetDetectReceiver = new HeadsetDetectReceiver();
        IntentFilter intentFilter = new IntentFilter();
        intentFilter.addAction("android.intent.action.HEADSET_PLUG");
        registerReceiver(mHeadsetDetectReceiver, intentFilter);
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

    public class HeadsetDetectReceiver extends BroadcastReceiver {
        @Override
        public void onReceive(Context context, Intent intent) {
            if (intent.hasExtra("state")) {
                if (intent.getIntExtra("state", 0) == 0) {
                    Toast.makeText(context, "没有插入耳机", Toast.LENGTH_SHORT).show();
                } else if (intent.getIntExtra("state", 0) == 1) {
                    Toast.makeText(context, "耳机已插入", Toast.LENGTH_SHORT).show();
                }
            }

        }
    }


    @Override
    protected void onDestroy() {
        unregisterReceiver(mHeadsetDetectReceiver);
        super.onDestroy();
    }

}
