Pressing F10+F9 toggles the speed limit of planes.


Based on this post by OP9080
--------------------------------------------------------------------------------
https://gtaforums.com/topic/222739-remove-the-hardwired-speed-limit-on-the-hydra

Address 0x86E104 - float constant, square of the maximum speed of the Hydra
(actually, all planes)

Unit: 2500 meters^2/sec^2

Value: 2.25 (gives a maximum speed of 75 m/s)

Code that checks the limit:

006DADDD: D8 1D 04 E1 86 00  fcomp  dword ptr ds:[0086E104h]
006DADE3: DF E0              fnstsw      ax
006DADE5: F6 C4 41           test        ah,41h
006DADE8: 75 60              jne         006DAE4A

How to remove:

Change byte at 0x6DADE8 from 0x75 to 0xEB to change it to an unconditional jmp
and ignore the test.

If you have GTA hoodlum, you can patch it with a hex editor at file address
0x2DA1E8.

These numbers hold for both US & EU exes.

The Hydra's speed is also limited by the drag physics so if you want to make
it go faster, reduce the default drag factor of 20 in handling.cfg.
I used a drag of 2, and it maxed out spookie's speedometer at 999 KPH in
about 10 seconds. 
