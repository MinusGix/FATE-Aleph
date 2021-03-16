# Patcher
**Language**: C++
Uses clang, but it should work just fine with gcc or even msvc.


This applies patches to the program, with some safety measures.  
Usage: `./patch start_addr end_addr code_patch.bin dest_execuable`  
Note: `start_addr` and `end_addr` are in hexadecimal by default.  
While we only need the start address to know where to patch, knowing the end address lets us require the patch to fit within that. If we did not require that then we could easily break the executable by overwriting adjacent functions.

It might be a nice idea to switch to an already developed patcher that at least has the features that this one has, because those are likely more optimized for performance, and may have extra features which are nice (like encoding start addr and end addr in the patch).