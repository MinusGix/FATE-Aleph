#ifndef SEEN_GENERAL_H
#define SEEN_GENERAL_H

#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <windef.h>
// #define NULL 0

// This define is meant to later be used to force the function with this to be the first thing
// that appears at the address
// This uses part of the implementation of ld script it is currently using (which we perhaps
// shouldn't rely upon) to link patch funcs before other functions and data.
#define PATCH_FUNC __attribute__((section (".text.startup")))

// Defines that this has an SEH FrameHandler at the address
// Currently this does nothing, but it may be used in the future to insert frame handlers?
// Probably not, but at the very least it is a good marker.
#define SEH_FRAME_HANDLER(addr) 

#define CLASS_METHOD __thiscall
#define VIRTUAL_CLASS_METHOD CLASS_METHOD

#define PACKED __attribute__((packed))

#ifdef __cplusplus
#define EXTERNAL extern "C"
#else
#define EXTERNAL 
#endif

// Very aggressively inline. It'd be nice if we could make this error if it fails to inline.
// This is meant for helper functions that are meant to just be used to avoid repeats.
#define INLINE __attribute__((always_inline)) inline

#ifdef __cplusplus
#define RAW_PTR_CAST(x, ptr) (reinterpret_cast<x*>(ptr))
#else
#define RAW_PTR_CAST(x, ptr) ((x*) ptr)
#endif

#ifdef __cplusplus
#define FUNC_PTR_CAST(x, ptr) (reinterpret_cast<x>(ptr))
#else
#define FUNC_PTR_CAST(x, ptr) ((x) ptr)
#endif

// Modifiers for functions that are just compile time assertions.
#define ASSERTS_AREA INLINE static

#define MAKE_VECTOR(t, name) typedef struct name { \
void* unknown; \
t * start; \
t * last; \
t * end; \
} PACKED name


MAKE_VECTOR(void, GenericVector);


// === STRING ===
#define STRING_SSO_CAP 0xf
typedef struct string {
    // I still have no clue what this is. It seems to never be used.
    uint32_t unknown;
    // char buffer[16];
    union {
        char* ptr;
        char buffer[16];
    } data;
    uint32_t length;
    uint32_t capacity;
} PACKED string;

// === RANDOM ===

typedef struct SettingEntry {
    uint32_t id; // enum id
    string name;
    uint32_t value;
} PACKED SettingEntry;

typedef struct StringPtrDeque {
    void* unknown;
    string** start;
    uint32_t capacity;
    uint32_t offset;
    uint32_t length;
} PACKED StringPtrDeque;

/// Known as UnknownGemma1 in Ghidra proj
typedef struct File {
    // I believe this marks whether it is at end of file
    bool eof;
    // Probably padding.
    uint8_t unknown[3];
    FILE* file;
    string path;
} PACKED File;


MAKE_VECTOR(string, StringVectorL);

struct UnknownBravo1;
MAKE_VECTOR(struct UnknownBravo1, UnknownBravo1Vector);
typedef struct UnknownBravo1 {
    string unk;
    StringVectorL unk_string_vec;
    UnknownBravo1Vector vec;
} PACKED UnknownBravo1;

