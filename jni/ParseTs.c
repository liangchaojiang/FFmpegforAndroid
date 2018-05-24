#include <stdio.h>
#include <stdlib.h>
#include "ParseTs.h"
#define PACKAGE_MAX_LENGTH 204


/*********************************************************************************************************************************
 * Function Name : ParseTS_PackageHead
 * Description   : parse the TS package head
 * Parameters    :
 *pstTS_PackageHead -- the package head structure
 *pucBufferPackage -- the package buffer
 * Returns       : void
 *********************************************************************************************************************************/
void ParseTS_PackageHead(TS_PACKAGE_HEAD *pstTS_PackageHead, unsigned char *pucPackageBuffer)
{

	pstTS_PackageHead->sync_byte = pucPackageBuffer[0];
	pstTS_PackageHead->transport_error_indicator = pucPackageBuffer[1] >> 7;
	pstTS_PackageHead->payload_unit_start_indicator = (pucPackageBuffer[1] >> 6) & 0x01;
	pstTS_PackageHead->transport_priority = (pucPackageBuffer[1] >> 5) & 0x01;
	pstTS_PackageHead->PID = ((pucPackageBuffer[1] & 0x1F) << 8) | pucPackageBuffer[2];
	pstTS_PackageHead->transport_scrambling_control = pucPackageBuffer[3] >> 6;
	pstTS_PackageHead->adaption_field_control = (pucPackageBuffer[3] >> 4) & 0x03;
	pstTS_PackageHead->continuity_counter = pucPackageBuffer[3] & 0x0f;

}
