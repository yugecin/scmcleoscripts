#include "opcodes.h"

struct stSAMP *g_SAMP;

BOOL InitOpcodes()
{
	return
		CLEO_RegisterOpcode(0x0C36, &op0C36) &&
		CLEO_RegisterOpcode(0x0C37, &op0C37) &&
		TRUE;
}

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
			td->fLetterWidth,
			td->fLetterHeight,
			td->dwLetterColor,
			td->byteCenter,
			td->byteBox,
			td->fBoxSizeX,
			td->fBoxSizeY,
			td->dwBoxColor,
			td->byteProportional,
			td->dwShadowColor,
			td->byteShadowSize,
			td->byteOutline,
			td->byteLeft,
			td->byteRight,
			td->iStyle,
			td->fX,
			td->fY);
	DWORD w;
	WriteFile(hFile, buf, strlen(buf), &w, NULL);
}

OpcodeResult WINAPI op0C36(CScriptThread *thread)
{
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

	return OR_CONTINUE;
}

OpcodeResult WINAPI op0C36(CScriptThread *thread)
{

	return OR_CONTINUE;
}