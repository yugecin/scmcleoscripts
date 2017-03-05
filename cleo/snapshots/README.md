ESP for snapshots, usefull for routing all snapshots speedruns  

[Demo video](https://youtu.be/F3fbW10hvOk)
  
Usefull stuff:
* use the NotForPublicRoads (Hotring A) cheat to spawn a NRG-500
* you can't fall of your bike (unless you drive in water)
* pickups will be shown if you don't look trough the camera (and when you're within 100 units)
* Usefull data at the bottom left of the screen: viewdistance/max snapshotdistance/#snapshots taken/total # of snapshots
  
ESP is red when snapshot is too far, green when it is possible to get them.  
The calculation behind that is.. not a calculation and not very accurate, but it comes close.  
  
It doesn't check if you zoomed in far enough to get the shot, I'll add that later when I find out how to do that.  
  
~~The signext.cleo plugin is needed for sign extending the XYZ positions of pickups, because they are saved as 2byte values. Let me know if you find a way to make it work in pure cleo, so the plugin wouldn't be needed anymore.~~
Finally found how to do it properly (I kept forgetting one step), the [snapshots.cs](snapshots.cs) script doesn't need the plugin anymore.
I'm keeping the last version that used the plugin as [snapshots-withplugin.cs](snapshots-withplugin.cs), if you want to use that one, make sure to also put the [signext.cleo](../../cleoplugins/signext/bin/signext.cleo) plugin in your CLEO folder.