typedef struct Unk48A {
    File* file;
    string filename;
    UnknownBravo1Vector vec;
} PACKED Unk48A;
typedef struct MouseButton {
    bool lbutton;
    bool rbutton;
    bool mbutton;
} PACKED MouseButton;
typedef struct KeyboardInfo {
    bool mm_caps_lock_pressed;
    bool mm_rel_held[512];
    bool mm_pressed[512];
    uint8_t kbd_state[255];
} PACKED KeyboardInfo;
typedef struct UnknownPlato1 {
    struct MouseButton down_new;
    struct MouseButton down;
    struct MouseButton dblclk;
    uint8_t field_0x9;
    uint8_t field_0xa;
    uint8_t field_0xb;
    POINT cursor_position;
    uint32_t field_0x14;
    uint32_t field_0x18;
    uint32_t mouse_wheel_distance;
} PACKED UnknownPlato1;
typedef struct UnknownKant1 {
    uint32_t field_0x0;
    struct UnknownAlfa1 * alfa;
    struct UnknownOmega1 * omega;
    struct RefManager * ref_manager;
    struct UnknownDelta1 * sound_system;
    struct KeyboardInfo kbd_info;
    uint8_t field_0x514;
    uint8_t field_0x515;
    uint8_t field_0x516;
    uint8_t field_0x517;
    struct UnknownPlato1 plato;
    uint32_t unk_buf2[57];
    struct UnknownNut1 * nut;
    void * field_0x620;
    struct UnknownAristotle1 * aristotle;
    uint8_t field_0x628;
    uint8_t field_0x629;
    uint8_t field_0x62a;
    uint8_t field_0x62b;
    uint8_t field_0x62c;
    uint8_t field_0x62d;
    uint8_t field_0x62e;
    uint8_t field_0x62f;
    uint8_t field_0x630;
    uint8_t field_0x631;
    uint8_t field_0x632;
    uint8_t field_0x633;
    void * field_0x634;
    void * field_0x638;
    uint8_t field_0x63c;
    uint8_t field_0x63d;
    uint8_t field_0x63e;
    uint8_t field_0x63f;
    void * field_0x640;
    uint8_t field_0x644;
    uint8_t field_0x645;
    uint8_t field_0x646;
    uint8_t field_0x647;
    void * field_0x648;
    struct UnknownPad1 * pad1;
    uint8_t field_0x650;
    uint8_t field_0x651;
    uint8_t field_0x652;
    uint8_t field_0x653;
    uint8_t field_0x654;
    uint8_t field_0x655;
    uint8_t field_0x656;
    uint8_t field_0x657;
    uint8_t field_0x658;
    uint8_t field_0x659;
    uint8_t field_0x65a;
    uint8_t field_0x65b;
    uint8_t field_0x65c;
    uint8_t field_0x65d;
    uint8_t field_0x65e;
    uint8_t field_0x65f;
    uint8_t field_0x660;
    uint8_t field_0x661;
    uint8_t field_0x662;
    uint8_t field_0x663;
    uint8_t field_0x664;
    uint8_t field_0x665;
    uint8_t field_0x666;
    uint8_t field_0x667;
    uint8_t field_0x668;
    uint8_t field_0x669;
    uint8_t field_0x66a;
    uint8_t field_0x66b;
    struct UnknownDialetic1 * dialetic;
    uint32_t field_0x670;
    uint8_t field_0x674;
    uint8_t field_0x675;
    uint8_t field_0x676;
    uint8_t field_0x677;
    uint8_t field_0x678;
    uint8_t field_0x679;
    uint8_t field_0x67a;
    uint8_t field_0x67b;
    uint8_t field_0x67c;
    uint8_t field_0x67d;
    uint8_t field_0x67e;
    uint8_t field_0x67f;
    uint32_t unk_buf3[16];
    uint8_t field_0x6c0;
    uint8_t field_0x6c1;
    uint8_t field_0x6c2;
    uint8_t field_0x6c3;
    uint8_t field_0x6c4;
    uint8_t field_0x6c5;
    uint8_t field_0x6c6;
    uint8_t field_0x6c7;
    POINT unk_cursor;
    uint8_t field_0x6d0;
    uint8_t field_0x6d1;
    uint8_t field_0x6d2;
    uint8_t field_0x6d3;
    string unk_str1;
    uint8_t field_0x6f0;
    uint8_t field_0x6f1;
    uint8_t field_0x6f2;
    uint8_t field_0x6f3;
    uint32_t dungeon_seed;
    uint8_t field_0x6f8;
    uint8_t field_0x6f9;
    uint8_t field_0x6fa;
    uint8_t field_0x6fb;
    uint8_t field_0x6fc;
    uint8_t field_0x6fd;
    uint8_t field_0x6fe;
    uint8_t field_0x6ff;
    uint8_t field_0x700;
    uint8_t field_0x701;
    uint8_t field_0x702;
    uint8_t field_0x703;
    string unk_str2;
    string unk_str3;
    uint8_t field_0x73c;
    uint8_t field_0x73d;
    uint8_t field_0x73e;
    uint8_t field_0x73f;
    uint8_t field_0x740;
    uint8_t field_0x741;
    uint8_t field_0x742;
    uint8_t field_0x743;
    uint8_t field_0x744;
    uint8_t field_0x745;
    uint8_t field_0x746;
    uint8_t field_0x747;
    uint8_t field_0x748;
    uint8_t field_0x749;
    uint8_t field_0x74a;
    uint8_t field_0x74b;
    string unk_str5;
    uint8_t field_0x768;
    uint8_t field_0x769;
    uint8_t field_0x76a;
    uint8_t field_0x76b;
    uint8_t field_0x76c;
    uint8_t field_0x76d;
    uint8_t field_0x76e;
    uint8_t field_0x76f;
    struct Unkx598 * x598; /* Created by retype action */
    struct FSOUND_SAMPLE * unk_rel_enchanting1;
    struct FSOUND_SAMPLE * unk_sound_sample;
    struct FSOUND_SAMPLE * mm_gems_removed_sound;
    struct FSOUND_SAMPLE * mm_no_gems_sound;
    struct FSOUND_SAMPLE * unk_post_enchantment_sound;
    uint8_t field_0x788;
    uint8_t field_0x789;
    uint8_t field_0x78a;
    uint8_t field_0x78b;
    struct FSOUND_SAMPLE * field_0x78c;
    float field_0x790;
    uint8_t field_0x794;
    uint8_t field_0x795;
    uint8_t field_0x796;
    uint8_t field_0x797;
    uint8_t field_0x798;
    uint8_t field_0x799;
    uint8_t field_0x79a;
    uint8_t field_0x79b;
    uint8_t field_0x79c;
    uint8_t field_0x79d;
    uint8_t field_0x79e;
    uint8_t field_0x79f;
    uint8_t field_0x7a0;
    uint8_t field_0x7a1;
    uint8_t field_0x7a2;
    uint8_t field_0x7a3;
    uint8_t field_0x7a4;
    uint8_t field_0x7a5;
    uint8_t field_0x7a6;
    uint8_t field_0x7a7;
    uint8_t field_0x7a8;
    uint8_t field_0x7a9;
    uint8_t field_0x7aa;
    uint8_t field_0x7ab;
    struct string unk_str6;
    uint8_t field_0x7c8;
    uint8_t field_0x7c9;
    uint8_t field_0x7ca;
    uint8_t field_0x7cb;
    struct SteamRemoteStorage * * steam_remote_storage;
} PACKED UnknownKant1;
static UnknownKant1** gblKant = RAW_PTR_CAST(UnknownKant1*, 0x00e2a110);

