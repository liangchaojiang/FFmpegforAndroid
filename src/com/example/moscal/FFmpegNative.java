package com.example.moscal;


public class FFmpegNative {
	static{
			System.loadLibrary("avutil-51");
			System.loadLibrary("avcodec-53");
			System.loadLibrary("swresample-0");
			System.loadLibrary("avformat-53");
			System.loadLibrary("swscale-2");
			System.loadLibrary("avfilter-2");
			System.loadLibrary("ffmpeg_codec");
		}
	public native int avcodec_find_decoder(String inputurl);

}