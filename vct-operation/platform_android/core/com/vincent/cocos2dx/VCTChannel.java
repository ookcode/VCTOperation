package com.vincent.cocos2dx;

import org.cocos2dx.lib.Cocos2dxActivity;
//import org.cocos2dx.lib.Cocos2dxGLSurfaceView;

import android.util.Log;

import Manager.VCTManager;

public class VCTChannel extends Cocos2dxActivity {
	
	public static native void Response(final String args,final String callback);
	
	public static String Request(final String moudle,final String method,final String args,final String callback) {
		Log.i("AndroidLog","**************Request**************");
		Log.i("AndroidLog","module = " + moudle);
		Log.i("AndroidLog","method = " + method);
		Log.i("AndroidLog","param = " + args);
	    Log.i("AndroidLog","cbaddress = " + callback);
	    Log.i("AndroidLog","***********************************");
    	String result = VCTManager.getInstance().Request(moudle, method, args, callback);
    	return result;
	}
}
