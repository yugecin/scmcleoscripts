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

; initialize verts
mov eax, [_var0B] ; vert
add eax, 0x8
cmp dword ptr [eax], 0x38D1B717
je vertsinitialized
mov edi, 0x1F40 ; nodecount * 4 (8000)
initnextvert:
mov dword ptr [eax], 0x38D1B717 ; 0.0001f NearScreenZ
add eax, 0x4
mov dword ptr [eax], 0x40555555 ; 3.333333254f RecipNearClip
add eax, 0x4
mov dword ptr [eax], 0xFFB41818 ; col
add eax, 0x4
mov dword ptr [eax], 0x0 ; u
add eax, 0x4
mov dword ptr [eax], 0x0 ; v
add eax, 0xC
dec edi
test edi, edi
jnz initnextvert

vertsinitialized:
push 0
push _var01
call 0x56E010 ; RwV3D *__cdecl getPlayerCoords(RwV3D *outPoint, int playerIndex)
;add esp, 0x8

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
push 0x7D0 ; (2000) maxNodesToFind
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
mov ecx, [0x40CA27] ; this
call 0x4515D0 ; __thiscall CPathFind::DoPathSearch

mov ax, [_var03] ; pNodesCount
test ax, ax
jz nogps2

push ebx
push edx ; changed by 0x420AC0
mov bx, ax

mov edi, 0
transformnextnode:

push [edi*4+_var06] ; address
mov ecx, [0x40CA27] ; this
call 0x420AC0 ; __thiscall CPathNode *CPathFind::GetPathNode
push _var07 ; pResult
mov ecx, eax ; this
call 0x420A10 ; __thiscall CPathNode::GetNodeCoors
push _var07 ; pIn
push _var08 ; pOut
call 0x583530 ; cdecl void CRadar::TransformRealWorldPointToRadarSpace(CVector2D &out,CVector2D const&in)
; push _var08 ; pPoint
call 0x5832F0 ; cdecl float CRadar::LimitRadarPoint(CVector2D &point)
fstp dword ptr [_var01] ; (origin, junk)
;push _var08 ; pIn
lea eax, [edi*8+_var09]
push eax
call 0x583480 ; cdecl void CRadar::TransformRadarPointToScreenSpace(CVector2D &out,CVector2D const&in)
pop eax
add esp, 0x8

; fild dword ptr [edi*8+_var09]
; fild dword ptr [0x9B48D8+0x4] ; RsGlobal.maximumWidth
; fld dword ptr [_var0A] ; (640.0)
; fdivp
; fmulp
; fstp dword ptr [edi*8+_var09]

; fild dword ptr [edi*8+_var09+0x4]
; fild dword ptr [0x9B48D8+0x8] ; RsGlobal.maximumWidth
; fld dword ptr [_var0A+0x4] ; (448.0)
; fdivp
; fmulp
; fstp dword ptr [edi*8+_var09+0x4]

lea eax, [edi*8+_var09+0x4]
push eax ; pY
sub eax, 0x4
push eax ; pX
call 0x583350 ; cdecl void CRadar::LimitToMap(float *pX,float *pY)
;add esp, 0x8

push 0 ; value
push 1 ; state (rwRENDERSTATETEXTURERASTER)
mov eax, [0xC97B24] ; RwEngineInstance
call [eax+0x20] ; RwBool RwRenderStateSet(RwRenderState state, void* value)
add esp, 0x10

inc edi
dec bx
test bx, bx
jnz transformnextnode



mov ax, [_var03] ; pNodesCount
mov bx, ax
mov eax, [_var0B] ; vert
mov edx, _var09 ; nodepoint
nextnodeverts:

mov edi, [edx]
mov dword ptr [eax], edi ; x
mov edi, [edx+0x4]
mov dword ptr [eax+0x4], edi ; y

add eax, 0x1C

push [edx]
fld dword ptr [esp]
fldpi
faddp ST(1), ST(0)
fstp dword ptr [esp]
pop edi
mov dword ptr [eax], edi ; x
push [edx+0x4]
fld dword ptr [esp]
fldpi
faddp ST(1), ST(0)
fstp dword ptr [esp]
pop edi
mov dword ptr [eax+0x4], edi ; y

add edx, 0x8
add eax, 0x1C

mov edi, [edx]
mov dword ptr [eax], edi ; x
mov edi, [edx+0x4]
mov dword ptr [eax+0x4], edi ; y

add eax, 0x1C

push [edx]
fld dword ptr [esp]
fldpi
faddp ST(1), ST(0)
fstp dword ptr [esp]
pop edi
mov dword ptr [eax], edi ; x
push [edx+0x4]
fld dword ptr [esp]
fldpi
faddp ST(1), ST(0)
fstp dword ptr [esp]
pop edi
mov dword ptr [eax+0x4], edi ; y

add edx, 0x8
add eax, 0x1C

dec bx
test bx, bx
jnz nextnodeverts

mov eax, [_var03] ; pNodesCount
imul eax, 0x4
push eax ; numVertices
push [_var0B] ; vertices
push 4 ; primType (rwPRIMTYPETRISTRIP)
mov eax, [0xC97B24] ; RwEngineInstance
call [eax+0x30] ; RwBool RwIm2DRenderPrimitiveFunction(RwPrimitiveType primType, RwIm2DVertex *vertices, RwInt32 numVertices);
add esp, 0xC


pop edx
pop ebx
nogps2:
pop edi
nogps:
jmp 0x5869C4