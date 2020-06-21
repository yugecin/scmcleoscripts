#pragma once

#include "Stdafx.h"
#include "CLEO.h"
#include "samp.h"

BOOL setupTextdraws();
BOOL InitOpcodes();
#if SNOOP
OpcodeResult WINAPI op6C36(CScriptThread *thread);
#endif
OpcodeResult WINAPI op6C37(CScriptThread *thread);

#define INVALID_TEXTDRAW	(-1)
#define TDHANDLER_ATTACH	(1)
#define TDHANDLER_UPDATE	(2)

#define THEME_STANDARD		1
#define THEME_CLASSIC		2
#define THEME_ROBIN		3

// ----------------------

#if !defined THEME
#define THEME			THEME_ROBIN
#endif
//#define SNOOP 1
//#define DOTRACE 1

// ----------------------

#if DOTRACE
#define TRACE1(x,y) {char dbgStr[200];sprintf(dbgStr, x, y);trace(dbgStr);}
#define TRACE(x) TRACE1(x,0)
void trace(const char *f);
#else
#define TRACE(x)
#define TRACE1(x,y)
#endif

#define AIRSPEEDF(x)		(14.5f*x/7.5f)
#define AIRSPEED(x)		(int)(AIRSPEEDF(x))
#define GROUNDSPEED(x)		(int)(100.0f*x/27.8f)

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
	PLTD_CARSPEED,
	PLTD_CARODO,
	PLTDCOUNT,
};

inline int isplayertd(int td) { return td == PLTD_CARSPEED || td == PLTD_CARODO; }

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
	int		isplane;
	int		blinkstatus;
};

#define INCAR (gamedata.carhp != -1)
#define ISPLANE (gamedata.isplane)

void setupTD(int tdidx, unsigned int x, unsigned int y, unsigned int targetX, unsigned int targetY, TDHANDLER handler);

extern SGAMEDATA gamedata;
