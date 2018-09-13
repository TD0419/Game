#include <jni.h>
#include <GLES/gl.h>
#include <GLES/glext.h>
#include "glu.h"

// テクスチャ画像情報を入れる配列の要素数
#define TEXTURE_ARRAY_NUM (100)

//テクスチャの各定義
GLuint textures[TEXTURE_ARRAY_NUM];
unsigned char *texData[TEXTURE_ARRAY_NUM];


//テクスチャのサイズ
int texWidth[TEXTURE_ARRAY_NUM];
int texHeight[TEXTURE_ARRAY_NUM];

const GLfloat TexNormals[] =
        {
                0.f, 0.f, -1.f,
                0.f, 0.f, -1.f
        };

const GLfloat TexCoords[] =
        {
                0.0f, 0.0f,
                0.0f, 1.0f,
                1.0f, 0.0f,
                1.0f, 1.0f
        };

const int Vertexnum = 4;

extern "C" JNIEXPORT
void JNICALL Java_com_example_student_game_MainSurface_setNdkPixels (JNIEnv *env, jobject, jintArray pixels, jint width, jint height, jint size, jint number){
    texWidth[number] = width;
    texHeight[number] = height;

    // jintArrayをjint配列に変換
    jint* arr = env->GetIntArrayElements(pixels, NULL);

   texData[number] = new unsigned char[size * 4];
    for (int i=0; i<size; i++){
        int j = i * 4;
        texData[number][j + 2] = arr[i]; //Blue
        arr[i] >>= 8;
        texData[number][j + 1] = arr[i]; //Green
        arr[i] >>= 8;
        texData[number][j + 0] = arr[i]; //Red
        arr[i] >>= 8;
        texData[number][j + 3] = arr[i]; //Alpha
    }

    // jint配列を解放
    env->ReleaseIntArrayElements(pixels, arr, 0);
}

extern "C" JNIEXPORT
void JNICALL Java_com_example_student_game_MainSurface_setNdkRotate (JNIEnv *, jobject, jfloat x, jfloat y)
{

}

extern "C" JNIEXPORT
void JNICALL Java_com_example_student_game_MainSurface_onNdkCreated (JNIEnv *, jobject, jint drawnumber){
    //背景の色
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glClearDepthf(1.0);

    //片面スムーズシェーディング
    glShadeModel(GL_SMOOTH);

    //深度テスト
    glEnable(GL_DEPTH_TEST);

    //モデルビュー変換
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    //テクスチャ処理
    glGenTextures(1, textures);
    glBindTexture(GL_TEXTURE_2D, textures[drawnumber]);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texWidth[drawnumber], texHeight[drawnumber], 0, GL_RGBA,
                 GL_UNSIGNED_BYTE, texData[drawnumber]);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

extern "C" JNIEXPORT
void JNICALL Java_com_example_student_game_MainSurface_onNdkChanged (JNIEnv *, jobject, jint width, jint height){
    glViewport(0, 0, width, height);

    //射影変換
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrthof(-1.0f, 1.0f, -1.0f, 1.0f, 0.5f, -0.5f);

    //視点
    //gluPerspective(45, (float)width/(float)height, 0.1, 100);
    //gluLookAt(0, 0, 3, 0, 0, 0, 0, 1, 0);
}

extern "C" JNIEXPORT
void JNICALL Java_com_example_student_game_MainSurface_onNdkClear(JNIEnv *, jobject)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

extern "C" JNIEXPORT
void JNICALL Java_com_example_student_game_MainSurface_onNdkDraw (JNIEnv *, jobject,
 jfloat x, jfloat y, jfloat width, jfloat height, jint drawnumber)
{
    GLfloat TexVertexs[] =
            {
                    -0.5f + x, -0.5f + y + height, 0.0f,
                    -0.5f + x, -0.5f + y, 0.0f,
                    -0.5f + x + width, -0.5f + y + height, 0.0f,
                    -0.5f + x + width, -0.5f + y, 0.0f
            };

    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_NORMAL_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_ALPHA_TEST);

    //バナナを表示
    glAlphaFunc(GL_GEQUAL, 0.5);
    glBindTexture(GL_TEXTURE_2D, textures[drawnumber]);
    glVertexPointer(3, GL_FLOAT, 0, TexVertexs);
    glNormalPointer(GL_FLOAT, 0, TexNormals);
    glTexCoordPointer(2, GL_FLOAT, 0, TexCoords);
    glPushMatrix();
//    glRotatef(xrot, 0, 1, 0);
//    glRotatef(yrot, 1, 0, 0);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, Vertexnum);
    glPopMatrix();

    glDisable(GL_ALPHA8_EXT);
    glDisable(GL_TEXTURE_2D);
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
    glDisableClientState(GL_NORMAL_ARRAY);
    glDisableClientState(GL_VERTEX_ARRAY);
}

extern "C" JNIEXPORT
void JNICALL Java_com_example_student_game_MainSurface_ndkFinalize (JNIEnv *, jobject, jint number)
{
    delete [] texData[number];
}