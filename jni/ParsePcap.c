#include <stdio.h>
#include <memory.h>
#include <stdlib.h>

#include "ParsePcap.h"
#include "ParseTs.h"

#include <jni.h>
#include <android/log.h>
#define LOGE(format, ...)  __android_log_print(ANDROID_LOG_ERROR, "(>_<)", format, ##__VA_ARGS__)
#define LOGI(format, ...)  __android_log_print(ANDROID_LOG_INFO,  "(=_=)", format, ##__VA_ARGS__)

int Pcap_To_Ts(char * Inputfile,char * Outputfile)
{
	static int pkt_offset;//which was used to skip to the next ip packet
	static int ts_start_indicator=0;
	static unsigned char udp_id;
//	static unsigned char udp_id1;/////

	//the next code was used to define the headers of Packet.Through parse header we can filter the data we want.
	PCAPHeader_t pcaphr;
	PKTHeader_t *pkt_header;
	ETHeader_t *eth_header;
	IPHeader_t *ip_header;
	UDPHeader_t *udp_header;
	RTPHeader_t *rtp_header;
	TS_PACKAGE_HEAD *ts_header;

	FILE *fop;//the file we will open
	FILE *fwp;//the file we will write
//	FILE *fwf;
	unsigned char * ts_data;

	/*the inition of the header*/
	pkt_header=malloc(sizeof(PKTHeader_t));
    eth_header=malloc(sizeof(ETHeader_t));
    ip_header=malloc(sizeof(IPHeader_t));
    udp_header=malloc(sizeof(UDPHeader_t));
    rtp_header=malloc(sizeof(RTPHeader_t));
    ts_header=malloc(sizeof(TS_PACKAGE_HEAD));
    ts_data = malloc(188);

    //open the file
    if((fop = fopen(Inputfile,"rb"))==NULL)
    {
    	LOGE("Couldn't open input pcapfile,input_str is %s.\n",Inputfile);
        exit(0);
    }else{LOGI("Success open input pcapfile,input_str is %s.\n",Inputfile);}
    //open and create the output file
    if((fwp = fopen(Outputfile,"wb"))==NULL)
    {
    	LOGE("Couldn't open output pcapfile,output_str is %s.\n",Outputfile);
        exit(0);
    }else{LOGI("Success open output pcapfile,output_str is %s.\n",Outputfile);}

//    if((fwf = fopen("/sdcard/out1.ts","wb"))==NULL)
//    {
//    	LOGE("Couldn't open output pcapfile,output_str is %s.\n",Outputfile);
//        exit(0);
//    }else{LOGI("Success open output pcapfile,out1 ts.\n");}
//

    pkt_offset = sizeof(PCAPHeader_t);
    /*use a loop to parse the value of pcap file and write the ts data to the ts file*/
    while(fseek(fop,pkt_offset,SEEK_SET)==0)
    {
    	if(fread(pkt_header,sizeof(PKTHeader_t),1,fop)!=1)
    	{
    		LOGI("Open input pcapfile finish.\n");
    		break;
    	}
    	pkt_offset += 16+pkt_header->incl_len;//add 16 to skip the pkt header,so we can let pkt_offset point to the next packet,and fseek can find the next packet

    	if(fread(eth_header,sizeof(ETHeader_t),1,fop)!=1)
    	{
    		LOGE("Open eth_header error.\n");
    		break;
    	}
    	if(fread(ip_header,sizeof(IPHeader_t),1,fop)!=1)
        {
    		LOGE("Open ip_header error.\n");
        }
    	if(ip_header->ip_p==0x11)//0x11 is udp protocol,now the muliticast use udp over rtp.
    	{
    		if(udp_id==0)
    		udp_id = ip_header->ip_dst4;
//    		if( ip_header ->ip_dst4 != udp_id)
 //   		udp_id1 = ip_header->ip_dst4;
    		if(fread(udp_header,sizeof(UDPHeader_t),1,fop)!=1)
    		{
    			LOGE("Open udp_header error.\n");
            }
    		if(fread(rtp_header,sizeof(RTPHeader_t),1,fop)!=1)
    		{
    			LOGE("Open rtp_header error.\n");
    		}
    		if(rtp_header->one1==0x90)
    		{

    			int i;
    			for(i=0;i<7;i++)
    			{

    				fread(ts_data,188,1,fop);
    				ParseTS_PackageHead(ts_header,ts_data);
    				if(ts_header->sync_byte==0x47&&ts_header->transport_error_indicator==0x0)
    				{

    					if(ts_header->payload_unit_start_indicator==0x01)ts_start_indicator=1;
    					if(ts_start_indicator==1)
    					{
    						fwrite(ts_data,188,1,fwp);
    					}
    				}
    			}
    		}
//    		else if(ip_header->ip_dst4 == udp_id1)
//    		{
//    			int i;
//    			for(i=0;i<7;i++)
//    			{
//    			    	fread(ts_data,188,1,fop);
//    					ParseTS_PackageHead(ts_header,ts_data);
//        				if(ts_header->sync_byte==0x47&&ts_header->transport_error_indicator==0x0)
//   	    			{
//        					if(ts_header->payload_unit_start_indicator==0x01)ts_start_indicator=1;
// 		   					if(ts_start_indicator==1)
//    	  					{
//  	    						fwrite(ts_data,188,1,fwf);
//   	    				}
//        				}
//       		}
//    		}

    	}

    }

    free(pkt_header);
    free(eth_header);
    free(ip_header);
    free(udp_header);
    free(rtp_header);
    free(ts_header);
    free(ts_data);

    fclose(fop);
    fclose(fwp);
//    fclose(fwf);
}
