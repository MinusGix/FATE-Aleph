// Working: TSS
// This function normally initializes some setting information. This is called early on by __cinit
// It has been patched to shorten it and insert the Aleph intialization code.
#include <stdint.h>
#include "general.h"
#include "general_func.h"
#include "string.h"
#include "strings.h"

#define ALEPH_NO_FUNC
#include "../aleph/aleph.hpp"

#define NEARCLIP_SETTING ((SettingEntry*)0x00df4650)
#define FARCLIP_SETTING  ((SettingEntry*)0x00df4674)
#define FOV_SETTING      ((SettingEntry*)0x00df4698)
#define VERSION_SETTING  ((SettingEntry*)0x00df46bc)


PATCH_FUNC
SEH_FRAME_HANDLER(0x005eec6e)
void init_setting_info1(void) {
    // === ORIGINAL CODE === (roughly)

    h_string_clear(&NEARCLIP_SETTING->name);
    h_string_clear(&FARCLIP_SETTING->name);
    h_string_clear(&FOV_SETTING->name);
    h_string_clear(&VERSION_SETTING->name);

    NEARCLIP_SETTING->id = 0;
    NEARCLIP_SETTING->value = 0x41200000; // 10
    string_append(&NEARCLIP_SETTING->name, S_NEARCLIP, S_NEARCLIP_LEN);

    FARCLIP_SETTING->id = 0;
    FARCLIP_SETTING->value = 0x43800000; // 256
    string_append(&FARCLIP_SETTING->name, S_FARCLIP, S_FARCLIP_LEN);

    FOV_SETTING->id = 0;
    FOV_SETTING->value = 0x42340000; // 45
    string_append(&FOV_SETTING->name, S_FOV, S_FOV_LEN);

    VERSION_SETTING->id = 0;
    VERSION_SETTING->value = 0; // Dunno why its 0.
    string_append(&VERSION_SETTING->name, S_VERSION, S_VERSION_LEN);

    // === END ORIGINAL CODE ===

    // This code fails hard rather than letting the process continue.
    // While efforts could be made to make the game launch safely when it fails
    // to start aleph, it would mean complicating the patches to check for the
    // existence of Aleph.
    // But, one thing that would be better here is to use MessageBox
    // and provide a message.

    HMODULE mod = LoadLibraryA_v("aleph.dll");
    if (mod == NULL) {
        // Failed to get the dll..
        ExitProcess_v(1);
    }
    init_t init = (init_t)GetProcAddress_v(mod, "init");
    if (init == NULL) {
        // Failed to get function
        ExitProcess_v(2);
    }
    InitStatus status = init(mod);
    if (status < INIT_SUCCESS) {
        // Failed to initialize (failure)
        ExitProcess_v(3);
    }

    // Normally this setups an atexit to deallocate the strings, but i don't really care.
    // The OS can manage that. (Address: 0x00b37f10)
    
    return;
}