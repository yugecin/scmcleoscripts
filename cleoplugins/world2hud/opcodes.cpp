#include "opcodes.h"
#include "rw.h"

BOOL InitOpcodes()
{
	return
		CLEO_RegisterOpcode(0x0C27, &Op_0C27) &&
		CLEO_RegisterOpcode(0x0C28, &Op_0C28);
}

RwV3D TransformWorldXYZ(RwV3D world) {
	// partly based on https://github.com/multitheftauto/mtasa-blue/blob/9b1fbaf639657a446790469aa6711e11be0d3eee/MTA10/core/CGraphics.cpp#L498

	CMATRIX *cameraViewMatrix = (CMATRIX*)(0xB6FA2C);

	RwV3D screen;
	screen.x = world.z * cameraViewMatrix->three.x + world.y * cameraViewMatrix->two.x + world.x * cameraViewMatrix->one.x + cameraViewMatrix->four.x;
	screen.y = world.z * cameraViewMatrix->three.y + world.y * cameraViewMatrix->two.y + world.x * cameraViewMatrix->one.y + cameraViewMatrix->four.y;
	screen.z = world.z * cameraViewMatrix->three.z + world.y * cameraViewMatrix->two.z + world.x * cameraViewMatrix->one.z + cameraViewMatrix->four.z;

	float fRecip = 1.0f / screen.z;
	screen.x *= fRecip;
	screen.y *= fRecip;

	return screen;
}

OpcodeResult TransformPointFor0C270C28(CScriptThread *thread, int width, int height) {
	RwV3D world;
	world.x = CLEO_GetFloatOpcodeParam(thread);
	world.y = CLEO_GetFloatOpcodeParam(thread);
	world.z = CLEO_GetFloatOpcodeParam(thread);

	RwV3D screen = TransformWorldXYZ(world);

	CLEO_SetFloatOpcodeParam(thread, screen.x * width);
	CLEO_SetFloatOpcodeParam(thread, screen.y * height);
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
