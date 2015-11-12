package module.sysmodule;

import android.app.Activity;
import android.content.Context;
import android.content.Intent;
import android.content.pm.PackageInfo;
import android.content.pm.PackageManager;
import android.content.pm.PackageManager.NameNotFoundException;
import android.net.Uri;
import android.telephony.TelephonyManager;
import android.text.ClipboardManager;
import core.Manager.VCTModule;

public class VCTSysModule extends VCTModule{
	
	private static VCTSysModule mInstance = null;
	private final static String MODULE_NAME = "sysmodule";
	private Activity mActivity;
	
	public static VCTSysModule getInstance(Activity activity){
		if(mInstance == null){
			mInstance = new VCTSysModule(activity);
		}
		return mInstance;
	}
	
	private VCTSysModule(Activity activity){
		super(MODULE_NAME);
		mActivity = activity;
		this.RegisterMethod("getversion", "GetVersion");
		this.RegisterMethod("getudid", "GetUDID");
        //this.RegisterMethod("getosversion","");
        //this.RegisterMethod("getdevice","");
		this.RegisterMethod("copy","CopyToClipboard");
        this.RegisterMethod("parse","GetTextFromClipboard");
        this.RegisterMethod("webpageredirect", "WebPageRedirect");
	}

	public String WebPageRedirect(final String param,final String callback) {
		Uri uri = Uri.parse(param);  
		mActivity.startActivity(new Intent(Intent.ACTION_VIEW,uri));
		return "";
	}
	
	public String GetTextFromClipboard(final String param,final String callback) {
        ClipboardManager board = (ClipboardManager)mActivity.getSystemService(Context.CLIPBOARD_SERVICE);
        String text = board.getText().toString();
        return text;
    }
	
	public String CopyToClipboard(final String param,final String callback) {
		ClipboardManager board = (ClipboardManager)mActivity.getSystemService(Context.CLIPBOARD_SERVICE);
		board.setText(param);
		return "";
    }
	
	public String GetUDID(final String param,final String callback) {
		//使用IMEI作为设备唯一标识符
		TelephonyManager telephonyManager= (TelephonyManager) mActivity.getSystemService(Context.TELEPHONY_SERVICE);
		String imei = telephonyManager.getDeviceId();
		return imei;
	}

	public String GetVersion(final String param,final String callback) {
		String s = "1.0.0";
		PackageManager pm = mActivity.getPackageManager();
		PackageInfo pi;
		try {
			pi = pm.getPackageInfo(mActivity.getPackageName(), 0);
			s = pi.versionName;
		} catch (NameNotFoundException e) {
			e.printStackTrace();
		}
		return s;
	}
}
