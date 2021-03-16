#include <cstdarg>
#include <errhandlingapi.h>
#include <memoryapi.h>
#include <stdio.h>
#include <stdlib.h>
#include <winnt.h>
#include <new>

#include <cassert>

#include "aleph.hpp"
#include "helper.hpp"

static bool initialized = false;

/// Claim memory for aleph at a specific address.
/// If this function returns with SUCCESS then it assures that we have access to the address we
/// want to use for Aleph.
static InitStatus __nothrow claim_aleph() {
    MEMORY_BASIC_INFORMATION mem_info;
    SIZE_T query_status = VirtualQuery(aleph, &mem_info, sizeof(MEMORY_BASIC_INFORMATION));
    if (query_status == 0) {
        const DWORD error = GetLastError();
        aleph_error("There was an error querying informatmaking ion about where we want to allocate Aleph. Error code: %lu\n", error);
        return InitStatus::INIT_ALEPH_QUERY_ERROR;
    } else if (query_status != sizeof(MEMORY_BASIC_INFORMATION)) {
        // TODO: Should we assume failure if we didn't get all the info?
        // It might be a better idea to only error if it wouldn't include the info we need (State)
        aleph_error("We did not get all the information about the memory when querying information about where to allocate Aleph.\n");
        return InitStatus::INIT_ALEPH_QUERY_ERROR;
    }

    if ((mem_info.State & MEM_FREE) == 0) {
        aleph_error("Memory that was going to be used for Aleph was already allocated. This could indicate a bad choice of address.\n");
        return InitStatus::INIT_ALEPH_PAGE_USED;
    }

    // We don't use the memory ptr because it may be rounded down (maybe?), and anyway
    // we know what address we're storing Aleph at.
    // This allocation allows consistent storage of it.
    void* memory = VirtualAlloc(aleph, sizeof(Aleph), MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
    if (memory == nullptr) {
        const DWORD error = GetLastError();
        aleph_error("Failed to allocate Aleph. Error code: %lu\n", error);
        return InitStatus::INIT_ALEPH_ALLOC_FAILURE;
    }
    return InitStatus::INIT_SUCCESS;
}
static InitStatus __nothrow initialize_aleph(HMODULE mod) {
    InitStatus status = claim_aleph();
    if (status < InitStatus::INIT_SUCCESS) {
        return status;
    }

    // Use placement-new to initialize aleph with the constructor.
    try {
        new (aleph) Aleph(mod);
    } catch (std::exception&) {
        // We catch the error because we're likely at a C/C++ boundary that may not have sane
        // behavior when receiving C++ exceptions.
        aleph_error("Failed to construct Aleph.");
        return InitStatus::INIT_ALEPH_CONSTRUCTION_FAILURE;
    }

    return InitStatus::INIT_SUCCESS;
}

EXTERNAL CALLING_CONV __nothrow InitStatus init(HMODULE mod) {
    if (initialized) {
        aleph_warn("Initialize was called a second time. Ignoring, but this may cause weird effects.\n");
        return INIT_STATUS_TWICE;
    }
    aleph_info("Initializing\n");

    InitStatus aleph_status = initialize_aleph(mod);
    if (aleph_status < InitStatus::INIT_SUCCESS) {
        return aleph_status;
    }

    InitStatus lua_status = aleph->initialize_lua();
    if (lua_status < InitStatus::INIT_SUCCESS) {
        return lua_status;
    }

    assert(aleph->lua != nullptr);

    // int status = luaL_loadfile(aleph->lua, "scripts\\test_script.lua");
    // if (status) {
    //     aleph_warn("Failed to load script: %s\n", lua_tostring(aleph->lua, -1));
    // } else {
    //     lua_pcall(aleph->lua, 0, LUA_MULTRET, 0);
    // }
    aleph_info("Initialized Lua");

    // TODO: Load mods.

    aleph_info("Initialized");

    atexit_v(exiting);

    return InitStatus::INIT_SUCCESS;
}


// To be called when
EXTERNAL __cdecl __nothrow void exiting() {
    // TODO: Do full deinitialization.
    // Destruct aleph
    //  - free lua
    // Free pages
    // I don't think we need to close the module? No clue how it handles that if you're in the
    // module...

    log_files();
}

