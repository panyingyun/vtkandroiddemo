package com.michaelapp.demo1;

public class JavaNativeLib {
    static
    {
        System.loadLibrary("javanativelib");
    }
    public static native String stringFromJNI();
    public static native int  add(int a, int b);
}
