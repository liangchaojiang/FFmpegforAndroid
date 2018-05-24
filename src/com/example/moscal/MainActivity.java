package com.example.moscal;


import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;
import android.widget.TextView;
import android.widget.Toast;



public class MainActivity extends Activity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        
        final TextView tv=(TextView)this.findViewById(R.id.tv1);
        Button bt1 = (Button)this.findViewById(R.id.bt1);
        
        Intent intent = getIntent();
        Bundle bundle = intent.getExtras();
        final String str1 = bundle.getString("strpcap");
        tv.setText(str1);
        Toast.makeText(getApplicationContext(), str1, Toast.LENGTH_SHORT).show();
        
        bt1.setOnClickListener(new OnClickListener(){
        	public void onClick(View arg0){
   
                String inputurl = "/sdcard/"+str1;
                tv.setText(inputurl);
                FFmpegNative ffmpeg = new FFmpegNative();
                
                int res = ffmpeg.avcodec_find_decoder(inputurl);
                
                String i="null";
                if(res == 1)
                i="use lib succees";
                else if(res == -8)
                i="failed";
                else if(res>0)
                i="ok";
                tv.setText(i+res);
                Intent intent = new Intent();
                intent.setAction("MOS_PARSE_COMPLETED");
                intent.putExtra("mosname", "liangchao");
                MainActivity.this.sendBroadcast(intent);
                //Toast.makeText(getApplicationContext(), "send braodcast success", Toast.LENGTH_SHORT).show();
        	}
        });
        
    }


}
