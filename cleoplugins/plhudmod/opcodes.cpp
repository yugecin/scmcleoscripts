#include "opcodes.h"
#include "SRaceCheckpoint.h"
#include <math.h>

BOOL InitOpcodes()
{
	return
			CLEO_RegisterOpcode(0x0C36, &op0C36) &&
			CLEO_RegisterOpcode(0x0C37, &op0C37) &&
			setupTextdraws();
}

void trace(const char *f)
{
	static HANDLE hDbgFile = NULL;
	if (hDbgFile == NULL) {
		hDbgFile = CreateFileA("tddbg.txt", FILE_GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, 0, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, 0);
		SetFilePointer(hDbgFile, 0, NULL, FILE_END);
	}
	DWORD gDbgW;
	WriteFile(hDbgFile, f, strlen(f), &gDbgW, NULL);
}

struct SPLHXTEXTDRAW pltextdraws[PLTDCOUNT];
struct SGAMEDATA gamedata;
struct stTextdrawPool *tdpool;

int isTextdrawValid(SPLHXTEXTDRAW *hxtd)
{
	if (hxtd->iHandle == INVALID_TEXTDRAW || !tdpool->iIsListed[hxtd->iHandle]) {
		return 0;
	}
	if (tdpool->textdraw[hxtd->iHandle]->fX == hxtd->fTargetX &&
			tdpool->textdraw[hxtd->iHandle]->fY == hxtd->fTargetY) {
		return 1;
	}
	if (tdpool->textdraw[hxtd->iHandle]->fX == hxtd->fX &&
			tdpool->textdraw[hxtd->iHandle]->fY == hxtd->fY) {
		hxtd->handler(hxtd, tdpool->textdraw[hxtd->iHandle], TDHANDLER_ATTACH);
		return 1;
	}
	return 0;
}

void setupTD(int tdidx, unsigned int x, unsigned int y, unsigned int targetX, unsigned int targetY, TDHANDLER handler)
{
	pltextdraws[tdidx].iHandle = INVALID_TEXTDRAW;
	pltextdraws[tdidx].handler = handler;
	memcpy(&(pltextdraws[tdidx].fX), &x, 4);
	memcpy(&(pltextdraws[tdidx].fY), &y, 4);
	memcpy(&(pltextdraws[tdidx].fTargetX), &targetX, 4);
	memcpy(&(pltextdraws[tdidx].fTargetY), &targetY, 4);
	if (targetX == 0) {
		pltextdraws[tdidx].fTargetX = 2000.0f;
	}
	if (targetY == 0) {
		pltextdraws[tdidx].fTargetY = 2000.0f + 1.0f * (float) tdidx;
	}
}

DWORD hookedcall = NULL;
DWORD *samp_21A0B4 = NULL;
DWORD samp_21A0B4_val;

