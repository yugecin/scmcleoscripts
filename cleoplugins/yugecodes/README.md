Plugin that combines all my opcodes from my separate plugins, with some extra's that are not in a separate plugin.
Find a prebuilt [yugecodes.cleo](bin/yugecodes.cleo) in the bin folder.

### List of opcodes
sannybuilder macros:
```
{$O 0C26=2,sign_extend %1d% store_to %2d%}
{$O 0C27=5,transform world_xyz %1d% %2d% %3d% to hud_xy %4d% %5d%}
{$O 0C28=5,transform world_xyz %1d% %2d% %3d% to screen_xy %4d% %5d%}
{$O 0C29=4,lerp_ab %1d% %2d% f %3d% store_to %4d%}
{$O 0C30=12,draw_text %1d% at_screen_xy %2d% %3d% font %4d% proportional %5d% align %6d% RGBA %7d% %8d% %9d% %10d% letter_size %11d% %12d%}
{$O 0C31=12,draw_text %1d% at_hud_xy %2d% %3d% font %4d% proportional %5d% align %6d% RGBA %7d% %8d% %9d% %10d% letter_size %11d% %12d%}
{$O 0C32=5,condition_int %1d% EQ %2d% if_true %3d% if_false %4d% store_to %5d%}
{$O 0C33=5,condition_float %1d% EQ %2d% if_true %3d% if_false %4d% store_to %5d%}
{$O 0C34=5,condition_int %1d% GT %2d% if_true %3d% if_false %4d% store_to %5d%}
{$O 0C35=5,condition_float %1d% GT %2d% if_true %3d% if_false %4d% store_to %5d%}
```
opcodelist:
```
0C26: sign_extend 1@ store_to 2@
0C27: transform world_xyz 1@ 2@ 3@ to hud_xy 4@ 5@
0C28: transform world_xyz 1@ 2@ 3@ to screen_xy 4@ 5@
0C29: lerp_ab 1@ 2@ f 3@ store_to 4@
0C30: draw_text 1@ at_screen_xy 2@ 3@ font 4@ proportional 5@ align 6@ RGBA 7@ 8@ 9@ 10@ letter_size 11@ 12@
0C31: draw_text 1@ at_hud_xy 2@ 3@ font 4@ proportional 5@ align 6@ RGBA 7@ 8@ 9@ 10@ letter_size 11@ 12@
0C32: condition_int 1@ EQ 2@ if_true @TRUE if_false @FALSE store_to 3@
0C33: condition_float 1@ EQ 2@ if_true @TRUE if_false @FALSE store_to 3@
0C34: condition_int 1@ GT 2@ if_true @TRUE if_false @FALSE store_to 3@
0C35: condition_float 1@ GT 2@ if_true @TRUE if_false @FALSE store_to 3@
```

### Containing plugins
* [signext](../signext)
* [world2hud](../world2hud)

### Extra opcodes
* `0C29`: lerp
* `0C30`: draw text like in textdraws, but with a literal string instead of GXT entry (outline does not seem to work) (unstable)
* `0C31`: same as `0C30` but with HUD coordinates (640x480 canvas) (unstable)
* `0C32-0C35`: conditionals, usage:
```
0C32: condition_int 1@ EQ 0 if_true @TRUE if_false @FALSE store_to 2@
0002: jump 2@
:TRUE
// its true
0002: jump @WHEREVER
:FALSE
// its false
0002: jump @WHEREVER
```

