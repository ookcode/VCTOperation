package handlemodule;
import java.util.HashMap;
import android.util.Log;

import com.vincent.cocos2dx.VCTChannel;
import Manager.VCTModule;

public class VCTHandleModule extends VCTModule{
	
	private static VCTHandleModule mInstance = null;
	private final static String MODULE_NAME = "handlemodule";
	private HashMap<String, String> mCalbackMap = new HashMap<String, String>();
	
	public static VCTHandleModule getInstance(){
		if(mInstance == null){
			mInstance = new VCTHandleModule();
		}
		return mInstance;
	}
	
	private VCTHandleModule(){
		super(MODULE_NAME);
		this.RegisterMethod("register", "registerHandle");
		this.RegisterMethod("trigger", "triggerHandle");
	}
	
	public String registerHandle(final String param,final String callback){
		if(param.isEmpty()){
			Log.i("AndroidLog","[handlemodule] register must provide a param as a key");
			return "";
		}
		if(callback.isEmpty()){
			Log.i("AndroidLog","[handlemodule] register must provide a callback");
			return "";
		}
		mCalbackMap.put(param, callback);
		return "";
	}
	
	public String triggerHandle(final String param,final String callback){
		if(param.isEmpty()){
			Log.i("AndroidLog","[handlemodule] trigger must provide a param as a key");
			return "";
		}
		if(!mCalbackMap.containsKey(param)){
			Log.i("AndroidLog","[handlemodule] trigger " + param + " is not register");
			return "";
		}
		String registeredCallback =  mCalbackMap.get(param);
		mCalbackMap.remove(param);
		VCTChannel.Response("", registeredCallback);
		return "";
	}
}
