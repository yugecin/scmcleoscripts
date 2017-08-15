
#include "opcodes.h"

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
