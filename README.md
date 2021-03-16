# Fate Modding

This setup is for modding Fate. Each folder has its own README.md, which should provide more information. Maybe.  
  
Currently this is only attempting to work on the latest Steam version of Fate: The Traitor Soul. Theoretically, getting it working on others should not be overly challenging, since I imagine most of the things that are messed with still exist but are just in different positions. Applying the patches to a Fate that is not the tested here is likely to not even launch without modifications, tohugh.  
I'll note that this project has been deliberately avoiding looking at any other Fate Modding. If there is any that does more than modifying the game's text files.  
  
## Compilation
The reason this project uses `sh` files for much of the scripting is that it is developed on Linux, though Fate does not natively support the operating system (which isn't surprising). It would be nice to make `bat` files for Windows that work properly, but getting those setup would take some time. An alternative scripting language (like lua, maybe) would also work.  
Currently this uses i686-w64-mingw32-gcc for building to a windows target. It was originally using clang but that tha
Switching to Meson (or some other build system, but I like using Meson for C/C++) would potentially make that nicer, but ensuring that the compilation flags work properly across compilers will be unfortunate.  

`./test_apply.sh` contains some build instructions, but patcher should be built before that is ran for the first time.

## Reversing
To figure out the code of the game, Ghidra was used. It has some issues.  
 - Analyzing took a *long* time. Eight hours on one step. If you decide to analyze the game, it might be a good idea to turn off WindowsResourceReference analysis step. Then it would probably only take about 30 minutes, on my computer.  
 - C++ can be more challenging to reverse than C.  
 - Some of the functions (like one which changes the string to upper case) take `std::string` as a value, but this causes Ghidra to choke. It produces very strange stack accesses. I imagine it might be some weird C++ calling conv for these values, and haven't spent an hour or two analyzing the assembly closely to find what it is actually trying, but it makes all the code in that function decompile badly.  

The Ghidra project isn't in this repository since I'm uncertain if it includes the executable (which I obviously can't release). I'll likely eventually figure out the best way to upload it. (I now wonder how Version Tracking would behave if you gave it a bunch of different Fate games)  

## Sections
### Aleph
This is the 'mod manager'. It provides the scripting capabilities. This does not patch anything by itself, but does provide functions for patches to use.  
### Patcher
This applies patches to the executable, though it does not manage them itself. If using this, make sure to make a backup. The script does not try to keep the original code.  
### Patches
This is a folder with all the patches. See the `apply_patches.sh` script for what ones it enables.  
Note: Removing a patch from the list after it has already been applied.  
### Load Locale
This was an early testing script. It loads the string resources from the dlls in the `LANG` folder and outputs them as JSON. May not support unicode. The ids are what would be passed to `loadLocaleString`.  