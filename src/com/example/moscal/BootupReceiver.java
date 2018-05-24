package com.example.moscal;



import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.util.Log;

public class BootupReceiver extends BroadcastReceiver {
	
	private final String ACTION_BOOT= "android.intent.action.BOOT_COMPLETED";
	private final String PCAP_FINISH="PCAP_CATCH_COMPLETED";
	@Override
	public void onReceive(Context context, Intent intent) {
		// TODO Auto-generated method stub

		if(intent.getAction().equals(ACTION_BOOT))
		{
			Log.v("TAG","开机自动启动服务.....");
			Intent bootStartIntent = new Intent(context,BootService.class);
			bootStartIntent.addFlags(Intent.FLAG_ACTIVITY_NEW_TASK);
			context.startService(bootStartIntent);
		}else if(intent.getAction().equals(PCAP_FINISH)){
			Log.v("PCAP_CAPTURE","PCAP抓包完成 [>_<]");
			String pcapname = intent.getExtras().getString("pcapname");
			Intent parseStartIntent = new Intent(context,BootService.class);
			//parseStartIntent.addFlags(Intent.FLAG_ACTIVITY_NEW_TASK);
			parseStartIntent.putExtra("strpcap", pcapname);
			context.startService(parseStartIntent);
		}
	}
	
}
