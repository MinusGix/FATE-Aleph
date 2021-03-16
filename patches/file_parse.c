// bd690 bd88f
// This seems to do some basic parsing of the file.
// Likely collecting lines and splitting (?) on split_on, ignoring comments.
// There have been some modifications to the code that should make it more performant, but likely
// not significantly.

#include "general.h"
#include "../aleph/aleph.hpp"

PATCH_FUNC
SEH_FRAME_HANDLER(0x0067a198)
CLASS_METHOD
void file_parse(File* self, StringPtrDeque* lines, char* split_on, char comment_marker) {
    aleph->file_parse(self, lines, split_on, comment_marker);
}