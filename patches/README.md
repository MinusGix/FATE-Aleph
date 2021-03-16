# Patches
**Languages**: C, Assembly
This directory holds all the patch code. When built, the object files and flat binaries will be put in the parent directories `build/` folder.  
Adding a patch here does not automatically apply it. See the `./apply_patches.sh` script, near the end, for how they are applied.  
You can ignore warnings like: `ld: warning: cannot find entry symbol _start; defaulting to 0000000000748e70`.
  
Note: It might be nice to support C++ for easier writing of some code (I like templates, okay.), but that is likely more painful to implement properly.  
  
Later on, when supporting more than Fate: The Traitor Soul, it may be a good idea to make apply patches take the 'type'/'version' and only apply patches which work with that.  