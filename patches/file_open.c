#include "general.h"
#include "general_func.h"
#include "string.h"
#include "strings.h"
#include "file.h"

PATCH_FUNC
SEH_FRAME_HANDLER(0x0067a168)
CLASS_METHOD
bool file_open(File* self, string* path) {
    const char* path_str = h_string_data(path);

    self->file = fopen_v(path_str, S_RB);
    if (self->file == NULL) {
        return false;
    }

    // Originally this copied the path to a temp string then to self->path
    // but we don't need to bother
    string_insert(&self->path, path, 0, 0xffffffff);
    self->eof = false;
    return true;
}