#pragma once
#include "Stdafx.h"
#include "CLEO.h"
#include "samp.h"

BOOL setupTextdraws();
BOOL setupPlayerTextdraws();
BOOL InitOpcodes();
OpcodeResult WINAPI op0C36(CScriptThread *thread);
OpcodeResult WINAPI op0C37(CScriptThread *thread);

#define INVALID_TEXTDRAW	(-1)
#define TDHANDLER_ATTACH	(1)
#define TDHANDLER_UPDATE	(2)

#define THEME_STANDARD		1
#define THEME_CLASSIC		2
#define THEME_ROBIN		3

// ----------------------

#define THEME			THEME_STANDARD
#define SNOOP 1
//#define DOTRACE 1

// ----------------------

#if DOTRACE
#define TRACE1(x,y) {char dbgStr[100];sprintf(dbgStr, x, y);trace(dbgStr);}
#define TRACE(x) TRACE1(x,0)
#else
#define TRACE(x)
#define TRACE1(x,y)
#endif

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

#define REPOSITION_ON_ATTACH() if(reason==TDHANDLER_ATTACH){samptd->fX=hxtd->fTargetX;samptd->fY=hxtd->fTargetY;return;}

enum PLTEXTDRAWS
{
	PLTD_FUEL,
	PLTD_DAMAGE,
	PLTD_STATUSBARBOX,
	PLTD_FUELDMGBOX,
	PLTD_FUELPRICE,
	PLTD_SATISF,
	PLTD_FUELBAR,
	PLTD_STATUSBAR,
	PLTD_DMGBAR,
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
	float		carx;
	float		cary;
	float		carz;
	float		carspeed;
	int		missiondistance;
};

#define INCAR (gamedata.carhp != -1)

void setupTD(int tdidx, unsigned int x, unsigned int y, unsigned int targetX, unsigned int targetY, TDHANDLER handler);
void trace(const char *f);

extern SGAMEDATA gamedata;
