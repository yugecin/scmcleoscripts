#pragma once
#include "Stdafx.h"
#include "CLEO.h"
#include "samp.h"

BOOL setupTextdraws();
BOOL InitOpcodes();
OpcodeResult WINAPI op0C36(CScriptThread *thread);
OpcodeResult WINAPI op0C37(CScriptThread *thread);

#define INVALID_TEXTDRAW	(-1)
#define TDHANDLER_ATTACH	(1)
#define TDHANDLER_UPDATE	(2)

typedef void (*TDHANDLER)(struct SPLHXTEXTDRAW *hxtd, struct stTextdraw *samptd, int reason);

struct SPLHXTEXTDRAW
{
	int			iHandle;
	float			fX;
	float			fY;
	float			fTargetX;
	float			fTargetY;
	TDHANDLER		handler;
};

void removehandler(struct SPLHXTEXTDRAW *hxd, struct stTextdraw *samptd, int reason);
void airspeedhandler(struct SPLHXTEXTDRAW *hxd, struct stTextdraw *samptd, int reason);
void boxremovehandler(struct SPLHXTEXTDRAW *hxd, struct stTextdraw *samptd, int reason);
void fuelpricehandler(struct SPLHXTEXTDRAW *hxd, struct stTextdraw *samptd, int reason);
void gpshandler(struct SPLHXTEXTDRAW *hxd, struct stTextdraw *samptd, int reason);
void headinghandler(struct SPLHXTEXTDRAW *hxd, struct stTextdraw *samptd, int reason);

enum PLTEXTDRAWS
{
	PLTD_FUEL,
	PLTD_DAMAGE,
	PLTD_BOX0,
	PLTD_BOX1,
	PLTD_FUELPRICE,
	PLTD_SATISF,
	PLTD_BOX2,
	PLTD_STATUSBAR,
	PLTD_BOX3,
	PLTD_ODO,
	PLTD_AIRSPEED,
	PLTD_ALTITUDE,
	PLTD_GPS,
	PLTD_DESTNEAREST,
	PLTD_FUELPCT,
	PLTD_DAMAGEPCT,
	PLTD_HEADING,
	PLTDCOUNT,
};

struct SGAMEDATA
{
	int		carhp;
	int		carheading;
	float		carspeedx;
	float		carspeedy;
	float		carspeedz;
	int		carspeed;
};
