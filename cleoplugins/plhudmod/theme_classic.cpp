
#include "opcodes.h"
#include "commonhandlers.h"
#include "util.h"

#if THEME == THEME_CLASSIC

char fuel[5];
char odo[15];
char destnearstr[120];
char satisfstr[22];
char odocolor[2];

void fuelpcthandler(struct SPLHXTEXTDRAW *hxtd, struct stTextdraw *samptd, int reason)
{
	TRACE("fuelpcthandler\n");
	REPOSITION_ON_ATTACH();
	if (ISPLANE) {
		sprintf(fuel, "%s", samptd->szString);
		samptd->fLetterWidth = 0.0f;
		return;
	}
	samptd->fLetterWidth = 0.27f;
}

void odohandler(struct SPLHXTEXTDRAW *hxtd, struct stTextdraw *samptd, int reason)
{
	TRACE("odohandler\n");
	REPOSITION_ON_ATTACH();
	sprintf(odo, "%s", &(samptd->szString[9]));
	if (simplestrval(odo, 0) > 480) {
		odocolor[0] = 'r';
	} else {
		odocolor[0] = 'w';
	}
}

void satisfhandler(struct SPLHXTEXTDRAW *hxtd, struct stTextdraw *samptd, int reason)
{
	TRACE("satisfhandler\n");
	REPOSITION_ON_ATTACH();
	sprintf(satisfstr, "~b~Satisf: ~w~%s", &(samptd->szString[24]));
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
	TRACE1("gpshandler %s\n", samptd->szString);
	if (samptd->szString[0] == 'G' || samptd->szText[0] == 'G') {
		char gpsstring[100];
		sprintf(gpsstring, "%s", &(samptd->szText[9]));
		memcpy(samptd->szText, gpsstring, 100);
		memcpy(samptd->szString, gpsstring, 100);
	}
}

void destnearesthandler(struct SPLHXTEXTDRAW *hxtd, struct stTextdraw *samptd, int reason)
{
	destnearstr[0] = 0;
	TRACE("destnearesthandler\n");
	REPOSITION_ON_ATTACH();
	if (!INCAR) {
		return;
	}
	if (gamedata.missiondistance != -1) {
		sprintf(destnearstr, "~b~Distance~b~ ~w~%d", gamedata.missiondistance);
		return;
	}
	if (samptd->szString[0] != 'N') {
		return;
	}
	int idx = 18;
	int chars = 0;
	while (true) {
		if (samptd->szString[idx] == 'M') {
			chars = sprintf(destnearstr, "~b~%s ", &(samptd->szText[idx + 8]));
			break;
		}
		idx++;
		if (idx > 23) {
			return;
		}
	}
	if (chars == -1) {
		destnearstr[0] = 0;
		return;
	}
	int srcidx = 16;
	if (samptd->szText[srcidx] != '(') {
		return;
	}
	while (true) {
		char c = samptd->szText[srcidx++];
		destnearstr[chars++] = c;
		if (c == ')' || srcidx > 25) {
			break;
		}
	}
	destnearstr[chars] = 0;
}

void hijackhandler(struct SPLHXTEXTDRAW *hxtd, struct stTextdraw *samptd, int reason)
{
	TRACE("hijackhandler\n");
	REPOSITION_ON_ATTACH();
	if (!INCAR) {
		samptd->byteBox = 0;
		samptd->dwLetterColor = 0;
		samptd->dwShadowColor = 0;
		return;
	}
	samptd->fLetterWidth = 0.4f;
	samptd->fLetterHeight = 1.2f;
	samptd->dwLetterColor = 0xffffffff;
	samptd->byteCenter = 0;
	samptd->byteBox = 1;
	samptd->fBoxSizeX = 450.0f;
	samptd->fBoxSizeY = 0.0f;
	samptd->dwBoxColor = 0x6f370000;
	samptd->byteProportional = 1;
	samptd->dwShadowColor = 0xff000000;
	samptd->byteShadowSize = 1;
	samptd->byteOutline = 0;
	samptd->byteLeft = 0;
	samptd->byteRight = 0;
	samptd->iStyle = 1;
	char mainstring[700];
	float hp = (float)gamedata.carhp / 10.0f;
	int fuelvalue = simplestrval(fuel, 0);
	sprintf(mainstring, "~b~Airspeed: ~w~%d       ~b~Altitude: ~w~%d~n~~b~Fuel: ~%s~%s       ~b~ODO: ~%s~%s~n~~b~Health: ~%s~%.0f%%    ~w~%s~n~%s",
		AIRSPEED(gamedata.carspeed), (int) gamedata.carz, (fuelvalue < 20 && gamedata.blinkstatus ? "y" : "w"), fuel, odocolor, odo,
		(hp < 35.0f && gamedata.blinkstatus ? "y" : "w"), hp, satisfstr, destnearstr);
	memcpy(samptd->szText, mainstring, 700);
	memcpy(samptd->szString, mainstring, 700);
	fuel[0] = 0;
	destnearstr[0] = 0;
	satisfstr[0] = 0;
	odo[0] = 0;
}

