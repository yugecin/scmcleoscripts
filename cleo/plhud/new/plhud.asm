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

; _DEFINE:_options=_var02

; _DEFINE:OPTION_BIT_ENABLED=0x00000001
; _DEFINE:OPTION_BIT_SMART_MODE=0x00000002
; _DEFINE:OPTION_BIT_KEY_F10=0x00000004
; _DEFINE:OPTION_BIT_KEY_RARR=0x00000008
; _DEFINE:OPTION_BIT_KEY_DARR=0x00000010
; _DEFINE:OPTION_BIT_KEY_UARR=0x00000020
; _DEFINE:OPTION_BIT_KEY_LARR=0x00000040
; _DEFINE:OPTION_BIT_ALL_KEYS=0x0000007C
; _DEFINE:OPTION_BIT_ALL_KEYS_NOT=0xFFFFFF83

entry:
	test dword ptr [_options], OPTION_BIT_KEY_F10
	jz no_enable_keypress
	
	xor dword ptr [_options], OPTION_BIT_ENABLED
	and dword ptr [_options], OPTION_BIT_ALL_KEYS_NOT

no_enable_keypress:
	test dword ptr [_options], OPTION_BIT_ENABLED
	jz _exit
	
main:
	push edi
	push ebx
	push edx
	push ecx
	push eax
	
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
	push _var01 ; str
	push 0x43600000 ; y (224.0)
	push 0x43a00000 ; x (320.0)
	call __drawText
	;add esp, 0xC
	add esp, 0x28
	; <<<<<<< menu text
	
	jmp exit
	
exit:
	pop eax
	pop ecx
	pop edx
	pop ebx
	pop edi
	
_exit:
	sub esp, 0x1A0
	jmp 0x58EAF6

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