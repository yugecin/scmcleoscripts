Plugin that combines all my opcodes from my separate plugins, with some extra's that are not in a separate plugin.
Find a prebuilt [yugecodes.cleo](bin/yugecodes.cleo) in the bin folder.

### List of opcodes
sannybuilder macros:
```
{$O 0C26=2,sign_extend %1d% store_to %2d%}
{$O 0C27=5,transform world_xyz %1d% %2d% %3d% to hud_xy %4d% %5d%}
{$O 0C28=5,transform world_xyz %1d% %2d% %3d% to screen_xy %4d% %5d%}
{$O 0C29=4,lerp_ab %1d% %2d% f %3d% store_to %4d%}
{$O 0C30=11,draw_text %1d% at_screen_xy %2d% %3d% font %4d% align %5d% RGBA %6d% %7d% %8d% %9d% letter_size %10d% %11d%}
{$O 0C31=11,draw_text %1d% at_hud_xy %2d% %3d% font %4d% align %5d% RGBA %6d% %7d% %8d% %9d% letter_size %10d% %11d%}

```
opcodelist:
```
0C26: sign_extend 1@ store_to 2@
0C27: transform world_xyz 1@ 2@ 3@ to hud_xy 4@ 5@
0C28: transform world_xyz 1@ 2@ 3@ to screen_xy 4@ 5@
0C29: lerp_ab 1@ 2@ f 3@ store_to 4@
0C30: draw_text 1@ at_screen_xy 2@ 3@ font 4@ align 5@ RGBA 6@ 7@ 8@ 9@ letter_size 10@ 11@
0C31: draw_text 1@ at_hud_xy 2@ 3@ font 4@ align 5@ RGBA 6@ 7@ 8@ 9@ letter_size 10@ 11@
```

### Containing plugins
* [signext](../signext)
* [world2hud](../world2hud)

### Extra opcodes
* `0C29`: lerp
* `0C30`: draw text like in textdraws, but with a literal string instead of GXT entry (outline does not seem to work)
* `0C31`: same as `0C30` but with HUD coordinates (640x480 canvas)

