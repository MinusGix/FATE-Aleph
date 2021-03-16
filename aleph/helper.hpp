#ifndef SEEN_ALEPH_HELPER_HPP
#define SEEN_ALEPH_HELPER_HPP


#ifdef __cplusplus
extern "C" {
#endif
    #include "../patches/general.h"
    #include "../patches/string.h"
#ifdef __cplusplus
};
#endif

#define PRINTF_FUNC __attribute__((format (printf, 1, 2)))

typedef void (* __cdecl print_func)(const char* text, ...);
typedef void (* __cdecl log_files_t)(void);

#ifndef ALEPH_NO_FUNC
EXTERNAL PRINTF_FUNC void __cdecl aleph_info(const char* text, ...);
EXTERNAL PRINTF_FUNC void __cdecl aleph_warn(const char* text, ...);
EXTERNAL PRINTF_FUNC void __cdecl aleph_error(const char* text, ...);

EXTERNAL CLASS_METHOD string* file_readline(File* self, string* output);
EXTERNAL CLASS_METHOD void file_parse(File* self, StringPtrDeque* lines, char* split_on, char comment_marker);

EXTERNAL __cdecl void log_files(void);
#endif


#endif