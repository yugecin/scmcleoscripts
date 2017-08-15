
#include "stuff.h"
#include "windows.h"

struct SRaceCheckpoint
{
	BYTE		byteType;
	BYTE 		byteFree;
	BYTE 		byteUsed;
	BYTE 		byteField_3;
	BYTE 		byteField_4;
	BYTE 		byteField_5;
	BYTE 		byteField_6;
	BYTE 		byteField_7;
	BYTE 		byteR;
	BYTE 		byteG;
	BYTE 		byteB;
	BYTE 		byteField_B;
	BYTE 		byteField_C;
	BYTE 		byteField_D;
	BYTE 		byteField_E;
	BYTE		byteField_F;
	float		fX;
	float		fY;
	float		fZ;
	float		fArrowOffsetX;
	float		fArrowOffsetY;
	float		fArrowOffsetZ;
	DWORD		dwField_28;
	float		fRadius;
	DWORD		dwField_30;
	BYTE		dwField_34;
	BYTE		dwField_35;
	BYTE		dwField_36;
	BYTE		dwField_37;
};
VALIDATE_SIZE(SRaceCheckpoint, 0x38);

#define MAX_RACECHECKPOINTS	(0x20)
#define SA_RACECHECKPOINTS	(0xC7F158)
