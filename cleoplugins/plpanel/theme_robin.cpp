
#include "opcodes.h"
#include "commonhandlers.h"
#include "util.h"
#include "theme_robin.h"

#if THEME == THEME_ROBIN

int fuelval;
int fuelprice;
int satisfval;
int satisflastseen;
int odoval;
char destnearstr[120];

// ==== dmgboxstuff v

void damagepcthandler(struct SPLHXTEXTDRAW *hxtd, struct stTextdraw *samptd, int reason)
{
	TRACE("damagepcthandler\n");
	REPOSITION_ON_ATTACH();
	samptd->fLetterWidth = 0.0f;
}

void damagepatchhandlerex(struct SPLHXTEXTDRAW *hxtd, struct stTextdraw *samptd, int reason)
{
	TRACE("damagepatchhandlerex\n");
	REPOSITION_ON_ATTACH();
	if (ISPLANE) {
		samptd->fLetterWidth = 0.0f;
		return;
	}
	samptd->fLetterWidth = 0.259999f;
	damagepatchhandler(hxtd, samptd, reason);
}

void fuelpcthandler(struct SPLHXTEXTDRAW *hxtd, struct stTextdraw *samptd, int reason)
{
	TRACE("fuelpcthandler\n");
	REPOSITION_ON_ATTACH();
	if (INCAR) {
		char c = samptd->szText[0];
		if ('0' <= c && c <= '9') {
			fuelval = simplestrval(samptd->szText, 0);
		}
		samptd->fLetterWidth = 0.3f;
		samptd->fLetterHeight = 1.0f;
		samptd->dwLetterColor = -1;
		samptd->byteCenter = 0;
		samptd->byteLeft = 1;
		samptd->byteRight = 0;
		samptd->byteOutline = 1;
		samptd->fX = 155.0f;
		samptd->fY = 400.0f;
		hxtd->fTargetX = samptd->fX;
		hxtd->fTargetY = samptd->fY;
		memcpy(samptd->szString, destnearstr, 120);
		memcpy(samptd->szText, destnearstr, 120);
		return;
	}
	samptd->fLetterWidth = 0.0f;
}

// ==== dmgboxstuff ^

void gpshandler(struct SPLHXTEXTDRAW *hxtd, struct stTextdraw *samptd, int reason)
{
	TRACE("gpshandler\n");
	REPOSITION_ON_ATTACH();
	samptd->fX = 85.0f;
	samptd->fY = 320.0f;
	samptd->fLetterWidth = 0.3f;
	samptd->fLetterHeight = 1.0f;
	samptd->byteBox = 0;
	samptd->byteOutline = 1;
	samptd->fBoxSizeY = 0x44200000;
	if (strncmp(samptd->szText, "GPS~n~", 6) == 0) {
		sprintf(samptd->szString, "%s", &(samptd->szText[9]));
		memcpy(samptd->szText, samptd->szString, 100);
	}
}

void destnearesthandlerex(struct SPLHXTEXTDRAW *hxtd, struct stTextdraw *samptd, int reason)
{
	TRACE("destnearesthandlerex\n");
	destnearesthandler(hxtd, samptd, reason, destnearstr);
}

void odohandler(struct SPLHXTEXTDRAW *hxtd, struct stTextdraw *samptd, int reason)
{
	TRACE("odohandler\n");
	REPOSITION_ON_ATTACH();
	odoval = simplestrval(&(samptd->szText[9]), 0);
	int idx = 10;
	char c;
	do {
		c = samptd->szText[idx];
		if (c == 'K') {
			return;
		}
		if (c == 'M') {
			odoval = 0;
			return;
		}
		idx++;
	} while (c != 0);
}

void carodohandler(struct SPLHXTEXTDRAW *hxtd, struct stTextdraw *samptd, int reason)
{
	TRACE("carodohandler\n");
	REPOSITION_ON_ATTACH();
	odoval = simplestrval(&(samptd->szText[16]), 0);
	int idx = 10;
	char c;
	do {
		c = samptd->szText[idx];
		if (c == 'K') {
			return;
		}
		if (c == 'M') {
			odoval = 0;
			return;
		}
		idx++;
	} while (c != 0);
}

void fuelpricehandler(struct SPLHXTEXTDRAW *hxtd, struct stTextdraw *samptd, int reason)
{
	TRACE("fuelpricehandler\n");
	REPOSITION_ON_ATTACH();
	if (samptd->szText[11] == '$') {
		fuelprice = simplestrval(samptd->szText, 12);
	}
	if (INCAR) {
		samptd->fLetterWidth = 0.0f;
		samptd->fLetterHeight = 0.0f;
		return;
	}
	samptd->fLetterWidth = 0.25f;
	samptd->fLetterHeight = 1.75f;
}

