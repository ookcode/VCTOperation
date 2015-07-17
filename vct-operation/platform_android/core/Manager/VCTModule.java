package Manager;

import java.lang.reflect.Method;
import java.util.HashMap;

import android.util.Log;

public class VCTModule {
	private String mModuleName;
	HashMap<String, Method> mMethodMap = new HashMap<String, Method>();  
	public VCTModule(String moduleName){
		mModuleName = moduleName;
	}
	
	public String GetModuleName(){
		return mModuleName;
	}
	
	public void RegisterMethod(String methodName,String localMethodName)
	{
		//反射通过方法名获取方法
		Class<? extends VCTModule> obj = this.getClass(); 
		Method method;
		try {
			method = obj.getDeclaredMethod(localMethodName, String.class, String.class);
			mMethodMap.put(methodName, method);
		} catch (SecurityException e) {
			e.printStackTrace();
		} catch (NoSuchMethodException e) {
			e.printStackTrace();
		} 
	}
	
	public String Execute(final String methodName,final String param,final String callback)
	{
		Method method = mMethodMap.get(methodName);
		do {
			if(!mMethodMap.containsKey(methodName)) {
				break;
			}
			try {
				String result = (String) method.invoke(this,param,callback);
				return result;
			} catch (Exception e) {
				e.printStackTrace();
			}
		} while(false);
		
		Log.i("AndroidLog","method " + methodName + " not found");
		return "0";
	}
}
