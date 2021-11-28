;extern _OutputDebugStringA@4
extern _GetModuleHandleA@4
extern _VirtualProtect@16

DLL_PROCESS_ATTACH equ 1
PAGE_EXECUTE_READWRITE equ 0x40

section .data ; Initialized data segment
	;debugOk db "ZZ3DBlipsSARemoveHouseIcons ok", 0
	blipModuleName db "3DBlipsSA.asi", 0

section .bss ; Uninitialized data segment
	module dd ?

section .text
hookfunc:
	; ecx gets overwritten in either case (skip or no skip) so it's safe to use
	mov ecx, dword [module]
	cmp edx, 31 ; green house (radar_propertyG)
	jz skiphouse
	cmp edx, 32 ; red house (radar_propertyR)
	jz skiphouse
	; do the line we overwrote to perform this jmp (mov     eax, off_1008E040[edx*4])
	mov eax, [ecx+edx*4+08E040h] ; don't touch eax after this!!
	; jmp back to were we hooked from
	add ecx, 031F58h
	jmp ecx
skiphouse:
	; jmp to exit of function we hooked from, to skip this icon
	add ecx, 03223Dh
	jmp ecx

global dllmain
dllmain:
	push esi
	mov eax, [esp+0Ch] ; ul_reason_for_call
	cmp eax, DLL_PROCESS_ATTACH
	jnz ret

	push blipModuleName
	call _GetModuleHandleA@4 ; get base of the dll
	test eax, eax
	jz ret

	mov dword [module], eax
	mov esi, eax
	add esi, 031F51h ; this is the "mov     eax, off_1008E040[edx*4]" line
	;push debugOk
	;call _OutputDebugStringA@4

	sub esp, 04h ; space for oldvp
	push esp ; oldvp
	push PAGE_EXECUTE_READWRITE
	push 5 ; length
	push esi ; address
	call _VirtualProtect@16 ; memprotect so we can override that line with a jmp
	add esp, 04h ; reclaim space used for oldvp

	mov eax, hookfunc
	sub eax, esi
	sub eax, 05h ; get relative offset of hookfunc from where we're jmp'ing
	mov byte [esi], 0xE9 ; jmp
	mov dword [esi+1], eax

ret:
	pop esi
	mov eax, 1
	ret 0Ch