typedef struct UnknownMoriarty1 {
    struct UnknownAlfa1 * alfa;
    struct UnknownOmega1 * omega;
    struct RefManager * ref_manager;
    struct UnknownDelta1 * sound_system;
    struct KeyboardInfo kbd_info;
    uint8_t field_0x510;
    uint8_t field_0x511;
    uint8_t field_0x512;
    uint8_t field_0x513;
    struct UnknownPlato1 plato;
    uint32_t unk_buf1[57];
    struct UnknownDepth1 * depth;
    struct UnknownCranberry1 * unk;
    float mmmm_rel_blur;
    struct UnknownCharlie1 * charlie;
    void * field_0x628;
    uint8_t field_0x62c;
    uint8_t field_0x62d;
    uint8_t field_0x62e;
    uint8_t field_0x62f;
    uint8_t field_0x630;
    uint8_t field_0x631;
    uint8_t field_0x632;
    uint8_t field_0x633;
    void * field_0x634;
    uint8_t field_0x638;
    uint8_t field_0x639;
    uint8_t field_0x63a;
    uint8_t field_0x63b;
    uint8_t field_0x63c;
    uint8_t field_0x63d;
    uint8_t field_0x63e;
    uint8_t field_0x63f;
    uint8_t field_0x640;
    uint8_t field_0x641;
    uint8_t field_0x642;
    uint8_t field_0x643;
    uint8_t field_0x644;
    uint8_t field_0x645;
    uint8_t field_0x646;
    uint8_t field_0x647;
    uint8_t field_0x648;
    uint8_t field_0x649;
    uint8_t field_0x64a;
    uint8_t field_0x64b;
    uint32_t * field_0x64c;
    uint32_t * field_0x650;
    uint32_t * field_0x654;
    uint32_t unk_buf2[16];
    struct UnknownSherlock1 * sherlock[18];
    uint32_t * mmmm_indices;
    uint8_t field_0x6e4;
    uint8_t field_0x6e5;
    uint8_t field_0x6e6;
    uint8_t field_0x6e7;
    uint32_t field_0x6e8;
    uint8_t field_0x6ec;
    uint8_t field_0x6ed;
    uint8_t field_0x6ee;
    uint8_t field_0x6ef;
    uint8_t field_0x6f0;
    uint8_t field_0x6f1;
    uint8_t field_0x6f2;
    uint8_t field_0x6f3;
    bool field_0x6f4;
    uint8_t field_0x6f5;
    uint8_t field_0x6f6;
    uint8_t field_0x6f7;
    uint8_t field_0x6f8;
    uint8_t field_0x6f9;
    uint8_t field_0x6fa;
    uint8_t field_0x6fb;
    uint8_t field_0x6fc;
    uint8_t field_0x6fd;
    uint8_t field_0x6fe;
    uint8_t field_0x6ff;
    uint8_t field_0x700;
    uint8_t field_0x701;
    uint8_t field_0x702;
    uint8_t field_0x703;
    uint8_t field_0x704;
    uint8_t field_0x705;
    uint8_t field_0x706;
    uint8_t field_0x707;
    uint8_t field_0x708;
    uint8_t field_0x709;
    uint8_t field_0x70a;
    uint8_t field_0x70b;
    uint8_t field_0x70c;
    uint8_t field_0x70d;
    uint8_t field_0x70e;
    uint8_t field_0x70f;
    uint8_t field_0x710;
    uint8_t field_0x711;
    uint8_t field_0x712;
    uint8_t field_0x713;
    uint8_t field_0x714;
    uint8_t field_0x715;
    uint8_t field_0x716;
    uint8_t field_0x717;
    uint8_t field_0x718;
    uint8_t field_0x719;
    uint8_t field_0x71a;
    uint8_t field_0x71b;
    uint8_t field_0x71c;
    uint8_t field_0x71d;
    uint8_t field_0x71e;
    uint8_t field_0x71f;
    uint8_t field_0x720;
    uint8_t field_0x721;
    uint8_t field_0x722;
    uint8_t field_0x723;
    uint8_t field_0x724;
    uint8_t field_0x725;
    uint8_t field_0x726;
    uint8_t field_0x727;
    uint8_t field_0x728;
    uint8_t field_0x729;
    uint8_t field_0x72a;
    uint8_t field_0x72b;
    float field_0x72c;
    uint8_t field_0x730;
    uint8_t field_0x731;
    uint8_t field_0x732;
    uint8_t field_0x733;
    uint32_t unk_buf3[16];
    uint8_t field_0x774;
    uint8_t field_0x775;
    uint8_t field_0x776;
    uint8_t field_0x777;
    uint8_t field_0x778;
    uint8_t field_0x779;
    uint8_t field_0x77a;
    uint8_t field_0x77b;
    uint8_t field_0x77c;
    uint8_t field_0x77d;
    uint8_t field_0x77e;
    uint8_t field_0x77f;
    uint32_t unk_buf4[16];
} PACKED UnknownMoriarty1;
static UnknownMoriarty1** gblMor = RAW_PTR_CAST(UnknownMoriarty1*, 0x00f37aa8);

