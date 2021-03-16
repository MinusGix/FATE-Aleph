// b53a0 b546f
// This file does some unknown construction of data and parsing
// And we try to make it somewhat more efficient, but most of the changes are in the actual parsing 
// code.

#include "general.h"
#include "general_func.h"
#include "string.h"
#include "file.h"

PATCH_FUNC
SEH_FRAME_HANDLER(0x00671961)
CLASS_METHOD
Unk48A* unk48_constructor(Unk48A* self, string* filename) {
    // this function originally heap allocated the file, but it always freed it at the end
    // so, that was removed and it is just created on the stack.

    File file = {0};
    self->file = file_constructor_v(&file);

    h_string_clear(&self->filename);
    string_insert(&self->filename, filename, 0, 0xffffffff);
    h_vector_clear((GenericVector*)&self->vec);

    bool status = file_open_v(self->file, filename);
    if (status != false) {
        unk48a_unk_parsing_v(self);
        file_close_v(self->file);
    }

    self->file = NULL;

    return self;
}