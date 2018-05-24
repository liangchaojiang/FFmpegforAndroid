#ifndef PARSETS_H_
#define PARSETS_H_

typedef struct
{

	unsigned  sync_byte :8; //define 0x47
	unsigned  transport_error_indicator :1;
	unsigned  payload_unit_start_indicator :1;
	unsigned  transport_priority :1;
	unsigned  PID :13;
	unsigned  transport_scrambling_control :2;
	unsigned  adaption_field_control :2;
	unsigned  continuity_counter :4;

}TS_PACKAGE_HEAD;

void ParseTS_PackageHead(TS_PACKAGE_HEAD *pstTS_PackageHead, unsigned char *pucPackageBuffer);


#endif
