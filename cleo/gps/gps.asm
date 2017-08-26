;rewritecall 0x5869C0

;0x5759E4 ; map
;0x5869BF ; radar

call 0x586650 ; _?paintMapZones 0x586650

call 0x56E210 ; CPed *__cdecl getPlayerPed(int number)
test eax, eax
jz nogps
push edi
lea edi, [eax+0x58C] ; pVehicle
test edi, edi
jz nogps2
mov edi, [eax+0x58C]
mov eax, [eax+0x46C] ; pedFlags
test eax, 0x100 ; bInVehicle
jz nogps2
mov edi, [edi+0x590] ; carType
cmp edi, 0x3 ; heli
jge nogps2

push 0
push _var01
call 0x56E010 ; RwV3D *__cdecl getPlayerCoords(RwV3D *outPoint, int playerIndex)

push [_var05]
push [_var05+0x4]
call 0x569660 ; float __cdecl CWorld::findGroundZForCoord(float X, float Y)
fstp dword ptr [_var05+0x8]
add esp, 0x10

push 0 ; waterPath
push 0 ; includeNodesWithoutLinks
push 0xFFFFFFFF ; forbiddenNodeAddr
push 0 ; oneSideOnly
push 0x497423f0 ; (999999.0f) maxUnkLimit
push 0 ; targetAttr
push 0x497423f0 ; (999999.0f) maxSearchDistance
push _var04 ; pDistance
push 0x7D0 ; maxNodesToFind
push _var03 ; pNodesCount
push _var06 ; pResultNodes
push [_var05+0x8] ; target.z
push [_var05+0x4] ; target.y
push [_var05] ; target.x
push 0xFFFFFFFF ; originAddr
push [_var01+0x8] ; origin.z
push [_var01+0x4] ; origin.y
push [_var01] ; origin.x
push 0x0 ; pathType
mov ecx, [0x40CA27]
call 0x4515D0 ; __thiscall!! CPathFind::DoPathSearch

; void CPathFind::DoPathSearch(unsigned char pathType, CVector origin, CNodeAddress originAddr, 
		; CVector target, CNodeAddress *pResultNodes, short *pNodesCount, int maxNodesToFind, float *pDistance, 
		; float maxSearchDistance, CNodeAddress *targetAddr, float maxUnkLimit, bool oneSideOnly, 
		; CNodeAddress forbiddenNodeAddr, bool includeNodesWithoutLinks, bool waterPath)
; {
	; ((void (__thiscall *)(CPathFind *, unsigned char, CVector, CNodeAddress, CVector, CNodeAddress *,
		; short *, int, float *, float, CNodeAddress *, float, bool, CNodeAddress, bool, bool))0x4515D0)(
		; this, pathType, origin, originAddr, target, pResultNodes, pNodesCount, maxNodesToFind, pDistance, 
		; maxSearchDistance, targetAddr, maxUnkLimit, oneSideOnly, forbiddenNodeAddr, includeNodesWithoutLinks, 
		; waterPath);
; }

nogps2:
pop edi
nogps:
jmp 0x5869C4