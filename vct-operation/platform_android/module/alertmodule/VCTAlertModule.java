package alertmodule;
import org.json.JSONException;
import org.json.JSONObject;

import android.app.Activity;
import android.app.AlertDialog;
import android.app.AlertDialog.Builder;
import android.content.DialogInterface;
import android.content.DialogInterface.OnClickListener;
import com.vincent.cocos2dx.VCTChannel;
import Manager.VCTModule;

public class VCTAlertModule extends VCTModule{
	private final static String MODULE_NAME = "alertmodule";
	private Activity mActivity;
	public VCTAlertModule(Activity activity){
		super(MODULE_NAME);
		mActivity = activity;
		this.RegisterMethod("show", "ShowAlertView");
	}
	public String ShowAlertView(final String param,final String callback){

		mActivity.runOnUiThread(new Runnable() { 
            public void run() {
            	try {
					JSONObject json = new JSONObject(param);
					String title = json.getString("title");
					String message = json.getString("message");
					Builder alert = new AlertDialog.Builder(mActivity);
					alert.setTitle(title);
					alert.setMessage(message);
					boolean leftExist = !json.isNull("leftbtn");
					boolean rightExist = !json.isNull("rightbtn");
					
					if(leftExist)
					{
						String leftbtn = json.getString("leftbtn");
						alert.setPositiveButton(leftbtn, new OnClickListener(){
							@Override
							public void onClick(DialogInterface arg0, int arg1) {
								VCTChannel.Response("0", callback);
							}
		               });
					}
					
					if(rightExist)
					{
						String rightbtn = json.getString("rightbtn");
						alert.setNegativeButton(rightbtn, new OnClickListener(){
							@Override
							public void onClick(DialogInterface arg0, int arg1) {
								// TODO Auto-generated method stub
								VCTChannel.Response("1", callback);
							}
		        		});
					}
					
					if(leftExist || rightExist) alert.show();
					
				} catch (JSONException e) {
					e.printStackTrace();
				}
            }
        });
		return "1";
	}
}
