//
// Created by PC-USER on 2018/08/15.
//

#include <jni.h>
#include "Player.h"

//
extern "C" JNIEXPORT
void JNICALL Java_com_example_student_game_MainSurface_onNdkPlayerUpdate(JNIEnv *env, jobject,
 //jfloat x, jfloat y, jfloat width, jfloat height,jint drawnumber)
jobjectArray obj_data)
//jobject  obj_data)
{
//    width = 1.f;
//    height = 1.f;
//    drawnumber = 1;

    //http://d.hatena.ne.jp/Kazuhira/20110820/1313813194
    jclass integerClass = env->FindClass("com/example/student/game");
    jmethodID integerConstructor = env->GetMethodID(integerClass, "<init>", "(I)V");
    //jmethodID intValueMethod = env->GetMethodID(integerClass, "intValue", "()I");

    env->SetObjectArrayElement(obj_data, 0, env->NewObject(integerClass, integerConstructor, 0.f));
    env->SetObjectArrayElement(obj_data, 1, env->NewObject(integerClass, integerConstructor, 1.f));
    env->SetObjectArrayElement(obj_data, 2, env->NewObject(integerClass, integerConstructor, 2.f));
    env->SetObjectArrayElement(obj_data, 3, env->NewObject(integerClass, integerConstructor, 3.f));
    env->SetObjectArrayElement(obj_data, 4, env->NewObject(integerClass, integerConstructor, 0));


//    jclass object_Class = env->FindClass("MainSurface$Object_Data");
//    jmethodID getFloatPosXMethod, getFloatPosYMethod;
//    jmethodID object_Constructor;

}
