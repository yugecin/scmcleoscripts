This is a mod for a mod named "3DBlipsSA". That mod, which is NOT made by me but
by someone named "Xinerki", renders all radar blips on the HUD at their 3D world
positions (together with a distance measurement text).
https://gtaforums.com/topic/867079-3d-blips/

Someone came to me and asked if I could make it so that the property icons would
be excluded (green house/red house blips), because they can be omnipresent in
some SA:MP servers etc.

This mod "ZZ3DBlipsSaRemoveHouseIcons" does that by hooking into the loaded mod
dll and adds a hook to do an additional check of the blip type before rendering
it. The name is prefixed by a few Z's, to make sure this gets loaded after the
original mod was loaded (I was guessing that would work, and it seems like it
does).

So this mod is an additional "ZZ3DBlipsSaRemoveHouseIcons.asi" file that you
also need to paste into your GTA:SA game dir. If the "3DBlipsSA.asi" file is
not in your game dir, this mod won't do anything. Also note that this mod won't
work if the original mod is named anything different than "3DBlipsSA.asi".
Simply delete the file from your game directory to "uninstall".

I've also put the original 3DBlipsSA.asi mod in here (or at least, the version
that that person gave me) since apparently the original download link does not
resolve.
