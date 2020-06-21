/*
	following structs in this file are from the mod_sa project

	PROJECT:		mod_sa
	COPYRIGHT:		Copyright we_sux, BlastHack
	mod_sa is available from https://github.com/BlastHackNet/mod_s0beit_sa/
	mod_sa is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.
	mod_sa is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.
	You should have received a copy of the GNU General Public License
	along with mod_sa.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "stuff.h"
#include "windows.h"

enum Limits
{
	SAMP_MAX_ACTORS = 1000,
	SAMP_MAX_PLAYERS = 1004,
	SAMP_MAX_VEHICLES = 2000,
	SAMP_MAX_PICKUPS = 4096,
	SAMP_MAX_OBJECTS = 1000,
	SAMP_MAX_GANGZONES = 1024,
	SAMP_MAX_3DTEXTS = 2048,
	SAMP_MAX_TEXTDRAWS = 2048,
	SAMP_MAX_PLAYERTEXTDRAWS = 256,
	SAMP_MAX_CLIENTCMDS = 144,
	SAMP_MAX_MENUS = 128,
	SAMP_MAX_PLAYER_NAME = 24,
	SAMP_ALLOWED_PLAYER_NAME_LENGTH = 20,
};

#pragma pack(push, 1)
struct stSAMPPools
{
	void	   			*pActor; // stActorPool
	void	   			*pObject; // stObjectPool
	void				*pGangzone; // stGangzonePool
	void				*pText3D; // stTextLabelPool
	struct stTextdrawPool		*pTextdraw;
	void				*pPlayerLabels;
	void				*pPlayer; // stPlayerPool
	void				*pVehicle; // stVehiclePool
	void				*pPickup; // stPickupPool
};

struct stSAMP
{
	void				*pUnk0;
	void				*pServerInfo; // stServerInfo
	char				byteSpace[24];
	char				szIP[257];
	char				szHostname[259];
	BYTE				bNametagStatus; // changes by /nametagstatus // is bool, shown as byte for 1 byte emphasis
	unsigned int			ulPort;
	unsigned int			ulMapIcons[100];
	int				iLanMode;
	int				iGameState;
	unsigned int			ulConnectTick;
	void				*pSettings; // stServerPresets
	void				*pRakClientInterface;
	struct stSAMPPools		*pPools;
};

struct stTextdraw
{
	char		szText[800 + 1];
	char		szString[1600 + 2];
	float		fLetterWidth;
	float		fLetterHeight;
	DWORD		dwLetterColor;
	char		byte_unk;	// always = 01 (?) (justified?)
	BYTE		byteCenter;
	BYTE		byteBox;
	float		fBoxSizeX;
	float		fBoxSizeY;
	DWORD		dwBoxColor;
	BYTE		byteProportional;
	DWORD		dwShadowColor;
	BYTE		byteShadowSize;
	BYTE		byteOutline;
	BYTE		byteLeft;
	BYTE		byteRight;
	int		iStyle;		// font style/texture/model
	float		fX;
	float		fY;
	BYTE		unk[8];
	DWORD		dword99B;	// -1 by default
	DWORD		dword99F;	// -1 by default
	DWORD		index;		// -1 if bad
	BYTE		byte9A7;	// = 1; 0 by default
	UINT16		sModel;
	float		fRot[3];
	float		fZoom;
	WORD		sColor[2];
	BYTE		f9BE;
	BYTE		byte9BF;
	BYTE		byte9C0;
	DWORD		dword9C1;
	DWORD		dword9C5;
	DWORD		dword9C9;
	DWORD		dword9CD;
	BYTE		byte9D1;
	DWORD		dword9D2;
};
EXPECT_SIZE(struct stTextdraw, 0x9D6);

struct stTextdrawPool
{
	int			iIsListed[SAMP_MAX_TEXTDRAWS];
	int			iPlayerTextDraw[SAMP_MAX_PLAYERTEXTDRAWS];
	struct stTextdraw	*textdraw[SAMP_MAX_TEXTDRAWS];
	struct stTextdraw	*playerTextdraw[SAMP_MAX_PLAYERTEXTDRAWS];
};
#pragma pack(pop)

stSAMP *getSamp();
