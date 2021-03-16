#ifndef SEEN_FATE_MOD_H
#define SEEN_FATE_MOD_H
#include <stdarg.h>
#include <windef.h>

#include "../include/lua_general.h"

#ifdef __cplusplus
extern "C" {
#endif

#include "../patches/general.h"
#include "../patches/file.h"
#ifdef __cplusplus
}
#endif

#include "helper.hpp"

#define CALLING_CONV __stdcall

// This is a macro to initialize a property on  a structure with a value
// Since that is only supported in C++, the C version does not set it.
// NOTE: This _does_ mean that the field won't be initialized in C!
// This should be used for code that is created in C++
// and C only needs the type definitions!
#ifdef __cplusplus
#define CXX_SET(t, n, v) t n = v
#else
#define CXX_SET(t, n, v) t n
#endif

// Using this before initialization will likely crash.
// It'd be nice to make this a normal variable.
#define ALEPH_PTR 0x50000000
#define aleph RAW_PTR_CAST(Aleph, ALEPH_PTR)


// <0 = failure
// 0  = success.
// >0 = success but with caveats
typedef enum InitStatus {
    /// We were called twice (or more)..
    INIT_STATUS_TWICE = 1,
    /// We succeeded. No issues.
    INIT_SUCCESS = 0,

    INIT_UNKNOWN_FAILURE = -1,
    // We failed to query the memory location that aleph was at
    INIT_ALEPH_QUERY_ERROR = -2,
    /// We failed to allocate Aleph
    INIT_ALEPH_ALLOC_FAILURE = -3,
    /// The page was already in use.
    INIT_ALEPH_PAGE_USED = -4,
    /// We failed to construct. This likely originates from placement new complaining
    /// or our constructor throwing an exception.
    INIT_ALEPH_CONSTRUCTION_FAILURE = -5,
    /// We failed to initialize lua (newstate)
    INIT_LUA_NEW_STATE_FAILURE = -10,
} InitStatus;


EXTERNAL typedef struct Aleph {
    HMODULE mod;
    CXX_SET(lua_State*, lua, nullptr);
    // == Functions ==
    // These are function pointers to the functions so that C patches can access them
    // without going through the GetProcAddress method.
    CXX_SET(file_readline_t, file_readline, ::file_readline);
    CXX_SET(file_parse_t, file_parse, ::file_parse);

    CXX_SET(print_func, info, ::aleph_info);
    CXX_SET(print_func, warn, ::aleph_warn);
    CXX_SET(print_func, error, ::aleph_error);

    CXX_SET(log_files_t, log_files, ::log_files);

    #ifdef __cplusplus
    explicit Aleph(HMODULE mod_t): mod(mod_t) {}

    // TODO: Should this have its own return type for unique to lua statuses?
    // This doesn't do much, os maybe not.
    InitStatus initialize_lua () {
        this->lua = luaL_newstate();
        if (this->lua == nullptr) {
            aleph_error("Failed to create Lua state.\n");
            return INIT_LUA_NEW_STATE_FAILURE;
        }

        // Open general use libs.
        // TODO: In the future we may want to limit this more? Though given the code we're working
        // with, restricting file access just makes it harder to exploit.
        luaL_openlibs(aleph->lua);
        return InitStatus::INIT_SUCCESS;
    }
    #endif
} Aleph;

#ifndef ALEPH_NO_FUNC
EXTERNAL CALLING_CONV __nothrow InitStatus init(HMODULE mod);
EXTERNAL __cdecl __nothrow void exiting(void);
#endif
typedef InitStatus (* CALLING_CONV __nothrow init_t)(HMODULE mod);

#endif