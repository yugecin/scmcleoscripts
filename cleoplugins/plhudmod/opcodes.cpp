#include "opcodes.h"
#include <math.h>

struct stSAMP *g_SAMP;

BOOL InitOpcodes()
{
	return
			CLEO_RegisterOpcode(0x0C36, &op0C36) &&
			CLEO_RegisterOpcode(0x0C37, &op0C37) &&
			setupTextdraws();
}

#define SNOOP 1

#if SNOOP
HANDLE hFile = NULL;

void savetd(stTextdraw *td)
{
	char buf[512];
	sprintf(buf, "string %s\n\
			letterwidth %x\n\
			letterheight %x\n\
			nlettercolor %x\n\
			center %d\n\
			box %d\n\
			boxsizex %x\n\
			boxsizey %x\n\
			boxcolor %x\n\
			proportional %x\n\
			shadowcolor %x\n\
			shadowsize %x\n\
			outline %x\n\
			left %x\n\
			right %x\n\
			font %x\n\
			x %x\n\
			y %x\n\
			\n\n",
			td->szString,
			*(unsigned int*)&td->fLetterWidth,
			*(unsigned int*)&td->fLetterHeight,
			*(unsigned int*)&td->dwLetterColor,
			*(unsigned char*)&td->byteCenter,
			*(unsigned char*)&td->byteBox,
			*(unsigned int*)&td->fBoxSizeX,
			*(unsigned int*)&td->fBoxSizeY,
			*(unsigned int*)&td->dwBoxColor,
			*(unsigned char*)&td->byteProportional,
			*(unsigned int*)&td->dwShadowColor,
			*(unsigned char*)&td->byteShadowSize,
			*(unsigned char*)&td->byteOutline,
			*(unsigned char*)&td->byteLeft,
			*(unsigned char*)&td->byteRight,
			*(unsigned int*)&td->iStyle,
			*(unsigned int*)&td->fX,
			*(unsigned int*)&td->fY);
	DWORD w;
	WriteFile(hFile, buf, strlen(buf), &w, NULL);
}
#endif

OpcodeResult WINAPI op0C36(CScriptThread *thread)
{
#if SNOOP
	if (g_SAMP == NULL) {
		g_SAMP = getSamp();
		if (g_SAMP == NULL) {
			return OR_CONTINUE;
		}
	}

	if (g_SAMP->pPools == NULL) {
		return OR_CONTINUE;
	}

	if (g_SAMP->pPools == NULL ||
			g_SAMP->pPools->pTextdraw == NULL) {
		return OR_CONTINUE;
	}

	if (hFile == NULL) {
		hFile = CreateFileA("tds.txt", FILE_GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, 0, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, 0);
		SetFilePointer(hFile, 0, NULL, FILE_END);
	}

	char buf[512];

	DWORD w;
	sprintf(buf, "\n\n==== global\n");
	WriteFile(hFile, buf, strlen(buf), &w, NULL);
	for (int i = 0; i < SAMP_MAX_TEXTDRAWS; i++) {
		if (g_SAMP->pPools->pTextdraw->iIsListed[i]) {
			savetd(g_SAMP->pPools->pTextdraw->textdraw[i]);
		}
	}

	sprintf(buf, "\n\n==== player\n");
	WriteFile(hFile, buf, strlen(buf), &w, NULL);
	for (int i = 0; i < SAMP_MAX_PLAYERTEXTDRAWS; i++) {
		if (g_SAMP->pPools->pTextdraw->iPlayerTextDraw[i]) {
			savetd(g_SAMP->pPools->pTextdraw->playerTextdraw[i]);
		}
	}

#endif
	return OR_CONTINUE;
}

//#define DOTRACE 1

#if DOTRACE
char gDbgStr[100];
DWORD gDbgW;
HANDLE hDbgFile = NULL;
#define TRACE1(x,y) sprintf(gDbgStr, x, y);WriteFile(hDbgFile, gDbgStr, strlen(gDbgStr), &gDbgW, NULL);
#define TRACE(x) TRACE1(x,0)
#else
#define TRACE(x)
#define TRACE1(x,y)
#endif

struct SPLHXTEXTDRAW pltextdraws[PLTDCOUNT];
SGAMEDATA gamedata;

#define INCAR (gamedata.carhp != -1)

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

