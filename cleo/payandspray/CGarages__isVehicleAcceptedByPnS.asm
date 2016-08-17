.text:004479A0     ; =============== S U B R O U T I N E =======================================
.text:004479A0
.text:004479A0
.text:004479A0     CGarages__isVehicleAcceptedByPnS proc near
.text:004479A0                                             ; CODE XREF: CGarage__?vehicleEntered+225p
.text:004479A0
.text:004479A0     arg_0           = dword ptr  8
.text:004479A0
.text:004479A0 000                 push    esi
.text:004479A1 004                 mov     esi, [esp+arg_0]
.text:004479A5 004                 mov     ecx, esi
.text:004479A7 004                 call    CVehicle__IsLawEnforcementVehicle
.text:004479AC 004                 test    al, al
.text:004479AE 004                 jnz     short loc_4479E2
.text:004479B0 004                 cmp     dword ptr [esi+594h], 0Ah
.text:004479B7 004                 jz      short loc_4479E2
.text:004479B9 004                 movsx   eax, word ptr [esi+22h]
.text:004479BD 004                 cmp     eax, 431        ; bus
.text:004479C2 004                 ja      short loc_4479D2
.text:004479C4 004                 jz      short loc_4479E2
.text:004479C6 004                 sub     eax, 407        ; firetruk
.text:004479CB 004                 jz      short loc_4479E2
.text:004479CD 004                 sub     eax, 9          ; ambulan
.text:004479D0 004                 jmp     short loc_4479DC
.text:004479D2     ; ---------------------------------------------------------------------------
.text:004479D2
.text:004479D2     loc_4479D2:                             ; CODE XREF: CGarages__isVehicleAcceptedByPnS+22j
.text:004479D2 004                 cmp     eax, 437        ; coach
.text:004479D7 004                 jz      short loc_4479E2
.text:004479D9 004                 cmp     eax, -2         ; artict1
.text:004479DC
.text:004479DC     loc_4479DC:                             ; CODE XREF: CGarages__isVehicleAcceptedByPnS+30j
.text:004479DC 004                 jz      short loc_4479E2
.text:004479DE 004                 mov     al, 1
.text:004479E0 004                 pop     esi
.text:004479E1 000                 retn
.text:004479E2     ; ---------------------------------------------------------------------------
.text:004479E2
.text:004479E2     loc_4479E2:                             ; CODE XREF: CGarages__isVehicleAcceptedByPnS+Ej
.text:004479E2                                             ; CGarages__isVehicleAcceptedByPnS+17j
.text:004479E2                                             ; CGarages__isVehicleAcceptedByPnS+24j
.text:004479E2                                             ; CGarages__isVehicleAcceptedByPnS+2Bj ...
.text:004479E2 004                 xor     al, al
.text:004479E4 004                 pop     esi
.text:004479E5 000                 retn
.text:004479E5     CGarages__isVehicleAcceptedByPnS endp