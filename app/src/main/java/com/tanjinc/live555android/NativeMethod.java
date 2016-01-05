package com.tanjinc.live555android;

import android.util.Log;

/**
 * Created by tanjinc on 15-12-28.
 */
public class NativeMethod {
    private static final String TAG = "NativeMethod";

    static {
        System.loadLibrary("live555");
        System.loadLibrary("mytest");
    }

    public String sayHello() {
        Log.d(TAG, "sayHello");
        return "sayHello" + stringFromJNI();
    }

    public boolean startRTSPServer2() {
        int ret = startRTSPServer();
        Log.d(TAG, "startRTSPServer ret=" + ret);
        return ret > 0;
    }
    public static native String stringFromJNI();
    public static native int startRTSPServer();
}
