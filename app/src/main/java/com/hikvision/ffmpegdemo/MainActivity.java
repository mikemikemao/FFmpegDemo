package com.hikvision.ffmpegdemo;

import androidx.appcompat.app.AppCompatActivity;
import androidx.recyclerview.widget.LinearLayoutManager;
import androidx.recyclerview.widget.RecyclerView;

import android.content.Intent;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.TextView;

import com.hikvision.ffmpegdemo.adapter.SelectItem;
import com.hikvision.ffmpegdemo.adapter.SelectItemAdapter;
import com.hikvision.ffmpegdemo.audio.AudioActivity;
import com.hikvision.ffmpegdemo.cam.V4L2CamActivity;

import java.util.ArrayList;
import java.util.List;

public class MainActivity extends AppCompatActivity {
    private static String TAG = "MainActivity";
    private List<SelectItem> selectItemList = new ArrayList<>();
    private static final int FF_ANATIVE_WINDOWS_EXAMPLE = 0;
    private static final int FF_OPENGLES_EXAMPLE = 1;
    private static final int V4L2CAM_EXAMPLE = 2;
    private static final int Audio_EXAMPLE = 3;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        ((TextView)findViewById(R.id.text_title)).setText("FFmpeg Version "+ZZFFmpeg.GetFFmpegVersion());
        initItems();
        RecyclerView recyclerView = (RecyclerView) findViewById(R.id.recycler_view);
        LinearLayoutManager layoutManager = new LinearLayoutManager(this);
        recyclerView.setLayoutManager(layoutManager);
        final SelectItemAdapter adapter = new SelectItemAdapter(selectItemList);
        recyclerView.setAdapter(adapter);
        adapter.addOnItemClickListener(new SelectItemAdapter.OnItemClickListener() {
            @Override
            public void onItemClick(View view, int position) {
                int selectIndex = adapter.getSelectIndex();
                adapter.setSelectIndex(position);
                adapter.safeNotifyItemChanged(selectIndex);
                adapter.safeNotifyItemChanged(position);
                Log.d(TAG, "onItemClick: " + position);
                switch (position) {
                    case FF_ANATIVE_WINDOWS_EXAMPLE:
                        startActivity(new Intent(MainActivity.this, NativeMediaPlayerActivity.class));
                        break;
                    case FF_OPENGLES_EXAMPLE:
                        startActivity(new Intent(MainActivity.this, GLMediaPlayerActivity.class));
                        break;
                    case V4L2CAM_EXAMPLE:
                        startActivity(new Intent(MainActivity.this, V4L2CamActivity.class));
                        break;
                    case Audio_EXAMPLE:
                        startActivity(new Intent(MainActivity.this, AudioActivity.class));
                        break;
                    default:
                        break;
                }
            }
        });
    }

    private void initItems() {
        SelectItem foregroundItem = new SelectItem("ANativeWinodow player", R.drawable.lufei);
        selectItemList.add(foregroundItem);
        SelectItem glTest = new SelectItem("glTest", R.drawable.opengl);
        selectItemList.add(glTest);
        SelectItem cam = new SelectItem("camera", R.drawable.cam);
        selectItemList.add(cam);
        SelectItem speaker = new SelectItem("speaker", R.drawable.laba);
        selectItemList.add(speaker);

    }
}