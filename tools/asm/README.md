
# asmtool

tool to help with putting asm in cleo scripts

Example usage
-------------

Let's say you want to hook on this call
```
.text:005869BF     call    _?paintMapZones
```
so you put 005869C0 in the bottom right small box and tick 'jump'

Then you come up with this genius code:
```
call 0x586650 ; _?paintMapZones 0x586650 ; make the call that got rewritten

; do something
push 0
call 0x56E210 ; CPed *__cdecl getPlayerPed(int number)
mov [_var01], eax ; save the ped to some var
add esp, 0x4
; more code and awesome stuff

jmp 0x5869C4 ; back to business, continue right after the hooked call
```

Press the 'Do it all' button (after you made sure the gcc & objdump paths are correct, duh) and magic code appears:

```
:HOOKER
0AC6: 0@ = label @ENTRY offset

0085: 1@ = 0@ // (int)
000E: 1@ -= 0x005869c4
0A8C: write_memory 0x005869bf size 1 value 0xE9 vp 0
0A8C: write_memory 0x005869C0 size 4 value 1@ vp 0

0AC6: 1@ = label @ENTRY offset

000A: 1@ += 1
0A8D: 2@ = read_memory 1@ size 4 vp 0
0062: 2@ -= 0@  // (int)
0A8C: write_memory 1@ size 4 value 2@ vp 0
000A: 1@ += 7
0A8D: 2@ = read_memory 1@ size 4 vp 0
0062: 2@ -= 0@  // (int)
0A8C: write_memory 1@ size 4 value 2@ vp 0
000A: 1@ += 5
0AC6: 3@ = label @DATA01 offset
0A8C: write_memory 1@ size 4 value 3@ vp 0
000A: 1@ += 8
0A8D: 2@ = read_memory 1@ size 4 vp 0
0062: 2@ -= 0@  // (int)
0A8C: write_memory 1@ size 4 value 2@ vp 0

0002: jump @NOMOREHOOKER


:ENTRY
hex
e8
4b 66 58 00 
6a 00 
e8
04 e2 56 00 
a3 
00 00 00 00 // DATA01
83 c4 04 
e9
ab 69 58 00 
90 
90 
90 
end
```

So put this somewhere and jump to `@HOOKER` to hook the stuff and it will return to `:NOMOREHOOKER` when it's done hooking da hook.
Also reserve some bytes for the `_var01`:

```
:DATA01
hex
00 00 00 00
end
```

this was used for [gps](../../cleo/gps) and stuff
