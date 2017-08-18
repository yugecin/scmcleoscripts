
# plpanel

mod that changes sa-mp textdraws, specifically for [the pilot's life server](http://thepilotslife.com/).

Contains patches and has 3 themes with new features.

### Installation
You need the [cleo 4](http://cleo.li) library. Put `plpanel.cs` and one of the `.cleo` files from the `Releases` folder in your CLEO folder.

Features
* Fixes fuel/health bars showing while on foot
* Fixes heading bar having values like `-1 -0 [0] 1 2` or `358 359 [360] 361 362`
* Changes 'Damage' to 'Health'
* Per-frame instant updates for: heading bar, mission distance left, altitude, airspeed/car speed, vehicle health (both percentage and bar). This means (server) lag won't affect the update rate of the panel for these values!
* Blinking fuel bar when fuel is 20% or less
* Blinking health bar when health is 35% or less

Standard theme
----------------
The normal bar as you probably know it, but with the patches.
![standard](https://user-images.githubusercontent.com/12662260/29479931-374aebbe-8475-11e7-9cf2-3c5b434d94f4.png)

Classic theme
--------------
Get that sweet 2011 feeling with this remake of the old panel! Extra features for this theme:
* Passenger satisfaction included in panel instead of a separate textdraw
* GPS position above radar
* Blinking fuel/health/odo indicator when critical level almost reached
![classic](https://user-images.githubusercontent.com/12662260/29479911-24072ae0-8475-11e7-8d50-d816f0a36e38.png)

Robin's theme
---------------
Totally new panel 'design'. Extra features for this theme:
* GPS position above radar
* 'Native' progressbars for almost all values
* Fuel price next to the fuel bar
* Passenger satisfaction has its own bar
* Blinkings fuel/health/odo bars when critical level almost reached
* Classic themed status bar
![robin](https://user-images.githubusercontent.com/12662260/29479937-3b764f26-8475-11e7-947f-cc126c5f81f9.png)



### Credits
This mod uses code from the [Plugin-SDK](https://github.com/DK22Pac/plugin-sdk) and [mod_sa](https://github.com/BlastHackNet/mod_s0beit_sa/). These portions are annotated in the source.
