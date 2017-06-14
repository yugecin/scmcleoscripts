Plugin that combines all my opcodes from my separate plugins, with some extra's that are not in a separate plugin.
Find a prebuilt [yugecodes.cleo](bin/yugecodes.cleo) in the bin folder.

### List of opcodes
sannybuilder macros:
```
{$O 0C26=2,sign_extend %1d% store_to %2d%}
{$O 0C27=5,transform world_xyz %1d% %2d% %3d% to hud_xy %4d% %5d%}
{$O 0C28=5,transform world_xyz %1d% %2d% %3d% to screen_xy %4d% %5d%}
{$O 0C29=4,lerp_ab %1d% %2d% f %3d% store_to %4d%}
{$O 0C30=3,draw_text %1d% at %2d% %3d%}
```
opcodelist:
```
0C26: sign_extend 1@ store_to 2@
0C27: transform world_xyz 1@ 2@ 3@ to hud_xy 4@ 5@
0C28: transform world_xyz 1@ 2@ 3@ to screen_xy 4@ 5@
0C29: lerp_ab 1@ 2@ f 3@ store_to 4@
0C30: draw_text 1@ at 2@ 3@
```

### Containing plugins
* [signext](../signext)
* [world2hud](../world2hud)

### Extra opcodes
* 0C29: lerp
* 0C30: draw text like in textdraws, but with a literal string instead of GXT entry (outline does not seem to work)

