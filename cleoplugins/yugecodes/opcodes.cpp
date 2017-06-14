#include "opcodes.h"
#include "transform.h"

BOOL InitOpcodes()
{
	return
		CLEO_RegisterOpcode(0x0c26, &Op_0C26) &&
		CLEO_RegisterOpcode(0x0C27, &Op_0C27) &&
		CLEO_RegisterOpcode(0x0C28, &Op_0C28) &&
		CLEO_RegisterOpcode(0x0C29, &Op_0C29) &&
		CLEO_RegisterOpcode(0x0C30, &Op_0C30);
}

// 0C26: sign_extend 1@ store_to 2@
// {$O 0C26=2,sign_extend %1d% store_to %2d%}
OpcodeResult WINAPI Op_0C26(CScriptThread *thread)
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

// 0C27: transform world_xyz 1@ 2@ 3@ to hud_xy 4@ 5@
// {$O 0C27=5,transform world_xyz %1d% %2d% %3d% to hud_xy %4d% %5d%}
OpcodeResult WINAPI Op_0C27(CScriptThread *thread)
{
	return TransformPointFor0C270C28(thread, 640, 480);
}

// 0C28: transform world_xyz 1@ 2@ 3@ to screen_xy 4@ 5@
// {$O 0C28=5,transform world_xyz %1d% %2d% %3d% to screen_xy %4d% %5d%}
OpcodeResult WINAPI Op_0C28(CScriptThread *thread)
{
	DWORD *displayWidth = (DWORD*)(0xC17044);
	DWORD *displayHeight = (DWORD*)(0xC17048);
	return TransformPointFor0C270C28(thread, (*displayWidth), (*displayHeight));
}

// 0C29: lerp_ab 1@ to 2@ f 3@ store_to 4@
// {$O 0C29=4,lerp_ab %1d% f %2d% at %3d% store_to %4d%}
OpcodeResult WINAPI Op_0C29(CScriptThread *thread)
{
	float a;
	float b;
	float f;

	a = CLEO_GetFloatOpcodeParam(thread);
	b = CLEO_GetFloatOpcodeParam(thread);
	f = CLEO_GetFloatOpcodeParam(thread);

	// https://stackoverflow.com/questions/4353525/floating-point-linear-interpolation
	a = a + f * (b - a);

	CLEO_SetFloatOpcodeParam(thread, a);
	return OR_CONTINUE;
}

// 0C30: draw_text 1@ at 2@ 3@
// {$O 0C30=3,draw_text %1d% at %2d% %3d%}
OpcodeResult WINAPI Op_0C30(CScriptThread *thread)
{
	const char *text = (char*)CLEO_GetIntOpcodeParam(thread);
	float x = CLEO_GetFloatOpcodeParam(thread);
	float y = CLEO_GetFloatOpcodeParam(thread);

	((void (__cdecl *)(float x, float y, const char* text))0x71A700)(x, y, text);

	return OR_CONTINUE;
} 
