
#include "opcodes.h"

#if THEME == THEME_STANDARD

void destnearesthandler(struct SPLHXTEXTDRAW *hxtd, struct stTextdraw *samptd, int reason)
{
	TRACE("destnearesthandler\n");
	REPOSITION_ON_ATTACH();
	if (!INCAR) {
		return;
	}
	if (gamedata.missiondistance == -1 || samptd->szString[0] != 'D') {
		return;
	}
	int destinationidx = 0;
	char c = 0;
	while (true) {
		c = samptd->szText[destinationidx];
		if (c == '~' || c == 0) {
			break;
		}
		if (++destinationidx > 150) {
			break;
		}
	}
	char destinationstring[100];
	if (c == 0) {
		sprintf(destinationstring, "Destination (%d M)", gamedata.missiondistance);
	} else {
		sprintf(destinationstring, "Destination (%d M)%s", gamedata.missiondistance, &(samptd->szText[destinationidx]));
	}
	memcpy(samptd->szText, destinationstring, 100);
	memcpy(samptd->szString, destinationstring, 100);
}

void damagepcthandler(struct SPLHXTEXTDRAW *hxtd, struct stTextdraw *samptd, int reason)
{
	TRACE("damagepcthandler\n");
	REPOSITION_ON_ATTACH();
	if (!INCAR) {
		return;
	}
	char damagepctstring[7];
	sprintf(damagepctstring, "%.0f%%", (float) gamedata.carhp / 10.0f);
	memcpy(samptd->szText, damagepctstring, 7);
	memcpy(samptd->szString, damagepctstring, 7);
}

void fuelpricehandler(struct SPLHXTEXTDRAW *hxtd, struct stTextdraw *samptd, int reason)
{
	TRACE("fuelpricehandler\n");
	REPOSITION_ON_ATTACH();
}

void removehandler(struct SPLHXTEXTDRAW *hxtd, struct stTextdraw *samptd, int reason)
{
	TRACE("removehandler\n");
	REPOSITION_ON_ATTACH();
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
	REPOSITION_ON_ATTACH();
}

void airspeedhandler(struct SPLHXTEXTDRAW *hxtd, struct stTextdraw *samptd, int reason)
{
	TRACE("airspeedhandler\n");
	REPOSITION_ON_ATTACH();
	if (!INCAR) {
		return;
	}
	char airspeedstring[10];
	sprintf(airspeedstring, "%d KTS", (int) (14.5f * gamedata.carspeed / 7.5f));
	memcpy(&samptd->szText[14], airspeedstring, 10);
	memcpy(&samptd->szString[14], airspeedstring, 10);
}

void altitudehandler(struct SPLHXTEXTDRAW *hxtd, struct stTextdraw *samptd, int reason)
{
	TRACE("altitudehandler\n");
	REPOSITION_ON_ATTACH();
	if (!INCAR) {
		return;
	}
	char altitudestring[10];
	sprintf(altitudestring, "%d FT", (int) gamedata.carz);
	memcpy(&samptd->szText[14], altitudestring, 10);
	memcpy(&samptd->szString[14], altitudestring, 10);
}

void headinghandler(struct SPLHXTEXTDRAW *hxtd, struct stTextdraw *samptd, int reason)
{
	TRACE("headinghandler\n");
	REPOSITION_ON_ATTACH();
	if (!INCAR) {
		return;
	}
#define HEADINGSTRLEN (3 + 1 + 3 + 1 + 3 + 1 + 5 + 1 + 3 + 1 + 3 + 1 + 3 + 1)
	char headingstring[HEADINGSTRLEN];
	int n[7];
	for (int i = 0; i < 7; i++) {
		n[i] = (360 - gamedata.carheading) - 3 + i;
		if (n[i] < 1) n[i] += 360;
		if (n[i] > 360) n[i] -= 360;
	}
	sprintf(headingstring, "%03d %03d %03d [%03d] %03d %03d %03d", n[0], n[1], n[2], n[3], n[4], n[5], n[6]);
	memcpy(samptd->szText, headingstring, HEADINGSTRLEN);
	memcpy(samptd->szString, headingstring, HEADINGSTRLEN);
#undef HEADINGSTRLEN
}

void progressbarpatchhandler(struct SPLHXTEXTDRAW *hxtd, struct stTextdraw *samptd, int reason)
{
	TRACE("progressbarpatchhandler\n");
	REPOSITION_ON_ATTACH();
	samptd->szText[0] = '_';
	samptd->szString[0] = '_';
	if (!INCAR) {
		samptd->dwBoxColor &= 0x00ffffff;
	} else {
		samptd->dwBoxColor |= 0xff000000;
	}
}

void damagebarhandler(struct SPLHXTEXTDRAW *hxtd, struct stTextdraw *samptd, int reason)
{
	TRACE("damagebarhandler\n");
	REPOSITION_ON_ATTACH();
	if (!INCAR) {
		return;
	}
	progressbarpatchhandler(hxtd, samptd, reason);
	samptd->fBoxSizeX = 569.0f + (float) gamedata.carhp * 63.0f / 1000.0f;
}

BOOL setupTextdraws()
{
	setupTD(PLTD_FUEL, 0x44078000, 0x43C48000, 0, 0, NULL);
	setupTD(PLTD_DAMAGE, 0x44044000, 0x43CB0000, 0, 0, NULL);
	setupTD(PLTD_STATUSBARBOX, 0x43A00000, 0x43D60000, 0, 0, NULL);
	setupTD(PLTD_FUELDMGBOX, 0x4403C000, 0x43C48000, 0, 0, NULL);
	setupTD(PLTD_FUELPRICE, 0x44000000, 0x42C80000, 0, 0, NULL);
	setupTD(PLTD_SATISF, 0x44108000, 0x43B58000, 0, 0, NULL);
	setupTD(PLTD_FUELBAR, 0x440E4000, 0x43C78000, 0x440E4000, 0x43C78148, &progressbarpatchhandler);
	setupTD(PLTD_STATUSBAR, 0x43A00000, 0x43D60000, 0, 0, 0);
	setupTD(PLTD_DMGBAR, 0x440E4000, 0x43CE8000, 0x440E4000, 0x43CE8148, &damagebarhandler);
	setupTD(PLTD_ODO, 0x43FA8000, 0x43C80000, 0, 0, NULL);
	setupTD(PLTD_AIRSPEED, 0x43E38000, 0x43C80000, 0x43E38000, 0x43C80148, &airspeedhandler);
	setupTD(PLTD_ALTITUDE, 0x43CC0000, 0x43C80000, 0x43CC0000, 0x43C80148, &altitudehandler);
	setupTD(PLTD_GPS, 0x43430000, 0x43C80000, 0, 0, NULL);
	setupTD(PLTD_DESTNEAREST, 0x439D0000, 0x43C80000, 0x439D0000, 0x43C80148, &destnearesthandler);
	setupTD(PLTD_FUELPCT, 0x44124000, 0x43C60000, 0, 0, NULL);
	setupTD(PLTD_DAMAGEPCT, 0x44128000, 0x43CD0000, 0x44128000, 0x43CD0148, &damagepcthandler);
	setupTD(PLTD_HEADING, 0x439e0000, 0x40000000, 0x439e0000, 0x40200000, &headinghandler);
	//setupTD(PLTD_HEADING, 0x439e0000, 0x40000000, 0x439e0000, 0x40200000, NULL);
	return TRUE;
}

#endif
