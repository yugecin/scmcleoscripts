
#include "samp.h"

#define SAMP_INFO_OFFSET 0x21A0F8

struct stSAMP *getSamp(void)
{
	static HMODULE samp_dll = GetModuleHandle("samp.dll");

	if (samp_dll == NULL) {
		return NULL;
	}

	DWORD& adr = *(DWORD*)(((DWORD)samp_dll + SAMP_INFO_OFFSET));

	return (stSAMP*)(adr);
}
