Plugin to perform easy sign extension in cleo scripts.  
Find a prebuilt [signext.cleo](bin/signext.cleo) in the bin folder.

### Usage
Put this at the top of your script (along with other sannybuilder macros):
```
{$O 0C26=2,sign_extend %1d% store_to %2d%}
```
This lets sannybuilder know an additional opcode 0C26 exists so it will know what to do when compiling.  
Then you can call it like any other opcode:
```
0C26: sign_extend 1@ store_to 2@
```

### Usecase
This was used in the [snapshots](../../cleo/snapshots) esp CLEO script as (snapshot) pickup XYZ locations are saved in memory as 2 byte coordinates, and we need to work with 4 byte values in the script.  
After a while I did find a way to do this in plain CLEO, which means this plugins isn't used for that anymore.  
This can be still usefull if you don't mind the dependency on this plugin so you don't have to bother with sign extension in your CLEO code (or if you simply don't have any spare local variables :p).

### Plain CLEO alternative
Eventually I found out how to do it without plugins (I kept forgetting about the 2-complement thing when I first searched for it).
```
// 1@ is input (and output)
// 2@ is a temp variable
:SIGNEXT
0006: 2@ = 0
08B7:   test 1@ bit 15
004D: jump_if_false @SIGNEXT2
0006: 2@ = 15
:SIGNEXT0
000A: 2@ += 1
08BF: set 1@ bit 2@
0019:   2@ > 31
004D: jump_if_false @SIGNEXT0
0012: 1@ *= -1
:SIGNEXT2
0093: 1@ = integer 1@ to_float
0039:   2@ == 32
004D: jump_if_false @SIGNEXT3
0013: 1@ *= -1.0
:SIGNEXT3
return
```
