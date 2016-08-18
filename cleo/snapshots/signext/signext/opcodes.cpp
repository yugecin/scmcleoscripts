#include "opcodes.h"

BOOL InitOpcodes()
{
	if (CLEO_RegisterOpcode(0x0C26, &ext)) {
		return TRUE;
	}
	return FALSE;
}

OpcodeResult WINAPI ext(CScriptThread *thread)
{
	WORD i = CLEO_GetIntOpcodeParam(thread);
	float result;
	const float mp = 0.125;
	_asm
	{
		movsx ecx, i
		mov result, ecx
		fild result
		fmul mp
		fstp result
	}
	CLEO_SetFloatOpcodeParam(thread, result);
	return OR_CONTINUE;
}