# Aleph

This folder contains the main mod ''manager'' for the game. It manages the loading and running of scripts.  
Though, it should be noted that this is not what actually installs the scripts/patches! This is purely the modding library and has functions that would be called by the patches.  
  
Currently the way it is setup is that you should the exported `init` function early on. Currently the patches do this in a patched functin called during `__cinit`, but it could probably be later.  
A goal for Aleph is to try to limit what specific Fate designs it has, though that isn't too important. A more important goal is to try not to limit itself to just Fate: The Traitor Soul. This can be done by registering the memory addresses of important data for access.