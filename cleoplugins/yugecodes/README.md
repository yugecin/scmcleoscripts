Plugin that combines all my opcodes from my separate plugins, with some extra's that are not in a separate plugin.
Find a prebuilt [yugecodes.cleo](bin/yugecodes.cleo) in the bin folder.

### List of opcodes
sannybuilder macros:
```
{$O 0C27=5,transform world_xyz %1d% %2d% %3d% to hud_xy %4d% %5d%}
{$O 0C28=5,transform world_xyz %1d% %2d% %3d% to screen_xy %4d% %5d%}
```
opcodelist:
```
0C27: transform world_xyz 1@ 2@ 3@ to hud_xy 4@ 5@
0C28: transform world_xyz 1@ 2@ 3@ to screen_xy 4@ 5@
```

### Containing plugins
* [signext](../signext)
* [world2hud](../world2hud)

