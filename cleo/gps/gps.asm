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
lea eax, [eax+0x46C] ; pedFlags
test eax, 0x100 ; bInVehicle
jz nogps2
mov edi, [edi+0x590] ; carType
cmp edi, 0x3 ; heli
jge nogps2

push 0
push _var01
call 0x56E010
add esp, 0x8

mov eax, [0x40CA27]

; push this
; push 0 ; pathType
; push _var01 ; origin
; push _var02 ; originAddr
; push target
; push pResultNodes
; push _var03 ; pNodesCount
; push 2000 ; maxNodesToFind
; push _var04 ; pDistance
; push 0xF0237449 ; (999999.0f) maxSearchDistance
; push 0 ; targetAttr
; push 0xF0237449 ; (999999.0f) maxUnkLimit
; push 0 ; oneSideOnly
; push _var02 ; forbiddenNodeAddr
; push 0 ; includeNodesWithoutLinks
; push 0 ; waterPath
; call 0x4515D0

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