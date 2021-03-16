// bd2a0 bd36f
// Working: TSS
// This function reads some info out of the file.
// It is used often, but the original was terrifyingly inefficient.

#include "general.h"
#include "string.h"
#include "../aleph/aleph.hpp"

// TODO: Overwrite this functions exception handler!
PATCH_FUNC
SEH_FRAME_HANDLER(0x0067a168)
CLASS_METHOD string* file_readline_patch(File* self, string* output) {
    // Constraints:
    // - If file is eof then we set eof.
    //   - in initial check
    //   - reading
    // - If it is a null byte or newline then it is not added, but it is consumed.
    // - Output does not have to keep its pointer.
    // - Output must be cleared.

    // It was challenging to fit the code in this, so we just have it s a function ptr.

    return aleph->file_readline(self, output);
}