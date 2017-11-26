; _ASM_HOOKADDR: 0058EAF1
; _ASM_JUMP: true
; _ASM_CORRECT_OFFSETS: true
; _ASM_COMMENTS: false
; _ASM_GCC: S:\broftware\perl\c\bin\gcc.exe
; _ASM_OBJDUMP: S:\broftware\perl\c\bin\objdump.exe
; _ASM_TARGETFILE: plhud-asm.txt
; _ASM_PREPROCONLY: false
; _ASM_LF: true

; hook on 0058EAF0 _DrawHud (0058EAF1 in asmtool)

; _DEFINE:__drawText=0x71A700
; _DEFINE:CText__SetBorderEffectRGBA=0x719510
; _DEFINE:CText__SetFont=0x719490
; _DEFINE:CText__SetTextAlignment=0x719610
; _DEFINE:CText__SetTextBackground=0x7195C0
; _DEFINE:CText__SetTextColour=0x719430
; _DEFINE:CText__SetTextLetterSize=0x719380
; _DEFINE:CText__SetTextOutline=0x719590
; _DEFINE:CText__SetTextUseProportionalValues=0x7195B0
; _DEFINE:dummy_7194F0=0x7194F0

; _DEFINE:_menutxt=_var01
; _DEFINE:_options=_var02
; _DEFINE:_menuidx=_var03

; _DEFINE:MAXMENUIDX=2
; _DEFINE:MENUITEMS=MAXMENUIDX+1

; _DEFINE:OPTION_BIT_ENABLED=0x00000001
; _DEFINE:OPTION_BIT_SMART_MODE=0x00000002
; _DEFINE:OPTION_BIT_KEY_F10=0x00000004
; _DEFINE:OPTION_BIT_KEY_RARR=0x00000008
; _DEFINE:OPTION_BIT_KEY_DARR=0x00000010
; _DEFINE:OPTION_BIT_KEY_UARR=0x00000020
; _DEFINE:OPTION_BIT_KEY_LARR=0x00000040
; _DEFINE:OPTION_BIT_ALL_KEYS=0x0000007C
; _DEFINE:OPTION_BIT_ALL_KEYS_NOT=0xFFFFFF83
; _DEFINE:OPTION_BIT_ARR_KEYS=0x00000078
; _DEFINE:OPTION_BIT_ARR_KEYS_NOT=0xFFFFFF87
; _DEFINE:OPTION_BIT_ARR_KEYS_UPDOWN=0x00000030
; _DEFINE:OPTION_BIT_SHOW_MENU=0x00000080
; _DEFINE:OPTION_BIT_SHOW_MENU_NOT=0xFFFFFF7F

entry:
	test dword ptr [_options], OPTION_BIT_KEY_F10
	jz no_enable_keypress
	xor dword ptr [_options], OPTION_BIT_ENABLED
	and dword ptr [_options], OPTION_BIT_ALL_KEYS_NOT
	or dword ptr [_options], OPTION_BIT_SHOW_MENU
no_enable_keypress:
	test dword ptr [_options], OPTION_BIT_ENABLED
	jz _exit

main:
	push edi
	push ebx
	push edx
	push ecx
	push eax
	test dword ptr [_options], OPTION_BIT_SHOW_MENU
	jnz menu
menu_ret:
	
exit:
	pop eax
	pop ecx
	pop edx
	pop ebx
	pop edi

_exit:
	sub esp, 0x1A0
	jmp 0x58EAF6

; modifies eax, edx
menu:
	; >>>>>>> menu nav
	test dword ptr [_options], OPTION_BIT_ARR_KEYS
	jz menu_show
	test dword ptr [_options], OPTION_BIT_ARR_KEYS_UPDOWN
	jz menu_rl_nav
	; >>> updown nav
	mov dl, 0x5F ; "_"
	call menu_write_mark
	test dword ptr [_options], OPTION_BIT_KEY_UARR
	jz menu_keys_down
	sub byte ptr [_menuidx], 1
	mov al, MAXMENUIDX
	jmp menu_idx_boundscheck
