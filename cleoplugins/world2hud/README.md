Plugin to transform 3D world points to 2D screen points.
Find a prebuilt [world2hud.cleo](bin/world2hud.cleo) in the bin folder.

### Usage
Put this at the top of your script (along with other sannybuilder macros):
```
{$O 0C27=5,transform world_xyz %1d% %2d% %3d% to hud_xy %4d% %5d%}
{$O 0C28=5,transform world_xyz %1d% %2d% %3d% to screen_xy %4d% %5d%}
```
This lets sannybuilder know these additional opcodes exists so it will know what to do when compiling.  
Then you can call it like any other opcode:
```
0C27: transform world_xyz 1@ 2@ 3@ to hud_xy 4@ 5@
0C28: transform world_xyz 1@ 2@ 3@ to screen_xy 4@ 5@
```
What this does: it transforms a 3D world point to 2D screen point. Use `0C27` to transform to a hud (640x480) point for using with textdraws/texture positions. Use `0C28` to transform to a screen point (project to whatever resolution sa is running with) when directly accessing drawing APIs.

### Plain CLEO alternative
See [garages esp script](../../scm/garages/scr.txt) at :DOPROJECTION.