void satisfhandler(struct SPLHXTEXTDRAW *hxtd, struct stTextdraw *samptd, int reason)
{
	satisflastseen = 0;
	TRACE("satisfhandler\n");
	REPOSITION_ON_ATTACH();
	if (samptd->szText[22] == ':') {
		satisfval = simplestrval(samptd->szText, 24);
	}
}

void statusbarhandler(struct SPLHXTEXTDRAW *hxtd, struct stTextdraw *samptd, int reason)
{
	TRACE("statusbarhandler\n");
	REPOSITION_ON_ATTACH();
	// statusbar & statusbarbox have the same position
	if (samptd->byteBox) {
		samptd->dwBoxColor = 0x6AA00200;
		samptd->fLetterHeight = 1.0f;
	} else {
		samptd->iStyle = 2;
		samptd->fLetterWidth = 0.25f;
		samptd->fLetterHeight = 1.0f;
		samptd->byteShadowSize = 1;
	}
}

void hijackhandler1(struct SPLHXTEXTDRAW *hxtd, struct stTextdraw *samptd, int reason)
{
	TRACE("hijackhandler1\n");
	REPOSITION_ON_ATTACH();
	if (!INCAR) {
		samptd->byteBox = 0;
		samptd->dwShadowColor = 0;
		samptd->fLetterWidth = 0.0f;
		samptd->fLetterHeight = 0.0f;
		return;
	}
	samptd->fLetterWidth = 0.26f;
	samptd->fLetterHeight = 1.0f;
	samptd->dwLetterColor = 0xffffffff;
	samptd->byteCenter = 0;
	samptd->byteBox = 0;
	samptd->fBoxSizeX = 1280.0f;
	samptd->fBoxSizeY = 1280.0f;
	samptd->byteProportional = 1;
	samptd->dwShadowColor = 0xff000000;
	samptd->byteShadowSize = 1;
	samptd->byteOutline = 0;
	samptd->byteLeft = 0;
	samptd->byteRight = 1;
	samptd->iStyle = 1;
	char satisfstr[20];
	satisfstr[0] = 0;
	if (satisfval != -1) {
		sprintf(satisfstr, "Satisfaction");
	}
	sprintf(samptd->szText, "%s~n~Airspeed~n~Altitude~n~ODO~n~Fuel ($%d/l)~n~Health", satisfstr, fuelprice);
	memcpy(samptd->szString, samptd->szText, 200);
	fuelprice = -1;
}

void hijackhandler2(struct SPLHXTEXTDRAW *hxtd, struct stTextdraw *samptd, int reason)
{
	TRACE("hijackhandler2\n");
	REPOSITION_ON_ATTACH();
	if (!INCAR) {
		samptd->byteBox = 0;
		samptd->dwShadowColor = 0;
		samptd->fLetterWidth = 0.0f;
		samptd->fLetterHeight = 0.0f;
		return;
	}
	samptd->fLetterWidth = 0.26f;
	samptd->fLetterHeight = 1.0f;
	samptd->dwLetterColor = 0xffffffff;
	samptd->byteCenter = 0;
	samptd->byteBox = 0;
	samptd->fBoxSizeX = 1280.0f;
	samptd->fBoxSizeY = 1280.0f;
	samptd->byteProportional = 1;
	samptd->dwShadowColor = 0xff000000;
	samptd->byteShadowSize = 1;
	samptd->byteOutline = 0;
	samptd->byteLeft = 1;
	samptd->byteRight = 0;
	samptd->iStyle = 1;
	char satisfstr[20];
	satisfstr[0] = 0;
	if (satisfval != -1) {
		sprintf(satisfstr, "%d%%", satisfval);
	}
	sprintf(samptd->szText, "%s~n~%d KTS~n~%d FT~n~%d KM~n~%d%%~n~%d%%", satisfstr, AIRSPEED(gamedata.carspeed), (int) gamedata.carz, odoval,
			fuelval, gamedata.carhp / 10);
	memcpy(samptd->szString, samptd->szText, 230);
	satisflastseen++;
	if (satisflastseen >= 2) {
		satisfval = -1;
	}
}