menu_keys_down:
	add byte ptr [_menuidx], 1
	mov al, 0
menu_idx_boundscheck:
	cmp byte ptr [_menuidx], MENUITEMS
	jb menu_update_idx
	mov byte ptr [_menuidx], al
menu_update_idx:
	mov dl, 0x3E ; ">"
	call menu_write_mark
	; <<< updown nav
menu_show_clearkeys:
	and dword ptr [_options], OPTION_BIT_ARR_KEYS_NOT
	; <<<<<<< menu nav
menu_show:
	; >>>>>>> menu text
	push 0 ; a2
	push 0 ; a1
	call CText__SetTextBackground
	;add esp, 0x8
	;;push 0
	call dummy_7194F0
	;;add esp, 0x4
	push [0x858F14] ; y ; 1.1
	push [0x866CAC] ; x ; 0.55000001
	call hud2screen
	call CText__SetTextLetterSize ; flip x/y when alignment is center
	;add esp, 0x8
	push 1
	call CText__SetTextUseProportionalValues
	;add esp, 0x4
	;;push 1
	call CText__SetFont
	;;add esp, 0x4
	;;push 1 ; 0 center 1 left 2 right
	call CText__SetTextAlignment
	;;add esp, 0x4
	;;push 1
	call CText__SetTextOutline
	;;add esp, 0x4
	push 0xFF000000 ; ABGR
	call CText__SetBorderEffectRGBA
	;add esp, 0x4
	push 0xFFFFFFFF; ABGR
	call CText__SetTextColour
	;add esp, 0x4
	push _menutxt ; str
	push 0x43600000 ; y (224.0)
	push 0x43a00000 ; x (320.0)
	call __drawText
	;add esp, 0xC
	add esp, 0x28
	; <<<<<<< menu text
	jmp menu_ret

menu_rl_nav:
	mov eax, [_menuidx]
	imul eax, 4
	add eax, __BASEADDR
	mov eax, [eax+menujmptable]
	add eax, __BASEADDR
	jmp eax
menu_rl_continue:
	xor dword ptr [_options], OPTION_BIT_SHOW_MENU
	and dword ptr [_options], OPTION_BIT_ARR_KEYS_NOT
	jmp menu_ret
menu_rl_smartmode:
	xor dword ptr [_options], OPTION_BIT_SMART_MODE
	mov eax, _menutxt
	add eax, 0xAA ; !!MENUOFFSET
	lea edx, [eax-0x3] ; !!MENUOFFSET
	test dword ptr [_options], OPTION_BIT_SMART_MODE
	jz menu_rl_smartmode@1
	mov word ptr [eax], 0x5F4E ; "_N"
	mov byte ptr [edx], 0x67 ; "g"
	jmp menu_show_clearkeys
menu_rl_smartmode@1:
	mov word ptr [eax], 0x4646 ; "FF"
	mov byte ptr [edx], 0x72 ; "r"
	jmp menu_show_clearkeys
menu_rl_viewdistance:
	jmp menu_show_clearkeys

menu_write_mark:
	mov eax, [_menuidx]
	imul eax, 0x1A ; !!MENUOFFSET
	add eax, _menutxt
	mov byte ptr [eax+0x7E], dl ; !!MENUOFFSET
	ret

;hud2screen(float x, float y) ; in place
hud2screen:
	fild dword ptr [0xC17048] ; _RwCurrentResolution_Y
	fmul dword ptr [0x859524] ; 1.0f/448.0f
	fmul dword ptr [esp +0x8] ; y
	fstp dword ptr [esp +0x8] ; y
	fild dword ptr [0xC17044] ; _RwCurrentResolution_X
	fmul dword ptr [0x859520] ; 1.0f/640.0f
	fmul dword ptr [esp +0x4] ; x
	fstp dword ptr [esp +0x4] ; x
	ret

menujmptable:
	.long menu_rl_continue
	.long menu_rl_smartmode
	.long menu_rl_viewdistance

