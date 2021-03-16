#ifndef SEEN_GENERAL_FUNC_H
#define SEEN_GENERAL_FUNC_H

#include "general.h"
#include <windef.h>

// === stdlib ===
typedef void (*free_t)(void*);
static free_t free_v = FUNC_PTR_CAST(free_t, 0x005dd138); // thunk

typedef void (* __cdecl sprintf_t)(char* dest, char* format, ...);
static sprintf_t sprintf_v = FUNC_PTR_CAST(sprintf_t, 0x005ddbcd);

typedef void* (*__cdecl operator_new_t)(uint32_t size);
static operator_new_t operator_new_v = FUNC_PTR_CAST(operator_new_t, 0x005dc490);

typedef int (* __cdecl atexit_t)(void (* __cdecl func)(void));
static atexit_t atexit_v = FUNC_PTR_CAST(atexit_t, 0x005dde46);


// === WINDOWS ===
// typedef void* HMODULE;
// typedef int32_t (* __stdcall FARPROC)(void);
// typedef int32_t (* __stdcall NEARPROC)(void);
// typedef int32_t (* __stdcall PROC)(void);

// Note: Why these are pointers to the function rather than the function themselves is
// because they are loaded in as dlls and so all i have is the pointer to where the func
// ptr will bep ut when they're loaded
// The function redeclarations are just to make them cleaner to use.
// Making a macro to make this easier is sadly too challenging for the C macro system
// I wish I was using Rust. Almost. I'd have to spam unsafe.
typedef void (* __stdcall LoadStringA_t)(HMODULE, uint32_t, char*, uint32_t);
static LoadStringA_t* LoadStringA_ptr = RAW_PTR_CAST(LoadStringA_t, 0x00b5e280);
INLINE static void __stdcall LoadStringA_v(HMODULE m, uint32_t id, char* buf, uint32_t size) {
    (*LoadStringA_ptr)(m, id, buf, size);
}

typedef void (* __stdcall OutputDebugStringA_t)(char*);
static OutputDebugStringA_t* OutputDebugStringA_ptr = RAW_PTR_CAST(OutputDebugStringA_t, 0x00b5e0ec);
INLINE static void __stdcall OutputDebugStringA_v(char* text) {
    (*OutputDebugStringA_ptr)(text);
}

typedef HMODULE (* __stdcall LoadLibraryA_t)(char*);
static LoadLibraryA_t* LoadLibraryA_ptr = RAW_PTR_CAST(LoadLibraryA_t, 0x00b5e1f0);
INLINE static HMODULE __stdcall LoadLibraryA_v(char* name) {
    return (*LoadLibraryA_ptr)(name);
}

typedef FARPROC (* __stdcall GetProcAddress_t)(HMODULE, char* name);
static GetProcAddress_t* GetProcAddress_ptr = RAW_PTR_CAST(GetProcAddress_t, 0x00b5e110);
INLINE static FARPROC __stdcall GetProcAddress_v(HMODULE module, char* name) {
    return (*GetProcAddress_ptr)(module, name);
}

typedef uint32_t (* __stdcall GetLastError_t)(void);
static GetLastError_t* GetLastError_ptr = RAW_PTR_CAST(GetLastError_t, 0x00b5e108);
INLINE static uint32_t __stdcall GetLastError_v(void) {
    return (*GetLastError_ptr)();
}

typedef void (* __attribute__ ((noreturn)) __stdcall ExitProcess_t)(uint32_t code);
static ExitProcess_t* ExitProcess_ptr = RAW_PTR_CAST(ExitProcess_t, 0x00b5e190);
INLINE static __attribute__ ((noreturn)) void __stdcall ExitProcess_v(uint32_t code) {
    (*ExitProcess_ptr)(code);
}

// === StringPtrDeque ===
typedef void (* __thiscall string_ptr_deque_push_back_t)(StringPtrDeque*, string* value);
static string_ptr_deque_push_back_t string_ptr_deque_push_back = FUNC_PTR_CAST(string_ptr_deque_push_back_t, 0x004bd620);

// === Vectors ===
INLINE static void h_vector_clear(GenericVector* vector) {
    vector->start = NULL;
    vector->last = NULL;
    vector->end = NULL;
}

// === RANDOM ===
typedef HMODULE (* __stdcall getLocaleModule_t)(void);
static getLocaleModule_t getLocaleModule_v = FUNC_PTR_CAST(getLocaleModule_t, 0x0041e660);

typedef void (* __thiscall unk48a_unk_parsing_t)(Unk48A* self);
static unk48a_unk_parsing_t unk48a_unk_parsing_v = FUNC_PTR_CAST(unk48a_unk_parsing_t, 0x004b4f40);

#endif