BOOL setupTextdraws()
{
	setupTD(PLTD_FUEL, 0x44078000, 0x43C48000, 0, 0, NULL);
	setupTD(PLTD_DAMAGE, 0x44044000, 0x43CB0000, 0, 0, NULL);
	setupTD(PLTD_BOX0, 0x43A00000, 0x43D60000, 0, 0, &boxremovehandler);
	setupTD(PLTD_BOX1, 0x4403C000, 0x43C48000, 0, 0, &boxremovehandler);
	setupTD(PLTD_FUELPRICE, 0x44000000, 0x42C80000, 0, 0, NULL);
	setupTD(PLTD_SATISF, 0x44108000, 0x43B58000, 0, 0, NULL);
	setupTD(PLTD_FUELBAR, 0x440E4000, 0x43C78000, 0x440E4000, 0x43C78148, &progressbarpatchhandler);
	setupTD(PLTD_STATUSBAR, 0x43A00000, 0x43D60000, 0, 0, 0);
	setupTD(PLTD_DMGBAR, 0x440E4000, 0x43CE8000, 0x440E4000, 0x43CE8148, &progressbarpatchhandler);
	setupTD(PLTD_ODO, 0x43FA8000, 0x43C80000, 0, 0, NULL);
	setupTD(PLTD_AIRSPEED, 0x43E38000, 0x43C80000, 0x43E38000, 0x43C80148, &airspeedhandler);
	setupTD(PLTD_ALTITUDE, 0x43CC0000, 0x43C80000, 0x43CC0000, 0x43C80148, &altitudehandler);
	setupTD(PLTD_GPS, 0x43430000, 0x43C80000, 0, 0, NULL);
	setupTD(PLTD_DESTNEAREST, 0x439D0000, 0x43C80000, 0, 0, NULL);
	setupTD(PLTD_FUELPCT, 0x44124000, 0x43C60000, 0, 0, NULL);
	setupTD(PLTD_DAMAGEPCT, 0x44128000, 0x43CD0000, 0, 0, NULL);
	setupTD(PLTD_HEADING, 0x439e0000, 0x40000000, 0x439e0000, 0x40200000, &headinghandler);
	//setupTD(PLTD_HEADING, 0x439e0000, 0x40000000, 0x439e0000, 0x40200000, NULL);
	return TRUE;
}

void fuelpricehandler(struct SPLHXTEXTDRAW *hxtd, struct stTextdraw *samptd, int reason)
{
	TRACE("fuelpricehandler\n");
	if (reason == TDHANDLER_ATTACH) {
		samptd->fX = hxtd->fTargetX;
		samptd->fY = hxtd->fTargetY;
		return;
	}
}

void removehandler(struct SPLHXTEXTDRAW *hxtd, struct stTextdraw *samptd, int reason)
{
	TRACE("removehandler\n");
	if (reason == TDHANDLER_ATTACH) {
		samptd->fX = hxtd->fTargetX;
		samptd->fY = hxtd->fTargetY;
		return;
	}
}

void boxremovehandler(struct SPLHXTEXTDRAW *hxtd, struct stTextdraw *samptd, int reason)
{
	TRACE("boxremovehandler\n");
	if (reason == TDHANDLER_ATTACH) {
		samptd->dwBoxColor = 0;
		samptd->fX = hxtd->fTargetX;
		samptd->fY = hxtd->fTargetY;
		return;
	}
}

void gpshandler(struct SPLHXTEXTDRAW *hxtd, struct stTextdraw *samptd, int reason)
{
	TRACE("gpshandler\n");
	if (reason == TDHANDLER_ATTACH) {
		samptd->fX = hxtd->fTargetX;
		samptd->fY = hxtd->fTargetY;
		return;
	}
}

void airspeedhandler(struct SPLHXTEXTDRAW *hxtd, struct stTextdraw *samptd, int reason)
{
	TRACE("airspeedhandler\n");
	if (reason == TDHANDLER_ATTACH) {
		samptd->fX = hxtd->fTargetX;
		samptd->fY = hxtd->fTargetY;
		return;
	}
	if (!INCAR) {
		return;
	}
	char airspeedstring[10];
	sprintf(airspeedstring, "%d KTS", gamedata.carspeed);
	memcpy(&samptd->szText[14], airspeedstring, strlen(airspeedstring + 1));
	memcpy(&samptd->szString[14], airspeedstring, strlen(airspeedstring + 1));
}

void altitudehandler(struct SPLHXTEXTDRAW *hxtd, struct stTextdraw *samptd, int reason)
{
	TRACE("altitudehandler\n");
	if (reason == TDHANDLER_ATTACH) {
		samptd->fX = hxtd->fTargetX;
		samptd->fY = hxtd->fTargetY;
		return;
	}
	if (!INCAR) {
		return;
	}
	char altitudestring[10];
	sprintf(altitudestring, "%d FT", gamedata.altitude);
	memcpy(&samptd->szText[14], altitudestring, strlen(altitudestring + 1));
	memcpy(&samptd->szString[14], altitudestring, strlen(altitudestring + 1));
}

void headinghandler(struct SPLHXTEXTDRAW *hxtd, struct stTextdraw *samptd, int reason)
{
	TRACE("headinghandler\n");
	if (reason == TDHANDLER_ATTACH) {
		samptd->fX = hxtd->fTargetX;
		samptd->fY = hxtd->fTargetY;
		return;
	}
	if (!INCAR) {
		return;
	}
	char headingstring[3 + 1 + 3 + 1 + 3 + 1 + 5 + 1 + 3 + 1 + 3 + 1 + 3 + 1];
	int n[7];
	for (int i = 0; i < 7; i++) {
		n[i] = gamedata.carheading + 3 - i;
		if (n[i] < 1) n[i] += 360;
		if (n[i] > 360) n[i] -= 360;
	}
	sprintf(headingstring, "%03d %03d %03d [%03d] %03d %03d %03d", n[0], n[1], n[2], n[3], n[4], n[5], n[6]);
	memcpy(samptd->szText, headingstring, strlen(headingstring + 1));
	memcpy(samptd->szString, headingstring, strlen(headingstring + 1));
}

