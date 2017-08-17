
#include "opcodes.h"
#include "commonhandlers.h"

#if THEME == THEME_STANDARD

void destnearesthandler(struct SPLHXTEXTDRAW *hxtd, struct stTextdraw *samptd, int reason)
{
	TRACE("destnearesthandler\n");
	REPOSITION_ON_ATTACH();
	if (!INCAR) {
		return;
	}
	if (gamedata.missiondistance == -1 || samptd->szText[0] != 'D') {
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
	if (c == 0) {
		sprintf(samptd->szString, "Destination (%d M)", gamedata.missiondistance);
	} else {
		sprintf(samptd->szString, "Destination (%d M)%s", gamedata.missiondistance, &(samptd->szText[destinationidx]));
	}
	memcpy(samptd->szText, samptd->szString, 100);
}

void damagepcthandler(struct SPLHXTEXTDRAW *hxtd, struct stTextdraw *samptd, int reason)
{
	TRACE("damagepcthandler\n");
	REPOSITION_ON_ATTACH();
	if (!INCAR) {
		return;
	}
	sprintf(samptd->szString, "%.0f%%", (float) gamedata.carhp / 10.0f);
	memcpy(samptd->szString, samptd->szString, 7);
}

void fuelpricehandler(struct SPLHXTEXTDRAW *hxtd, struct stTextdraw *samptd, int reason)
{
	TRACE("fuelpricehandler\n");
	REPOSITION_ON_ATTACH();
}

void airspeedhandler(struct SPLHXTEXTDRAW *hxtd, struct stTextdraw *samptd, int reason)
{
	TRACE("airspeedhandler\n");
	REPOSITION_ON_ATTACH();
	if (!INCAR) {
		return;
	}
	sprintf(&samptd->szText[14], "%d KTS", AIRSPEED(gamedata.carspeed));
	memcpy(&samptd->szString[14], &samptd->szText[14], 10);
}

void altitudehandler(struct SPLHXTEXTDRAW *hxtd, struct stTextdraw *samptd, int reason)
{
	TRACE("altitudehandler\n");
	REPOSITION_ON_ATTACH();
	if (!INCAR) {
		return;
	}
	sprintf(&samptd->szText[14], "%d FT", (int) gamedata.carz);
	memcpy(&samptd->szString[14], &samptd->szText[14], 10);
}

BOOL setupTextdraws()
{
	setupTD(PLTD_FUEL, 0x44078000, 0x43C48000, 0, 0, NULL);
	setupTD(PLTD_DAMAGE, 0x44044000, 0x43CB0000, 0x44044000, 0x43CB0148, &damagepatchhandler);
	setupTD(PLTD_STATUSBARBOX, 0x43A00000, 0x43D60000, 0, 0, NULL);
	setupTD(PLTD_FUELDMGBOX, 0x4403C000, 0x43C48000, 0, 0, NULL);
	setupTD(PLTD_FUELPRICE, 0x44000000, 0x42C80000, 0, 0, NULL);
	setupTD(PLTD_SATISF, 0x44108000, 0x43B58000, 0, 0, NULL);
	setupTD(PLTD_FUELBAR, 0x440E4000, 0x43C78000, 0x440E4000, 0x43C78148, &progressbarpatchhandler);
	setupTD(PLTD_STATUSBAR, 0x43A00000, 0x43D60000, 0, 0, NULL);
	setupTD(PLTD_DMGBAR, 0x440E4000, 0x43CE8000, 0x440E4000, 0x43CE8148, &damagebarhandler);
	setupTD(PLTD_ODO, 0x43FA8000, 0x43C80000, 0, 0, NULL);
	setupTD(PLTD_AIRSPEED, 0x43E38000, 0x43C80000, 0x43E38000, 0x43C80148, &airspeedhandler);
	setupTD(PLTD_ALTITUDE, 0x43CC0000, 0x43C80000, 0x43CC0000, 0x43C80148, &altitudehandler);
	setupTD(PLTD_GPS, 0x43430000, 0x43C80000, 0, 0, NULL);
	setupTD(PLTD_DESTNEAREST, 0x439D0000, 0x43C80000, 0x439D0000, 0x43C80148, &destnearesthandler);
	setupTD(PLTD_FUELPCT, 0x44124000, 0x43C60000, 0, 0, NULL);
	setupTD(PLTD_DAMAGEPCT, 0x44128000, 0x43CD0000, 0x44128000, 0x43CD0148, &damagepcthandler);
	setupTD(PLTD_HEADING, 0x439e0000, 0x40000000, 0x439e0000, 0x40200000, &headinghandler);
	return TRUE;
}

#endif