void __cdecl update_textdraws()
{
	DWORD samp_21A0B4_val = *samp_21A0B4;

	TRACE("updating toupdate\n");
	int tdstoupdate[PLTDCOUNT];
	int tdstoupdatecount = 0;
	for (int i = 0; i < PLTDCOUNT; i++) {
		if (pltextdraws[i].handler != NULL && !isTextdrawValid(&pltextdraws[i])) {
			tdstoupdate[tdstoupdatecount++] = i;
			pltextdraws[i].iHandle = INVALID_TEXTDRAW;
		}
	}

	TRACE("updating handles\n");
	for (int i = 0; i < tdstoupdatecount; i++) {
		SPLHXTEXTDRAW *hxtd = &pltextdraws[tdstoupdate[i]];
		for (int j = 0; j < SAMP_MAX_TEXTDRAWS; j++) {
			if (!tdpool->iIsListed[j]) {
				continue;
			}
			if (tdpool->textdraw[j]->fX == hxtd->fX &&
					tdpool->textdraw[j]->fY == hxtd->fY) {
				TRACE1("assigned a handle to a textdraw %d\n", tdstoupdate[i]);
				hxtd->iHandle = j;
				hxtd->handler(hxtd, tdpool->textdraw[hxtd->iHandle], TDHANDLER_ATTACH);
				break;
			}
		}
	}

	gamedata.carspeed = (int) (14.5f * sqrt(gamedata.carspeedx * gamedata.carspeedx + gamedata.carspeedy * gamedata.carspeedy + gamedata.carspeedz * gamedata.carspeedz) / 7.5f);
	if (gamedata.carhp == 999.0f) gamedata.carhp = 1000.0f; // adjust anticheat hp
	gamedata.carhp /= 1000.0f;
	int destinationtdhandle = pltextdraws[PLTD_DESTNEAREST].iHandle;
	struct SRaceCheckpoint *racecheckpoint = (SRaceCheckpoint*)(SA_RACECHECKPOINTS);
	if (destinationtdhandle != INVALID_TEXTDRAW && tdpool->textdraw[destinationtdhandle]->szString[0] == 'D') {
		for (int i = 0; i < MAX_RACECHECKPOINTS; i++) {
			if (racecheckpoint[i].byteUsed) {
				float dx = gamedata.carx - racecheckpoint[i].fX;
				float dy = gamedata.cary - racecheckpoint[i].fY;
				float dz = gamedata.carz - racecheckpoint[i].fZ;
				gamedata.missiondistance = (int) sqrt(dx * dx + dy * dy + dz * dz);
			}
		}
	}

	TRACE("invoking handles\n");
	for (int i = 0; i < PLTDCOUNT; i++) {
		SPLHXTEXTDRAW *hxtd = &pltextdraws[i];
		if (hxtd->iHandle != INVALID_TEXTDRAW && hxtd->handler != NULL) {
			TRACE1("textdraw with a handle %d\n", i);
			hxtd->handler(hxtd, tdpool->textdraw[hxtd->iHandle], TDHANDLER_UPDATE);
		}
	}
}

void __declspec(naked) hookstuff()
{
	_asm {
		push ebx
		push ecx
		push edx
		push esi
		push edi
		push ebp
	}

	update_textdraws();

	_asm {
		xor eax, eax
		pop ebp
		pop edi
		pop esi
		pop edx
		pop ecx
		pop ebx
		mov eax, samp_21A0B4_val
		ret
	}
}

OpcodeResult WINAPI op0C37(CScriptThread *thread)
{
	static struct stSAMP *g_SAMP = NULL;

	gamedata.carhp = CLEO_GetFloatOpcodeParam(thread);
	gamedata.carheading = CLEO_GetIntOpcodeParam(thread);
	gamedata.carspeedx = CLEO_GetFloatOpcodeParam(thread);
	gamedata.carspeedy = CLEO_GetFloatOpcodeParam(thread);
	gamedata.carspeedz = CLEO_GetFloatOpcodeParam(thread);
	gamedata.carx = CLEO_GetFloatOpcodeParam(thread);
	gamedata.cary = CLEO_GetFloatOpcodeParam(thread);
	gamedata.carz = CLEO_GetFloatOpcodeParam(thread);

	if (g_SAMP == NULL) {
		g_SAMP = getSamp();
		if (g_SAMP == NULL) {
			goto exitzero;
		}
	}

	if (g_SAMP->pPools == NULL ||
			g_SAMP->pPools->pTextdraw == NULL) {
		goto exitzero;
	}

	if (g_SAMP->ulPort != 7777 || strcmp("142.44.161.46", g_SAMP->szIP) != 0) {
		goto exitzero;
	}

	tdpool = g_SAMP->pPools->pTextdraw;

	if (hookedcall) {
		goto exitzero;
	}

	HMODULE samp_dll = GetModuleHandle("samp.dll");
	DWORD mem = (DWORD)samp_dll + 0x1AD40;
	DWORD *sub = (DWORD*)(mem);
	hookedcall = *sub;
	hookedcall += mem + 5;
	samp_21A0B4 = (DWORD*)((DWORD)samp_dll + 0x21A0B4);

	CLEO_SetIntOpcodeParam(thread, mem);
	CLEO_SetIntOpcodeParam(thread, ((DWORD) &hookstuff) - mem + 1 - 4 - 2);
	return OR_CONTINUE;
exitzero:
	CLEO_SetIntOpcodeParam(thread, 0);
	CLEO_SetIntOpcodeParam(thread, 0);
	return OR_CONTINUE;
}
