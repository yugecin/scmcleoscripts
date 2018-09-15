#include <Windows.h>
#include <string>
#include <CLEO.h>

HANDLE hFile;
OpcodeResult WINAPI ext(CScriptThread *thread)
{
	if (hFile == NULL) {
		hFile = CreateFileA("camera.txt", FILE_GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, 0, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, 0);
		SetFilePointer(hFile, 0, NULL, FILE_END);
	}
	char buf[255];
	int i = CLEO_GetIntOpcodeParam(thread);
	float x = CLEO_GetFloatOpcodeParam(thread);
	float y = CLEO_GetFloatOpcodeParam(thread);
	float z = CLEO_GetFloatOpcodeParam(thread);
	float f[16];
	for (int i = 0; i < 16; i++) {
		f[i] = CLEO_GetFloatOpcodeParam(thread);
	}
	sprintf_s(buf, "%d %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f\n", i,
		x, y, z,
		f[0], f[1], f[2], f[3], f[4], f[5], f[6], f[7], f[8], f[9], f[10], f[11], f[12], f[13], f[14], f[15]);
	DWORD w;
	WriteFile(hFile, buf, strlen(buf), &w, NULL);

	return OR_CONTINUE;
}
OpcodeResult WINAPI ext2(CScriptThread *thread)
{
	if (hFile != NULL) {
		CloseHandle(hFile);
		hFile = NULL;
	}
	return OR_CONTINUE;
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{
	if (ul_reason_for_call == DLL_PROCESS_ATTACH) {
		return CLEO_RegisterOpcode(0x0DDF, &ext) && CLEO_RegisterOpcode(0x0DE0, &ext2);
	}
	return TRUE;
}