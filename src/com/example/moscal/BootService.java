package com.example.moscal;

import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;
import java.nio.channels.FileLock;

import android.app.Service;
import android.content.Context;
import android.content.Intent;
import android.os.Bundle;
import android.os.IBinder;
import android.util.Log;

public class BootService extends Service{

	String data;
	boolean running = false;

	@Override
	public IBinder onBind(Intent arg0) {
		// TODO Auto-generated method stub
		return null;
	}
    public int onStartCommand(Intent intent,int flag,int startId){
        super.onStartCommand(intent, flag, startId);
        Bundle bundle = (Bundle)intent.getExtras();
        String str1=bundle.getString("strpcap");
        String inputurl = str1;
        
        try {
			FileLock fl = new FileOutputStream("/sdcard/mos.txt",true).getChannel().lock();
			startThread(inputurl);  
			fl.release();
		} catch (FileNotFoundException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
        
        
        return START_NOT_STICKY;
    }
	
	public void onCreate()
	{
		Log.i("PCAP_CAPTURE","Æô¶¯serviceÍê³É [>_<]"+data);
	}
	
	//create a thread to finish the task which cost too many time
	public void startThread(final String inputur){
		new Thread(new Runnable(){
			
			@Override
			public void run() {
				// TODO Auto-generated method stub
		        FFmpegNative ffmpeg = new FFmpegNative();
		        int res = ffmpeg.avcodec_find_decoder(inputur);
		        Intent intent1 = new Intent();
		        intent1.setAction("MOS_PARSE_COMPLETED");
		        intent1.putExtra("pcapname", inputur);
		        BootService.this.sendBroadcast(intent1);
		        Log.i("res","res is:"+res+inputur);
			}
			
		}).start();
	}
	
}
