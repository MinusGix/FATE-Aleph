#ifndef SEEN_GENERAL_FILE_H
#define SEEN_GENERAL_FILE_H

#include "general.h"

INLINE bool is_file_eof(FILE* file) {
    return (file->_flag & _IOEOF) != 0;
}

typedef uint32_t (* __cdecl fread_t)(void* dest, uint32_t size, uint32_t count, FILE* file);
static fread_t fread_v = FUNC_PTR_CAST(fread_t, 0x005de799);

typedef uint32_t (* __cdecl fseek_t)(FILE*, uint32_t offset, uint32_t whence);
static fseek_t fseek_v = FUNC_PTR_CAST(fseek_t, 0x005de874);

typedef uint32_t (* __cdecl ftell_t)(FILE*);
static ftell_t ftell_v = FUNC_PTR_CAST(ftell_t, 0x005dea1f);

typedef uint32_t (* __cdecl fgetpos_t)(FILE*, fpos_t* pos);
static fgetpos_t fgetpos_v = FUNC_PTR_CAST(fgetpos_t, 0x005df0a8);

typedef FILE* (* __cdecl fopen_t)(const char* filename, const char* mode);
static fopen_t fopen_v = FUNC_PTR_CAST(fopen_t, 0x005de591);

// File / gemma
typedef File* (* __thiscall file_constructor_t)(File* self);
static file_constructor_t file_constructor_v = FUNC_PTR_CAST(file_constructor_t, 0x004bd3e0);

typedef bool (* __thiscall file_open_t)(File* self, string* path);
static file_open_t file_open_v = FUNC_PTR_CAST(file_open_t, 0x004bd410);

typedef string* (* __thiscall file_readline_t)(File* self, string* output);
static file_readline_t file_readline_v = FUNC_PTR_CAST(file_readline_t, 0x004bd2a0);

typedef void (* CLASS_METHOD file_parse_t)(File* self, StringPtrDeque* lines, char* split_on, char comment_marker);
static file_parse_t file_parse_v = FUNC_PTR_CAST(file_parse_t, 0x004bd690);

typedef void (* __thiscall file_close_t)(File* self);
static file_close_t file_close_v = FUNC_PTR_CAST(file_close_t, 0x004bd110);

typedef void (* __thiscall file_destructor_t)(File* self);
static file_destructor_t file_destructor_v = FUNC_PTR_CAST(file_destructor_t, 0x004bd260);

#endif