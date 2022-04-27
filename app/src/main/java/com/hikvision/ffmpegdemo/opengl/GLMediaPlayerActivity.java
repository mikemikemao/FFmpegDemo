package com.hikvision.ffmpegdemo.opengl;

import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.view.ViewGroup;
import android.view.ViewTreeObserver;
import android.widget.RelativeLayout;

import androidx.appcompat.app.AppCompatActivity;

import com.hikvision.ffmpegdemo.R;

import java.io.IOException;
import java.io.InputStream;
import java.nio.ByteBuffer;

import static android.opengl.GLSurfaceView.RENDERMODE_WHEN_DIRTY;
import static com.hikvision.ffmpegdemo.ZZOpenglNative.SAMPLE_TYPE;
import static com.hikvision.ffmpegdemo.opengl.MyGLRender.IMAGE_FORMAT_RGBA;

/**
 * description ： TODO:类的作用
 * author : pirate
 * param
 * date : 2022/3/8 09:35
 */
public class GLMediaPlayerActivity extends AppCompatActivity implements View.OnClickListener, ViewTreeObserver.OnGlobalLayoutListener{
    private static final String TAG  = "GLMediaPlayerActivity";
    private MyGLSurfaceView mGLSurfaceView;
    private MyGLRender mGLRender;
    private ViewGroup mRootView;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_gl_media_player);
        Log.d(TAG, "onCreate: ");

        mRootView = (ViewGroup) findViewById(R.id.rootView);
        mRootView.getViewTreeObserver().addOnGlobalLayoutListener(this);
        mGLRender = new MyGLRender();
        mGLSurfaceView = new MyGLSurfaceView(GLMediaPlayerActivity.this,mGLRender);

        findViewById(R.id.tv_glTriangle).setOnClickListener(this);
        findViewById(R.id.tv_glTxtMap).setOnClickListener(this);
    }

    @Override
    public void onGlobalLayout() {
        Log.d(TAG, "onGlobalLayout: ");
        mRootView.getViewTreeObserver().removeOnGlobalLayoutListener(this);
        RelativeLayout.LayoutParams lp = new RelativeLayout.LayoutParams(
                ViewGroup.LayoutParams.MATCH_PARENT, ViewGroup.LayoutParams.MATCH_PARENT);
        lp.addRule(RelativeLayout.CENTER_IN_PARENT);
        mGLSurfaceView = new MyGLSurfaceView(this, mGLRender);
        mRootView.addView(mGLSurfaceView, lp);
        mGLSurfaceView.setRenderMode(RENDERMODE_WHEN_DIRTY);

    }

    @Override
    public void onClick(View v) {
        switch (v.getId()) {
            case R.id.tv_glTriangle:
                Log.d(TAG, "onClick: glTriangle");
                mGLRender.setParamsInt(SAMPLE_TYPE, SAMPLE_TYPE+0, 0);
                break;
            case R.id.tv_glTxtMap:
                Log.d(TAG, "onClick: glTxtMap");
                mGLRender.setParamsInt(SAMPLE_TYPE, SAMPLE_TYPE+1, 0);
                loadRGBAImage(R.drawable.dzzz);
                break;
            default:
                break;
        }

        mGLSurfaceView.requestRender();
    }



    private Bitmap loadRGBAImage(int resId) {
        InputStream is = this.getResources().openRawResource(resId);
        Bitmap bitmap;
        try {
            bitmap = BitmapFactory.decodeStream(is);
            if (bitmap != null) {
                int bytes = bitmap.getByteCount();
                ByteBuffer buf = ByteBuffer.allocate(bytes);
                bitmap.copyPixelsToBuffer(buf);
                byte[] byteArray = buf.array();
                mGLRender.setImageData(IMAGE_FORMAT_RGBA, bitmap.getWidth(), bitmap.getHeight(), byteArray);
            }
        }
        finally
        {
            try
            {
                is.close();
            }
            catch(IOException e)
            {
                e.printStackTrace();
            }
        }
        return bitmap;
    }
}
