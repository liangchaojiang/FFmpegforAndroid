#ifndef PARSEPCAP_H_
#define PARSEPCAP_H_

#include<stdint.h>


typedef uint32_t u_int;
typedef uint16_t u_short;
typedef unsigned char u_char;

unsigned char H264_STREAM_ID;

#define ETHER_ADDR_LEN 6

//Global Header 24 bytes
typedef struct pcap_file_header {
	u_int  magic;
	u_short version_major;
	u_short version_minor;
	int32_t thiszone;	/* gmt to local correction */
	u_int sigfigs;	/* accuracy of timestamps */
	u_int snaplen;	/* max length saved portion of each pkt */
	u_int linktype;	/* data link type (LINKTYPE_*) */
}PCAPHeader_t;
//Packet Header 16 bytes
typedef struct pcap_pkthdr {
	u_int ts_sec;         /* timestamp seconds */
    u_int ts_usec;        /* timestamp microseconds */
    u_int incl_len;       /* number of octets of packet saved in file */
    u_int orig_len;       /* actual length of packet */
}PKTHeader_t;
//ethernet  14 bytes
typedef struct ether_header
{
    u_char ether_dhost[ETHER_ADDR_LEN];
    u_char ether_shost[ETHER_ADDR_LEN];
    u_short ether_type;
}ETHeader_t;
//IP header 20 bytes
typedef struct ip
{
    u_char Ver_HLen;
    u_char ip_tos;
    u_short ip_len;
    u_short ip_id;
    u_short ip_off;
    u_char ip_ttl;
    u_char ip_p;
    u_short ip_sum;
    u_int ip_src;
    u_char ip_dst1;
    u_char ip_dst2;
    u_char ip_dst3;
    u_char ip_dst4;
}IPHeader_t;
//udp header 8 bytes
typedef struct udphdr
{
    u_short uh_sport;
    u_short uh_dport;
    u_short uh_ulen;
    u_short uh_sum;
}UDPHeader_t;
//rtp header 32 bytes note:should follw the rfc,it's only a fake data to padding
typedef struct rtphdr
{
    u_char one1;
    u_char one2;
    u_char one3;
    u_char one4;
    u_int two;
    u_int three;
    u_int four;
    u_int five;
    u_int six;
    u_int seven;
    u_int eight;
}RTPHeader_t;


int Pcap_To_Ts(char * Inputfile,char * Outputfile);


#endif // PARSEPCAP_H_
