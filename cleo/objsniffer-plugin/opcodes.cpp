#include "opcodes.h"

HANDLE hFile = NULL;

BOOL InitOpcodes()
{
	if (CLEO_RegisterOpcode(0x0DDD, &ext)) {
		return TRUE;
	}
	return FALSE;
}

OpcodeResult WINAPI ext(CScriptThread *thread)
{
	if (hFile == NULL) {
		hFile = CreateFileA("objz.txt", FILE_GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, 0, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, 0);
		SetFilePointer(hFile, 0, NULL, FILE_END);
	}
	unsigned char buf[28];
	DWORD d;
	d = CLEO_GetIntOpcodeParam(thread);
	memcpy(&buf[0], &d, 4);
	float f;
	for (int i = 0; i < 6; i++) {
		f = CLEO_GetFloatOpcodeParam(thread);
		memcpy(&buf[4 + i * 4], &f, 4);
	}
	DWORD w;
	WriteFile(hFile, buf, 28, &w, NULL);

	return OR_CONTINUE;
}