void progressbarpatchhandler(struct SPLHXTEXTDRAW *hxtd, struct stTextdraw *samptd, int reason)
{
	TRACE("progressbarpatchhandler\n");
	if (reason == TDHANDLER_ATTACH) {
		samptd->fX = hxtd->fTargetX;
		samptd->fY = hxtd->fTargetY;
		return;
	}
	samptd->szText[0] = '_';
	samptd->szString[0] = '_';
}

//int isTextdrawValid(int idx)
int isTextdrawValid(SPLHXTEXTDRAW *hxtd)
{
	if (hxtd->iHandle == INVALID_TEXTDRAW || !g_SAMP->pPools->pTextdraw->iIsListed[hxtd->iHandle]) {
		return 0;
	}
	if (g_SAMP->pPools->pTextdraw->textdraw[hxtd->iHandle]->fX == hxtd->fTargetX &&
			g_SAMP->pPools->pTextdraw->textdraw[hxtd->iHandle]->fY == hxtd->fTargetY) {
		return 1;
	}
	if (g_SAMP->pPools->pTextdraw->textdraw[hxtd->iHandle]->fX == hxtd->fX &&
			g_SAMP->pPools->pTextdraw->textdraw[hxtd->iHandle]->fY == hxtd->fY) {
		hxtd->handler(hxtd, g_SAMP->pPools->pTextdraw->textdraw[hxtd->iHandle], TDHANDLER_ATTACH);
		return 1;
	}
	return 0;
}

DWORD hookedcall = NULL;
DWORD *samp_21A0B4 = NULL;
DWORD samp_21A0B4_val;

void __cdecl stuff()
{
	DWORD samp_21A0B4_val = *samp_21A0B4;

#if DOTRACE
	if (hDbgFile == NULL) {
		hDbgFile = CreateFileA("tddbg.txt", FILE_GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, 0, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, 0);
		SetFilePointer(hDbgFile, 0, NULL, FILE_END);
	}
#endif

	gamedata.carspeed = (int) (145.0f * sqrt(gamedata.carspeedx * gamedata.carspeedx + gamedata.carspeedy * gamedata.carspeedy + gamedata.carspeedz * gamedata.carspeedz) / 7.5f);

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
			if (!g_SAMP->pPools->pTextdraw->iIsListed[j]) {
				continue;
			}
			if (g_SAMP->pPools->pTextdraw->textdraw[j]->fX == hxtd->fX &&
					g_SAMP->pPools->pTextdraw->textdraw[j]->fY == hxtd->fY) {
				TRACE1("assigned a handle to a textdraw %d\n", tdstoupdate[i]);
				hxtd->iHandle = j;
				hxtd->handler(hxtd, g_SAMP->pPools->pTextdraw->textdraw[hxtd->iHandle], TDHANDLER_ATTACH);
				break;
			}
		}
	}

	TRACE("invoking handles\n");
	for (int i = 0; i < PLTDCOUNT; i++) {
		SPLHXTEXTDRAW *hxtd = &pltextdraws[i];
		if (hxtd->iHandle != INVALID_TEXTDRAW && hxtd->handler != NULL) {
			TRACE1("textdraw with a handle %d\n", i);
			hxtd->handler(hxtd, g_SAMP->pPools->pTextdraw->textdraw[hxtd->iHandle], TDHANDLER_UPDATE);
		}
	}
}

void __declspec(naked) Changestuff()
{
	_asm {
		push ebx
		push ecx
		push edx
		push esi
		push edi
		push ebp
	}

	stuff();

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
	gamedata.carhp = CLEO_GetIntOpcodeParam(thread);
	gamedata.carheading = CLEO_GetIntOpcodeParam(thread);
	gamedata.carspeedx = CLEO_GetFloatOpcodeParam(thread);
	gamedata.carspeedy = CLEO_GetFloatOpcodeParam(thread);
	gamedata.carspeedz = CLEO_GetFloatOpcodeParam(thread);
	gamedata.altitude = CLEO_GetIntOpcodeParam(thread);

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

	/*
	if (g_SAMP->ulPort != 7777 || strcmp("142.44.161.46", g_SAMP->szIP) != 0) {
		goto exitzero;
	}
	*/

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
	CLEO_SetIntOpcodeParam(thread, ((DWORD) &Changestuff) - mem + 1 - 4 - 2);
	return OR_CONTINUE;
exitzero:
	CLEO_SetIntOpcodeParam(thread, 0);
	CLEO_SetIntOpcodeParam(thread, 0);
	return OR_CONTINUE;
}
