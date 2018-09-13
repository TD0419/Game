package com.example.student.game;

import android.content.Context;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.graphics.Canvas;
import android.graphics.Color;
import android.graphics.Paint;
import android.graphics.PorterDuff;
import android.graphics.Typeface;
import android.opengl.GLSurfaceView;
import android.util.Log;
import android.view.SurfaceHolder;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

public class MainSurface extends GLSurfaceView implements GLSurfaceView.Renderer
{
    static {
        System.loadLibrary("native-lib");
    }

    public static class Object_Data
    {
        private float position_x;
        private float position_y;
        private float graphic_width;
        private float graphic_height;
        private int draw_number;

        public Object_Data(float pos_x, float pos_y)
        {
            this.position_x = pos_x;
            this.position_y = pos_y;
        }

        public Object_Data(float pos_x, float pos_y, float gra_width, float gra_height, int number)
        {
            this(pos_x, pos_y);
            this.graphic_width = gra_width;
            this.graphic_height = gra_height;
            this.draw_number = number;
        }

        public float GetPosX()
        {
            return position_x;
        }

        public float GetPosY()
        {
            return position_y;
        }

        public float GetGraWidth()
        {
            return graphic_width;
        }

        public float GetGraHeight()
        {
            return graphic_height;
        }

        public int GetDrawNumber()
        {
            return draw_number;
        }
    }

    native private void setNdkPixels(int[] pixels, int width, int height, int size, int drawnumber);
    native private void onNdkCreated(int drawnumber);
    native private void onNdkChanged(int width, int height);
    native private void onNdkClear();
    native private void onNdkDraw(float x, float y, float width, float height,int drawnumber);
    native private void ndkFinalize(int number);

    //native private void onNdkPlayerUpdate(float x, float y, float width, float height, float touch_x, float touch_y, int drawnumber);
    //native private void onNdkPlayerUpdate(float x, float y, float width, float height,int drawnumber);
    //native private void onNdkPlayerUpdate(Object_Data obj_data);
    native private void onNdkPlayerUpdate(Object[] objects);

    private float m_tap_x = 0.f;
    private float m_tap_y = 0.f;
    private int m_width = 0;
    private int m_height = 0;

    public MainSurface(Context context)
    {
        super(context);

        // ビットマップ情報作成
        StringBitmap("文字描画サンプル", 20, 0, 100,0);
        TextureBitmap(0, 0, 1);

        //Object_Data obj_data = new Object_Data();
        //onNdkPlayerUpdate(obj_data);
        Object[] objects = { new Float(0.f), new Float(0.f), new Float(0.f), new Float(0.f), new Integer(0) };
        //onNdkPlayerUpdate(objects);
        for(int i = 0; i < 5; i++)
            Log.d("test", objects[i].toString());
    }

    @Override
    public void onSurfaceCreated(GL10 gl, EGLConfig config){ }

    @Override
    public void onSurfaceChanged(GL10 gl, int width, int height)
    {
        m_width = width;
        m_height = height;
        onNdkChanged(width, height);
    }

    @Override
    public void onDrawFrame(GL10 gl)
    {
        float x = 0.f, y = 0.f, width = 0.f, height = 0.f;
        int drawnumber = 0;

        //onNdkPlayerUpdate(0.f, 0.f, 0.f, 0.f, 0.f, 0.f, drawnumber);
        //onNdkPlayerUpdate(x, y, width, height, drawnumber);

        // 描画クリア
        onNdkClear();

        // "文字サンプル"文字列描画
        onNdkCreated(0);
        onNdkDraw(0, 0, 1,1.5f,0);

        // image画像を描画
        onNdkCreated(1);
        onNdkDraw(m_tap_x, m_tap_y, 1.f, 1.f, 1);
    }

    @Override
    public void surfaceDestroyed(SurfaceHolder holder)
    {

        ndkFinalize(0);
        ndkFinalize(1);
        super.surfaceDestroyed(holder);
    }

    public void TextureBitmap(int x, int y, int number)
    {
        final BitmapFactory.Options opts = new BitmapFactory.Options();
        opts.inScaled = false;
        opts.inPreferredConfig = Bitmap.Config.ARGB_8888;
        Bitmap bmp = BitmapFactory.decodeResource(getResources(), R.drawable.images, opts);
        int width = bmp.getWidth();
        int height = bmp.getHeight();
        int size = width * height;
        int pixels[] = new int[size];
        bmp.getPixels(pixels, 0, width, 0, 0, width, height);
        bmp.recycle();
        setNdkPixels(pixels, width, height, size, number);
    }


    // 文字列データを取得
    public void StringBitmap(String str, int font_size, int x, int y, int number)
    {
        Bitmap bmp = Bitmap.createBitmap(256, 256, Bitmap.Config.ARGB_8888);
        {
            Canvas canvas = new Canvas(bmp);
            Paint paint = new Paint();
            paint.setColor(Color.BLUE);
            paint.setStyle(Paint.Style.FILL);
            paint.setTextSize(font_size);
            canvas.drawColor(Color.TRANSPARENT, PorterDuff.Mode.CLEAR);
            paint.setTypeface(Typeface.DEFAULT_BOLD);
            canvas.drawText(str, 0, 128, paint);
        }
        int width = bmp.getWidth();
        int height = bmp.getHeight();
        int size = width * height;
        int pixels[] = new int[size];
        bmp.getPixels(pixels, 0, width, 0, 0, width, height);
        bmp.recycle();
        setNdkPixels(pixels, width, height, size, number);
    }

    public void TouchEvent(float x, float y)
    {
        m_tap_x = (x / m_width) * 2.f - 1.f;
        m_tap_y = (y / m_height) * -2.f + 1.f;
    }
}