BOOL setupTextdraws()
{
	satisfval = -1;
	destnearstr[0] = 0;
	setupTD(PLTD_FUEL, 0x44044000, 0x43C60000, 0, 0, &removehandler);
	setupTD(PLTD_DAMAGE, 0x44044000, 0x43CB0000, 0, 0, &removehandler);
	setupTD(PLTD_STATUSBARBOX, 0x43A00000, 0x43D60000, 0x43A00000, 0x43D70000, &statusbarhandler);
	setupTD(PLTD_FUELDMGBOX, 0x4403C000, 0x43C48000, 0, 0, &removehandler);
	setupTD(PLTD_FUELPRICE, 0x44000000, 0x42C80000, 0x44000148, 0x42C80148, &fuelpricehandler);
	setupTD(PLTD_SATISF, 0x44108000, 0x43B58000, 0, 0, &satisfhandler);
	setupTD(PLTD_FUELBAR, 0x440E4000, 0x43C78000, 0x44070000, 0x43B18000, &hijackhandler1);
	setupTD(PLTD_STATUSBAR, 0x43A00000, 0x43D60000, 0x43A00000, 0x43D70000, &statusbarhandler);
	setupTD(PLTD_DMGBAR, 0x440E4000, 0x43CE8000, 0x44160000, 0x43B18000, &hijackhandler2);
	setupTD(PLTD_ODO, 0x43FA8000, 0x43C80000, 0, 0, &odohandler);
	setupTD(PLTD_AIRSPEED, 0x43E38000, 0x43C80000, 0, 0, &removehandler);
	setupTD(PLTD_ALTITUDE, 0x43CC0000, 0x43C80000, 0, 0, &removehandler);
	setupTD(PLTD_GPS, 0x43430000, 0x43C80000, 0x42AA0000, 0x43A00000, &gpshandler);
	setupTD(PLTD_DESTNEAREST, 0x439D0000, 0x43C80000, 0, 0, &destnearesthandlerex);
	//setupTD(PLTD_DESTNEAREST, 0x439D0000, 0x43C80000, 0x439D0000, 0x43C80148, NULL);
	setupTD(PLTD_FUELPCT, 0x44124000, 0x43C60000, 0x44124000, 0x43C60148, &fuelpcthandler);
	setupTD(PLTD_DAMAGEPCT, 0x44128000, 0x43CD0000, 0x44128000, 0x43CD0148, &damagepcthandler);
	setupTD(PLTD_HEADING, 0x439e0000, 0x40000000, 0x439e0000, 0x40200000, &headinghandler);
	setupTD(PLTD_CARSPEED, 0x44108000, 0x43B58000, 0, 0, &removehandler);
	setupTD(PLTD_CARODO, 0x4410c000, 0x43BB0000, 0, 0, &carodohandler);
	return TRUE;
}

void __cdecl drawbars()
{
	if (!INCAR) {
		return;
	}
	float WIDTHMP = (float)(*(DWORD*)(0xC17044)) / 640.0f;
	float HEIGHTMP = (float)(*(DWORD*)(0xC17048)) / 480.0f;

	float BARPOSITIONX = 547.0f * WIDTHMP;
	int BARWIDTH = (int) (50.0f * WIDTHMP);
	unsigned char BARHEIGHT = (unsigned char) (9.2f * HEIGHTMP);
	float DBARPOSITIONY = (9.0f * HEIGHTMP);

	float barpositiony = (383.0f * HEIGHTMP);

	float pct;

	// satisfaction
	if (satisfval != -1) {
		pct = (float)satisfval;
		DrawBarChart(BARPOSITIONX, barpositiony, BARWIDTH, BARHEIGHT, pct, 0, 0, 1, 0xFF00FFFF, 0);
	}
	barpositiony += DBARPOSITIONY;
	// speed
	pct = AIRSPEEDF(gamedata.carspeed) * 100.0f / 145.0f;
	DrawBarChart(BARPOSITIONX, barpositiony, BARWIDTH, BARHEIGHT, pct, 0, 0, 1, 0xFFFF00FF, 0);
	barpositiony += DBARPOSITIONY;
	// altitude
	pct = (float) gamedata.carz / 10.0f;
	DrawBarChart(BARPOSITIONX, barpositiony, BARWIDTH, BARHEIGHT, pct, 0, 0, 1, 0xFFFF00FF, 0);
	barpositiony += DBARPOSITIONY;
	// odo
	if (odoval < 480 || gamedata.blinkstatus) {
		pct = (float)odoval / 5.0f;
		DrawBarChart(BARPOSITIONX, barpositiony, BARWIDTH, BARHEIGHT, pct, 0, 0, 1, 0xFFFFFF00, 0);
	}
	barpositiony += DBARPOSITIONY;
	// fuel
	if (fuelval > 20 || gamedata.blinkstatus) {
		pct = (float)fuelval;
		DrawBarChart(BARPOSITIONX, barpositiony, BARWIDTH, BARHEIGHT, pct, 0, 0, 1, 0xFF00FF00, 0);
	}
	barpositiony += DBARPOSITIONY;
	// health
	if (gamedata.carhp > 350 || gamedata.blinkstatus) {
		pct = (float)gamedata.carhp / 10.0f;
		DrawBarChart(BARPOSITIONX, barpositiony, BARWIDTH, BARHEIGHT, pct, 0, 0, 1, 0xFFFF0000, 0);
	}
}

void __declspec(naked) robindrawhookstuff()
{
	_asm {
		push ebx
		push ecx
		push edx
		push esi
		push edi
		push ebp
	}

	drawbars();

	_asm {
		pop ebp
		pop edi
		pop esi
		pop edx
		pop ecx
		pop ebx
		mov eax, ds:0xB7CF28
		ret
	}
}

#endif
