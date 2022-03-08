package com.hikvision.ffmpegdemo;

import android.os.Bundle;
import android.os.Environment;
import android.util.Log;
import android.view.SurfaceHolder;
import android.widget.SeekBar;

import androidx.annotation.NonNull;
import androidx.annotation.Nullable;
import androidx.appcompat.app.AppCompatActivity;

import com.hikvision.ffmpegdemo.media.MySurfaceView;

import java.util.Vector;

import static com.hikvision.ffmpegdemo.ZZFFmpeg.VIDEO_RENDER_ANWINDOW;

/**
 * description ： TODO:类的作用
 * author : pirate
 * param
 * date : 2022/3/2 16:59
 */
public class NativeMediaPlayerActivity extends AppCompatActivity implements SurfaceHolder.Callback {
    private static String TAG = "NativeMediaPlayerActivity";
    private ZZFFmpeg zzfFmpeg = null;
    private MySurfaceView mSurfaceView = null;
    private SeekBar mSeekBar = null;
    private boolean mIsTouch = false;
    private String mVideoPath = Environment.getExternalStorageDirectory().getAbsolutePath() + "/byteflow/one_piece.mp4";
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_media_player);
        mSurfaceView = findViewById(R.id.surface_view);
        mSurfaceView.getHolder().addCallback(this);
        mSeekBar = findViewById(R.id.seek_bar);
        mSeekBar.setOnSeekBarChangeListener(new SeekBar.OnSeekBarChangeListener() {
            @Override
            public void onProgressChanged(SeekBar seekBar, int progress, boolean fromUser) {

            }

            @Override
            public void onStartTrackingTouch(SeekBar seekBar) {
                mIsTouch = true;
            }

            @Override
            public void onStopTrackingTouch(SeekBar seekBar) {
                Log.d(TAG, "onStopTrackingTouch() called with: progress = [" + seekBar.getProgress() + "]");
                if(zzfFmpeg != null) {
                    //zzfFmpeg.seekToPosition(mSeekBar.getProgress());
                    mIsTouch = false;
                }

            }
        });
    }

    @Override
    public void surfaceCreated(@NonNull SurfaceHolder holder) {
        Log.d(TAG, "surfaceCreated() called with: surfaceHolder = [" + holder + "]");
        zzfFmpeg = new ZZFFmpeg();
        //zzfFmpeg.addEventCallback(this);
        zzfFmpeg.init(mVideoPath, VIDEO_RENDER_ANWINDOW, holder.getSurface());
    }

    @Override
    public void surfaceChanged(@NonNull SurfaceHolder holder, int format, int width, int height) {
        Log.d(TAG, "surfaceChanged() called with: surfaceHolder = [" + holder + "], format = [" + format + "], w = [" + width + "], h = [" + height + "]");
        //zzfFmpeg.play();
    }

    @Override
    public void surfaceDestroyed(@NonNull SurfaceHolder holder) {
        Log.d(TAG, "surfaceDestroyed() called with: surfaceHolder = [" + holder + "]");
        //zzfFmpeg.stop();
        //zzfFmpeg.unInit();
    }
}
