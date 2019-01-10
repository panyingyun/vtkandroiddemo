//JavaNavieLib.cpp

#include <jni.h>
#include "com_michaelapp_demo1_JavaNativeLib.h"


/*
 * Class:     com_michaelapp_demo1_JavaNativeLib
 * Method:    stringFromJNI
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_com_michaelapp_demo1_JavaNativeLib_stringFromJNI
  (JNIEnv *env, jobject obj){
    std::string hello = "JavaNativeLib Here!";
    return env->NewStringUTF(hello.c_str());
}

/*
 * Class:     com_michaelapp_demo1_JavaNativeLib
 * Method:    add
 * Signature: (II)I
 */
JNIEXPORT jint JNICALL Java_com_michaelapp_demo1_JavaNativeLib_add
  (JNIEnv *env, jobject obj, jint a, jint b){
    return a+b;
}
