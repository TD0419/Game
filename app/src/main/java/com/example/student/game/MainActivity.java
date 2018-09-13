package com.example.student.game;

import android.app.Activity;
import android.opengl.GLSurfaceView;
import android.os.Bundle;
import android.view.MotionEvent;
import android.view.Window;

public class MainActivity extends Activity {

    private MainSurface surface = null;

    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        requestWindowFeature(Window.FEATURE_NO_TITLE); //タイトルバー非表示
    }

    @Override
    protected void onResume() {
        super.onResume();
        surface = new MainSurface(this);
        surface.setRenderer(surface);
        surface.setFocusable(true);
        surface.setKeepScreenOn(true);
        setContentView(surface);
    }

    @Override
    protected void onPause() {
        super.onPause();
        surface.setKeepScreenOn(false);
    }

    @Override
    public boolean onTouchEvent(MotionEvent event) {
        switch (event.getAction()) {
            case MotionEvent.ACTION_DOWN:
                surface.TouchEvent(event.getX(), event.getY());
                break;
        }
        return true;
    }
}