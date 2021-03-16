#include <stdint.h>
#include "general.h"
#include "string.h"
#define BUFFER_MAX 500

// This version is smaller, especially since it does away with a temp string variable that the
// original had.
PATCH_FUNC
SEH_FRAME_HANDLER(0x0067541b)
string* __cdecl loadLocaleString (string* output, uint32_t uid)  {
    char buffer[BUFFER_MAX];
    h_string_clear(output);

    LoadStringA_v((*getLocaleModule_v)(), uid, buffer, BUFFER_MAX);

    // Get to the end of the buffer
    char* current = buffer;
    while (*current != '\0') {
        current++;
    }

    const uint32_t length = ((uint32_t)current) - ((uint32_t)buffer);
    // const int length = strlen(buffer);
    string_append(output, buffer, length);

    return output;
}