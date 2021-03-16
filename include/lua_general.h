#ifndef SEEN_LUA_GENERAL_H
#define SEEN_LUA_GENERAL_H
// Quite likely don't need the above header guards.
// NOTE: This file is not part of the lua project, but a helper header to make it nicer to use with
// this project.

#pragma GCC diagnostic push
#ifdef __cplusplus
#pragma GCC diagnostic ignored "-Wold-style-cast"
extern "C" {
#endif

#include "lua/lua.h"
#include "lua/lualib.h"
#include "lua/lauxlib.h"
#ifdef __cplusplus
}
#endif
#pragma GCC diagnostic pop


#endif