void damagepcthandler(struct SPLHXTEXTDRAW *hxtd, struct stTextdraw *samptd, int reason)
{
	TRACE("damagepcthandler\n");
	REPOSITION_ON_ATTACH();
	if (ISPLANE) {
		char damagepctstring[7];
		sprintf(damagepctstring, "%.0f%%", (float)gamedata.carhp / 10.0f);
		memcpy(samptd->szText, damagepctstring, 7);
		memcpy(samptd->szString, damagepctstring, 7);
		samptd->fLetterWidth = 0.0f;
		return;
	}
	samptd->fLetterWidth = 0.27f;
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

void fuelhandler(struct SPLHXTEXTDRAW *hxtd, struct stTextdraw *samptd, int reason)
{
	TRACE("fuelhandler\n");
	REPOSITION_ON_ATTACH();
	if (ISPLANE) {
		samptd->fLetterWidth = 0.0f;
		return;
	}
	samptd->fLetterWidth = 0.289999f;
}

void fueldmgboxhandler(struct SPLHXTEXTDRAW *hxtd, struct stTextdraw *samptd, int reason)
{
	TRACE("fueldmgboxhandler\n");
	REPOSITION_ON_ATTACH();
	if (ISPLANE) {
		samptd->byteBox = 0;
		return;
	}
	samptd->byteBox = 1;
}

void damagebarhandlerex(struct SPLHXTEXTDRAW *hxtd, struct stTextdraw *samptd, int reason)
{
	TRACE("damagebarhandlerex\n");
	REPOSITION_ON_ATTACH();
	samptd->szText[0] = '_';
	samptd->szString[0] = '_';
	if (ISPLANE) {
		samptd->byteBox = 0;
		return;
	}
	samptd->byteBox = 1;
	damagebarhandler(hxtd, samptd, reason);
}

void progressbarpatchhandlerex(struct SPLHXTEXTDRAW *hxtd, struct stTextdraw *samptd, int reason)
{
	TRACE("progressbarpatchhandler\n");
	REPOSITION_ON_ATTACH();
	samptd->szText[0] = '_';
	samptd->szString[0] = '_';
	samptd->byteBox = 0;
	if (ISPLANE) {
		return;
	}
	if (INCAR) {
		samptd->byteBox = 1;
	}
}

BOOL setupTextdraws()
{
	fuel[0] = 0;
	destnearstr[0] = 0;
	satisfstr[0] = 0;
	odo[0] = 0;
	odocolor[0] = 'w';
	odocolor[1] = 0;
	setupTD(PLTD_FUEL, 0x44078000, 0x43C48000, 0x44078000, 0x43C48148, &fuelhandler);
	setupTD(PLTD_DAMAGE, 0x44044000, 0x43CB0000, 0x44044000, 0x43CB0148, &damagepatchhandlerex);
	setupTD(PLTD_STATUSBARBOX, 0x43A00000, 0x43D60000, 0x43A00000, 0x43D70000, &statusbarhandler);
	setupTD(PLTD_FUELDMGBOX, 0x4403C000, 0x43C48000, 0x4403C000, 0x43C48148, &fueldmgboxhandler);
	setupTD(PLTD_FUELPRICE, 0x44000000, 0x42C80000, 0, 0, NULL);
	setupTD(PLTD_SATISF, 0x44108000, 0x43B58000, 0, 0, &satisfhandler);
	setupTD(PLTD_FUELBAR, 0x440E4000, 0x43C78000, 0x440E4000, 0x43C78148, &progressbarpatchhandlerex);
	setupTD(PLTD_STATUSBAR, 0x43A00000, 0x43D60000, 0x43A00000, 0x43D70000, &statusbarhandler);
	setupTD(PLTD_DMGBAR, 0x440E4000, 0x43CE8000, 0x440E4000, 0x43CE8148, &damagebarhandlerex);
	setupTD(PLTD_ODO, 0x43FA8000, 0x43C80000, 0, 0, &odohandler);
	setupTD(PLTD_AIRSPEED, 0x43E38000, 0x43C80000, 0x43520000, 0x43B40000, &hijackhandler);
	setupTD(PLTD_ALTITUDE, 0x43CC0000, 0x43C80000, 0, 0, &boxremovehandler);
	setupTD(PLTD_GPS, 0x43430000, 0x43C80000, 0x42AA0000, 0x43A00000, &gpshandler);
	setupTD(PLTD_DESTNEAREST, 0x439D0000, 0x43C80000, 0, 0, &destnearesthandler);
	//setupTD(PLTD_DESTNEAREST, 0x439D0000, 0x43C80000, 0x439D0000, 0x43C80148, NULL);
	setupTD(PLTD_FUELPCT, 0x44124000, 0x43C60000, 0x44124000, 0x43C60148, &fuelpcthandler);
	setupTD(PLTD_DAMAGEPCT, 0x44128000, 0x43CD0000, 0x44128000, 0x43CD0148, &damagepcthandler);
	setupTD(PLTD_HEADING, 0x439e0000, 0x40000000, 0x439e0000, 0x40200000, &headinghandler);
	return TRUE;
}

#endif
