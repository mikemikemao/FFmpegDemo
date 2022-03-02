package com.hikvision.ffmpegdemo;

import androidx.appcompat.app.AppCompatActivity;
import androidx.recyclerview.widget.LinearLayoutManager;
import androidx.recyclerview.widget.RecyclerView;

import android.os.Bundle;
import android.widget.TextView;

import com.hikvision.ffmpegdemo.adapter.SelectItem;
import com.hikvision.ffmpegdemo.adapter.SelectItemAdapter;

import java.util.ArrayList;
import java.util.List;

public class MainActivity extends AppCompatActivity {
    private List<SelectItem> selectItemList = new ArrayList<>();
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        ((TextView)findViewById(R.id.text_title)).setText("FFmpeg Version "+ZZFFmpeg.GetFFmpegVersion());
        initItems();
        RecyclerView recyclerView = (RecyclerView) findViewById(R.id.recycler_view);
        LinearLayoutManager layoutManager = new LinearLayoutManager(this);
        recyclerView.setLayoutManager(layoutManager);
        SelectItemAdapter adapter = new SelectItemAdapter(selectItemList);
        recyclerView.setAdapter(adapter);
    }

    private void initItems() {
        SelectItem foregroundItem = new SelectItem("ANativeWinodow player", R.drawable.lufei);
        selectItemList.add(foregroundItem);

    }
}