typedef struct UnknownOmega1 {
    uint8_t unk[0xff0];
    struct UnknownAleph1* aleph;
    bool mm_screen_dim_has_changed;
    bool mm_fullscreen_has_changed;
    bool failed_config_dat;
    uint8_t field_0xff7;
    string root_path_1_unk;
    string root_path_2_unk;
    unsigned int* m_setting_values;
    unsigned int* dunno_setting_values;
    string* string_entries;
} PACKED UnknownOmega1;


typedef struct UnknownCap1 {
    uint8_t field_0x0;
    uint8_t field_0x1;
    uint8_t field_0x2;
    uint8_t field_0x3;
    void * field_0x4;
    uint32_t field_0x8;
    uint32_t field_0xc;
    int mmm_count;
} PACKED UnknownCap1;
typedef enum AlfaId {
    ALFA_Unknown4=4,
    ALFA_Unknown5=5,
    ALFA_Unknown2=2,
    ALFA_Unknown3=3,
    ALFA_Unknown8=8,
    ALFA_Unknown9=9,
    ALFA_Unknown6=6,
    ALFA_Unknown7=7,
    ALFA_Default=0,
    ALFA_Unknown1=1,
} AlfaId;
typedef struct UnknownAlfa1 {
    // Probably marks what'area' we're in. Like title screen, loading, ingame, etc.
    // Though, figuring it out is a pain.
    AlfaId id;
    uint32_t field_0x4;
    struct UnknownCap1 cap1;
    struct UnknownCap1 cap2;
    struct UnknownCap1 cap3;
    uint8_t field_0x44;
    uint8_t field_0x45;
    uint8_t field_0x46;
    uint8_t field_0x47;
} PACKED UnknownAlfa1;



// === Utility ===
// Note: this will crash the game if you don't have a debugger attached.
#define TRIGGER_DEBUG_INTERRUPT __asm__("int3")
// Statically assert the size of a structure
#ifdef __cplusplus
#define SIZE_CHK(st, size) static_assert(sizeof(st) == size, "Structure size was not as expected. That's not good. This implies that either your envir")
#else
#define SIZE_CHK(st, size) char st##1 [sizeof(st) != size ? -1 : 1]
#endif


ASSERTS_AREA void asserts_general () {
    // Just leaving this here for if you need to check the size of a type.
    // char (* size_chk)[sizeof(UnknownOmega1)] = 1;
    SIZE_CHK(string, 28);
    SIZE_CHK(AlfaId, 4);
    SIZE_CHK(UnknownOmega1, 0x103c);
    SIZE_CHK(UnknownKant1, 0x7d0);
}

#endif