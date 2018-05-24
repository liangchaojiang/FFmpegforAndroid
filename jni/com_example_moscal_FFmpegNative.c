#include <stdio.h>
#include <jni.h>
#include "libavcodec/avcodec.h"
#include "libavformat/avformat.h"
#include "libavutil/avutil.h"
#include "libavutil/log.h"
#include "ParsePcap.h"


#ifdef ANDROID
#include <jni.h>
#include <android/log.h>
#define LOGE(format, ...)  __android_log_print(ANDROID_LOG_ERROR, "(>_<)", format, ##__VA_ARGS__)
#define LOGI(format, ...)  __android_log_print(ANDROID_LOG_INFO,  "(=_=)", format, ##__VA_ARGS__)
#else
#define LOGE(format, ...)  printf("(>_<) " format "\n", ##__VA_ARGS__)
#define LOGI(format, ...)  printf("(^_^) " format "\n", ##__VA_ARGS__)
#endif


JNIEXPORT jint JNICALL Java_com_example_moscal_FFmpegNative_avcodec_1find_1decoder
  (JNIEnv *env, jobject obj, jstring input_jstr)
{


    AVFormatContext *pFormatCtx;
    AVCodecContext *pCodecCtx;
    AVCodec         *pCodec;
    AVFrame *pFrame;
    AVPacket    *packet;

    int i,videoindex;

    int ret,got_picture;

    char input_str[500]={0};

    FILE *fp = fopen("/sdcard/qp_skip.txt","wb+");

    FILE * fw;
    if((fw = fopen("/sdcard/mos.txt","a+"))==NULL)
    {
    	LOGE("Couldn't open input mos.txt\n");
    }else LOGI("open mos.txt success \n");
    char buffer_qp[50] = {0};
    char buffer_mos[20] = {0};
    sprintf(input_str,"%s",(*env)->GetStringUTFChars(env,input_jstr, NULL));

    Pcap_To_Ts(input_str, "/sdcard/out.ts");

    av_register_all();
    avformat_network_init();
    pFormatCtx = avformat_alloc_context();

    if(avformat_open_input(&pFormatCtx,"/sdcard/out.ts",NULL,NULL)!=0)
    {
    	LOGE("Couldn't open input stream,input_str is %s.\n","/sdcard/out.ts");
        return -8;
    }
    if(avformat_find_stream_info(pFormatCtx,NULL)<0)
    {
        return -7;
    }
    videoindex = -1;
    for(i=0;i<pFormatCtx->nb_streams;i++)
    {
        if(pFormatCtx->streams[i]->codec->codec_type == AVMEDIA_TYPE_VIDEO)
        {
            videoindex=i;
            break;
        }

    }
    //printf("video index is %d\n",videoindex);
    LOGI("video index is %d\n",videoindex);
    if(videoindex==-1)
    {
        return -6;
    }

    pCodecCtx=pFormatCtx->streams[videoindex]->codec;
    pCodec=avcodec_find_decoder(pCodecCtx->codec_id);

    if(pCodec==NULL){
        return -5;
    }
    if(avcodec_open2(pCodecCtx, pCodec,NULL)<0){
        return -4;
    }
    pFrame=(AVFrame*)av_malloc(sizeof(AVFrame));

    packet = (AVPacket*)av_malloc(sizeof(AVPacket));
    //av_dump_format(pFormatCtx,0,filepath,0);
    int frame_cnt = 0;
    float score_sum = 0;
    float score_avg = 0;
    while(av_read_frame(pFormatCtx,packet)>=0)
    {

        if(packet->stream_index==videoindex)
        {


//            /*packet,264stream*/
//
           int ret = avcodec_decode_video2(pCodecCtx,pFrame,&got_picture,packet);
        	LOGI("we in the frame %d ,%d",packet->size,pFrame->pict_type);
            /*if(ret<0)
            {
                return -3;
            }*/
//            if(got_picture)
//	    	{
//            	float score = 0;
//            	if(pFrame->width<700)
//            	 score = (141.5707 - 0.0032*pFrame->numskip_chao - 0.7335*pFrame->qp_chao)/30;
//				//if(pFrame->numskip_chao > 8000 && pFrame->numskip_chao < 10000 && score<=5)
//				//{
//            	else
//            	{
//            		if(pFrame->numskip_chao > 8000 && pFrame->numskip_chao < 10000 && score<=5)
//            		score = (141.5707 - 0.0032*pFrame->numskip_chao - 0.7335*pFrame->qp_chao)/20;
//            		else
//            		score = 4.5+(141.5707 - 0.0032*pFrame->numskip_chao - 0.7335*pFrame->qp_chao)/2000;
//
//            	}
//            		//if(score<=5)
//					//{
//						//printf("skip_num is %d, qp_num is %d\n",pFrame->numskip_chao,pFrame->qp_chao);
//						//LOGI("skip_num is %d, qp_num is %d\n",pFrame->numskip_chao,pFrame->qp_chao);
//						if(score<=5&&score>=3)
//						{
//							sprintf(buffer_qp,"%05.2f\n",score);
//							frame_cnt++;
//							score_sum += score;
//						}
//						fputs(buffer_qp,fp);
//
//
//						//return pFrame->qp_chao;
//						//printf("score is %f\n",score/20);
//					//}
//				//}


 //           }

        }

        av_free_packet(packet);
    }
    score_avg = score_sum / frame_cnt;
    LOGI("average score is %f\n",score_avg);
    sprintf(buffer_mos,"%05.2f\n",score_avg);
    fputs(buffer_mos,fw);

	fclose(fp);
	fclose(fw);
	avcodec_close(pCodecCtx);
	avformat_close_input(&pFormatCtx);
	return 1;
	//return (*env)->NewStringUTF("success");
}
