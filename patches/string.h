#ifndef SEEN_STRING_FUNC_H
#define SEEN_STRING_FUNC_H

#include "general.h"
#include "general_func.h"


typedef string* (* __thiscall string_append_t)(string*, const char*, uint32_t);
static string_append_t string_append = FUNC_PTR_CAST(string_append_t, 0x00401470);
typedef string* (* __thiscall string_insert_t)(string*, string*, uint32_t, uint32_t);
static string_insert_t string_insert = FUNC_PTR_CAST(string_insert_t, 0x00401380);
typedef string* (* __thiscall string_append_copies_of_single_t)(string*, uint32_t count, char chr);
static string_append_copies_of_single_t string_append_copies_of_single = FUNC_PTR_CAST(string_append_copies_of_single_t, 0x0041fe30);
typedef uint32_t (* __thiscall string_find_t)(string*, char* needle, uint32_t position, uint32_t count);
static string_find_t string_find = FUNC_PTR_CAST(string_find_t, 0x00403770);
typedef string* (* __thiscall string_erase_t)(string*, uint32_t index, uint32_t count);
static string_erase_t string_erase = FUNC_PTR_CAST(string_erase_t, 0x004010a0);
typedef uint32_t (* __thiscall string_find_first_of_t)(string*, char*, uint32_t, uint32_t);
static string_find_first_of_t string_find_first_of = FUNC_PTR_CAST(string_find_first_of_t, 0x004bd1e0);
typedef uint32_t (* __thiscall string_find_first_of1_t)(string*, char*, uint32_t, uint32_t);
static string_find_first_of1_t string_find_first_of1 = FUNC_PTR_CAST(string_find_first_of1_t, 0x004bd150);
typedef string* (* __thiscall string_copy_into_t)(string* self, string* into, uint32_t index, uint32_t count);
static string_copy_into_t string_copy_into = FUNC_PTR_CAST(string_copy_into_t, 0x00407f10);
typedef void (* CLASS_METHOD string_expand_t)(string* self, uint32_t new_size, uint32_t current_length);
static string_expand_t string_expand_v = FUNC_PTR_CAST(string_expand_t, 0x00401120);

// Helper to clear a string. Does not deallocate.
INLINE static void h_string_clear(string* str) {
    str->data.buffer[0] = '\0';
    str->length = 0;
    str->capacity = STRING_SSO_CAP;
}
// Helper to deallocate string. Does not clear it
// TODO: It would be nice if this didn't depend on this free, but rather any free
// but I'm unsure of a good way to do that..
INLINE static void h_string_free(string* str) {
    if (str->capacity > STRING_SSO_CAP) {
        // TODO: Is this correct? Arrays always mess with my head. This is supposed to take first
        // four bytes as a pointer
        free_v(str->data.ptr);
    }
}

INLINE static char* h_string_data(string* str) {
    if (str->capacity <= STRING_SSO_CAP) {
        return str->data.buffer;
    } else {
        return str->data.ptr;
    }
}

/// Empties a string. Sets its length to 0 and null terminates buffer.
/// Meant to be used when you want to keep the capacity and already allocated ptr
INLINE static void h_string_empty(string* str) {
    str->length = 0;
    h_string_data(str)[0] = '\0';
}

#endif