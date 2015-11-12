package core.Manager;
import java.util.HashMap;

import module.alertmodule.VCTAlertModule;
import module.handlemodule.VCTHandleModule;
import module.sysmodule.VCTSysModule;

import android.app.Activity;
import android.util.Log;

public class VCTManager {
	private static VCTManager mInstance = null;
	HashMap<String, VCTModule> mModuleMap = new HashMap<String, VCTModule>();   
	private Activity mActivity = null;
	public static VCTManager getInstance(){
		if(mInstance == null){
			mInstance = new VCTManager();
		}
		return mInstance;
	}
	public void start(Activity activity){
		mActivity = activity;
		RegisterModule(VCTSysModule.getInstance(mActivity));
		RegisterModule(VCTAlertModule.getInstance(mActivity));
		RegisterModule(VCTHandleModule.getInstance());
	}
	public void RegisterModule(VCTModule module){
		mModuleMap.put(module.GetModuleName(), module);
	}
	public String Request(final String moduleName,final String methodName,final String param,final String callback){
		if(mModuleMap.containsKey(moduleName)){
			final VCTModule module = mModuleMap.get(moduleName);
			if(!callback.equals("")) {
				mActivity.runOnUiThread(new Runnable() { 
					public void run() {
						module.Execute(methodName, param, callback);
					}
	            });
			} else {
				String result = module.Execute(methodName, param, callback);
				return result;
			}
		}else {
			Log.i("AndroidLog","module " + moduleName + " not found");
		}
		return "";
	}
	private VCTManager(){
		
	};
}
