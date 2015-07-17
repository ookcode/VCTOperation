package Manager;
import java.util.HashMap;

import android.util.Log;

public class VCTManager {
	private static VCTManager mInstance = null;
	HashMap<String, VCTModule> mModuleMap = new HashMap<String, VCTModule>();   
	public static VCTManager getInstance(){
		if(mInstance == null){
			mInstance = new VCTManager();
		}
		return mInstance;
	}
	public void RegisterModule(VCTModule module){
		mModuleMap.put(module.GetModuleName(), module);
	}
	public String Request(final String moduleName,final String methodName,final String param,final String callback){
		if(mModuleMap.containsKey(moduleName))
		{
			VCTModule module = mModuleMap.get(moduleName);
			String result = module.Execute(methodName, param, callback);
			return result;
		}
		Log.i("AndroidLog","module " + moduleName + " not found");
		return "0";
	}
	private VCTManager(){
		
	};
}
