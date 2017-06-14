#include "CLEO.h"

OpcodeResult DrawText(CScriptThread *thread, bool hudcoordinates) {
	float xratio = (float)(*(DWORD*)(0xC17044)) / 640.0f;
	float yratio = (float)(*(DWORD*)(0xC17048)) / 480.0f;

	const char *text = (char*)CLEO_GetIntOpcodeParam(thread);
	float x = CLEO_GetFloatOpcodeParam(thread);
	float y = CLEO_GetFloatOpcodeParam(thread);
	int font = CLEO_GetIntOpcodeParam(thread);
	int align = CLEO_GetIntOpcodeParam(thread);
	int r = CLEO_GetIntOpcodeParam(thread);
	int g = CLEO_GetIntOpcodeParam(thread);
	int b = CLEO_GetIntOpcodeParam(thread);
	int a = CLEO_GetIntOpcodeParam(thread);
	float xsize = CLEO_GetFloatOpcodeParam(thread) * xratio;
	float ysize = CLEO_GetFloatOpcodeParam(thread) * yratio;

	if (hudcoordinates) {
		x *= xratio;
		y *= yratio;
	}

	((void (__cdecl *)(BYTE font))0x719490)(font);
	((void (__cdecl *)(BYTE align))0x719610)(align);
	((void (__cdecl *)(float xsize, float ysize))0x719380)(xsize, ysize);
	((void (__cdecl *)(DWORD rgba))0x719430)((r) | (g << 8) | (b << 16) | (a << 24));
	((void (__cdecl *)(float x, float y, const char* text))0x71A700)(x, y, text);

	return OR_CONTINUE;
}