#ifndef SEEN_GENERAL_GAME_H
#define SEEN_GENERAL_GAME_H

#include "general.h"
#include <d3d8.h>
#include <windef.h>
// Steam callback structure, possibly not full
struct CCallbackBase {
    void * mmm_vtable; /* Unsure if there is a vatable at the base */
    uint8_t callbackFlags;
    int iCallback;
} PACKED;
typedef struct CCallbackBase CCallbackBase, *PCCallbackBase;

typedef struct Game {
    void* vtable;

    bool mm_windowed; /* Created by retype action */
    uint8_t field_0x1;
    uint8_t field_0x2;
    uint8_t field_0x3;
    struct D3DADAPTER_IDENTIFIER8_wrapper * adapter_w;
    struct UnknownSirius1 * sirius;
    struct UnknownDelphi1 * delphi; /* Created by retype action */
    D3DDISPLAYMODE display_mode;
    D3DFORMAT w_depth_stencil_format; /* Created by retype action */
    D3DMULTISAMPLE_TYPE w_multisample_type; /* Created by retype action */
    unsigned int field_0x28;
    int w_unk2; /* Created by retype action */
    unsigned int presentation_interval_rel_fullscreen; /* Created by retype action */
    unsigned int client_width;
    unsigned int client_height; /* Created by retype action */
    struct D3DADAPTER_IDENTIFIER8_wrapper * nw_adapter_w;
    struct UnknownSirius1 * nw_sirius;
    struct UnknownDelphi1 * nw_delphi; /* Created by retype action */
    D3DDISPLAYMODE nw_display_mode; /* Created by retype action */
    D3DFORMAT nw_depth_stencil_format; /* Created by retype action */
    D3DMULTISAMPLE_TYPE nw_multisample_type; /* Created by retype action */
    int nw_unk2; /* Created by retype action */
    unsigned int presentation_interval_rel; /* Created by retype action */
    D3DPRESENT_PARAMETERS pres_params;
    struct IDirect3D8 * d3d;
    struct IDirect3DDevice8 * d3d_dev;
    HANDLE semaphore_handle;
    struct UnknownOrion1 * orion; /* Created by retype action */
    D3DCAPS8 d3d_caps;
    D3DSURFACE_DESC surface_desc;
    HWND mHWND;
    HMENU hwnd_menu; /* Created by retype action */
    DWORD window_style;
    string window_title;
    unsigned int window_width;
    unsigned int window_height;
    struct tagRECT window_rect;
    struct tagRECT client_rect;
    bool mmmm_sound_not_init;
    bool not_vsync; /* Created by retype action */
    bool m_is_vsync; /* Created by retype action */
    bool mm_is_closing; /* Created by retype action */
    bool mm_has_window_style; /* Created by retype action */
    bool mmm_unk_bool1; /* Created by retype action */
    bool mmm_failed_cooperative_level;
    bool field_0x1f7;
    bool field_0x1f8;
    uint8_t field_0x1f9;
    bool mmmm_loaded_some_settings_info;
    bool ref_mg_rel1;
    bool mm_not_using_custom_cursor; /* Created by retype action */
    bool mmm_rel_to_initializd;
    bool fullscreen; /* Created by retype action */
    uint8_t mm_bool2_rel_fsaa; /* Created by retype action */
    bool unk_bool; /* Created by retype action */
    bool field_0x201;
    uint8_t field_0x202;
    bool field_0x203;
    bool is_os_older_version; /* Created by retype action */
    uint8_t mm_bool; /* Created by retype action */
    uint8_t field_0x206;
    uint8_t field_0x207;
    unsigned int field_0x208;
    float mm_fps;
    uint8_t unk_mmm_char_arr; /* Created by retype action */
    uint8_t field_0x211;
    uint8_t field_0x212;
    uint8_t field_0x213;
    uint8_t field_0x214;
    uint8_t field_0x215;
    uint8_t field_0x216;
    uint8_t field_0x217;
    uint8_t field_0x218;
    uint8_t field_0x219;
    uint8_t field_0x21a;
    uint8_t field_0x21b;
    uint8_t field_0x21c;
    uint8_t field_0x21d;
    uint8_t field_0x21e;
    uint8_t field_0x21f;
    uint8_t field_0x220;
    uint8_t field_0x221;
    uint8_t field_0x222;
    uint8_t field_0x223;
    uint8_t field_0x224;
    uint8_t field_0x225;
    uint8_t field_0x226;
    uint8_t field_0x227;
    uint8_t field_0x228;
    uint8_t field_0x229;
    uint8_t field_0x22a;
    uint8_t field_0x22b;
    uint8_t field_0x22c;
    uint8_t field_0x22d;
    uint8_t field_0x22e;
    uint8_t field_0x22f;
    uint8_t field_0x230;
    uint8_t field_0x231;
    uint8_t field_0x232;
    uint8_t field_0x233;
    uint8_t field_0x234;
    uint8_t field_0x235;
    uint8_t field_0x236;
    uint8_t field_0x237;
    uint8_t field_0x238;
    uint8_t field_0x239;
    uint8_t field_0x23a;
    uint8_t field_0x23b;
    uint8_t field_0x23c;
    uint8_t field_0x23d;
    uint8_t field_0x23e;
    uint8_t field_0x23f;
    uint8_t field_0x240;
    uint8_t field_0x241;
    uint8_t field_0x242;
    uint8_t field_0x243;
    uint8_t field_0x244;
    uint8_t field_0x245;
    uint8_t field_0x246;
    uint8_t field_0x247;
    uint8_t field_0x248;
    uint8_t field_0x249;
    uint8_t field_0x24a;
    uint8_t field_0x24b;
    uint8_t field_0x24c;
    uint8_t field_0x24d;
    uint8_t field_0x24e;
    uint8_t field_0x24f;
    uint8_t field_0x250;
    uint8_t field_0x251;
    uint8_t field_0x252;
    uint8_t field_0x253;
    uint8_t field_0x254;
    uint8_t field_0x255;
    uint8_t field_0x256;
    uint8_t field_0x257;
    uint8_t field_0x258;
    uint8_t field_0x259;
    uint8_t field_0x25a;
    uint8_t field_0x25b;
    uint8_t field_0x25c;
    uint8_t field_0x25d;
    uint8_t field_0x25e;
    uint8_t field_0x25f;
    uint8_t field_0x260;
    uint8_t field_0x261;
    uint8_t field_0x262;
    uint8_t field_0x263;
    uint8_t field_0x264;
    uint8_t field_0x265;
    uint8_t field_0x266;
    uint8_t field_0x267;
    uint8_t field_0x268;
    uint8_t field_0x269;
    uint8_t field_0x26a;
    uint8_t field_0x26b;
    struct CCallbackBase unk_maybe_function;
    uint8_t field_0x275;
    uint8_t field_0x276;
    uint8_t field_0x277;
    uint8_t mmm_self; /* Created by retype action */
    uint8_t field_0x279;
    uint8_t field_0x27a;
    uint8_t field_0x27b;
    unsigned int unk_function;
    uint8_t field_0x280;
    uint8_t field_0x281;
    uint8_t field_0x282;
    uint8_t field_0x283;
    UnknownAlfa1* alfa;
    struct UnknownOmega1 * omega; /* Game destructor has a debug log referring to this as 'device objects' */
    struct UnknownAleph1 * unk_aleph;
    struct UnknownDelta1 * sound_system;
    struct RefManager * ref_manager; /* Created by retype action */
    struct UnknownInvisible1 * invisible;
    struct FPSText * fps_text; /* Created by retype action */
    uint8_t mmmm_should_be_closing;
    bool gamma_ramp_rel;
    uint8_t field_0x2a2;
    uint8_t field_0x2a3;
    struct string version_text;
    struct Unkx598 * unk_x598;
    bool field_0x2c4;
    bool mm_has_set_gamma_ramp;
    bool steam_api_init_success;
    uint8_t field_0x2c7;
} PACKED Game;

// == Game ==
typedef void (* CLASS_METHOD game_set_gamma_ramp_t)(Game*);
static game_set_gamma_ramp_t game_set_gamma_ramp_v = (game_set_gamma_ramp_t)0x0041ddc0;

typedef void (* CLASS_METHOD game_unk_transforms_rel_t)(Game*);
static game_unk_transforms_rel_t game_unk_transforms_rel_v = (game_unk_transforms_rel_t)0x0041df00;

typedef void (* CLASS_METHOD game_fun0041df60_t)(Game*);
static game_fun0041df60_t game_fun0041df60_v = (game_fun0041df60_t)0x0041df60;

typedef HRESULT (* CLASS_METHOD game_update_screen_dimensions_t)(Game*, uint32_t width, uint32_t height);
static game_update_screen_dimensions_t game_update_screen_dimensions_v = (game_update_screen_dimensions_t)0x00404a90;

typedef HRESULT (* CLASS_METHOD game_fullscreen_rel_t)(Game*);
static game_fullscreen_rel_t game_fullscreen_rel_v = (game_fullscreen_rel_t)0x004b8d40;

// == Omega ==
typedef enum SettingIdx {
    SETTING_Vsync=41,
    SETTING_SpecularMapping=12,
    SETTING_AnimatedFog=42,
    SETTING_FSAA=9,
    SETTING_MotionBlur=30,
    SETTING_1440x900=54,
    SETTING_DynamicReflections=32,
    SETTING_1024x768_1=44,
    SETTING_1024x768_2=49,
    SETTING_GamesPlayed=31,
    SETTING_CubeMapping=11,
    SETTING_1680x1050=56,
    SETTING_FogTable=23,
    SETTING_1152x864=50,
    SETTING_SFXVolume=6,
    SETTING_StencilShadows=10,
    SETTING_PointLights=25,
    SETTING_Joystick=16,
    SETTING_960x600=47,
    SETTING_ShadowDetail=36,
    SETTING_Fullscreen=3,
    SETTING_ReflectionSpecularMapping=13,
    SETTING_SceneReflection=15,
    SETTING_ClampUVs=27,
    SETTING_MasterVolume=4,
    SETTING_PointSprites=20,
    SETTING_ProjectedShadows=33,
    SETTING_640x460_2=45,
    SETTING_640x460_1=43,
    SETTING_1600x1200=55,
    SETTING_ScreenHeight=1,
    SETTING_AllowCDAudio=7,
    SETTING_AlphaFade=19,
    SETTING_NoramlAdditive=29,
    SETTING_AlphaWrite=22,
    SETTING_MipFilter=26,
    SETTING_800x600=46,
    SETTING_Specular=21,
    SETTING_ShowTips=39,
    SETTING_ShadowResolution=34,
    SETTING_NormalMapping=14,
    SETTING_1280x768=52,
    SETTING_RedBlood=59,
    SETTING_NormalModulate=28,
    SETTING_1920x1080=58,
    SETTING_GammaRamp=37,
    SETTING_1280x720=51,
    SETTING_1280x1024=53,
    SETTING_DungeonSeed=35,
    SETTING_CustomCursor=60,
    SETTING_MusicVolume=5,
    SETTING_1024x600=48,
    SETTING_ScreenWidth=0,
    SETTING_ForceFeedback=17,
    SETTING_MaxLights=24,
    SETTING_CDMusic=8,
    SETTING_ShowFPS=2,
    SETTING_Online=18,
    SETTING_ParticleDetail=38,
    SETTING_1920x1200=57,
    SETTING_ConfirmLevel=40
} SettingIdx;

typedef unsigned int (* CLASS_METHOD omega_get_setting_value_t)(UnknownOmega1*, SettingIdx);
static omega_get_setting_value_t omega_get_setting_value_v = (omega_get_setting_value_t)0x004b8930;

typedef bool (* CLASS_METHOD omega_unmark_screen_dim_change_t)(UnknownOmega1*);
static omega_unmark_screen_dim_change_t omega_unmark_screen_dim_change_v = (omega_unmark_screen_dim_change_t)0x004b8d60;

typedef bool (* CLASS_METHOD omega_unmark_fullscreen_change_t)(UnknownOmega1*);
static omega_unmark_fullscreen_change_t omega_unmark_fullscreen_change_v = (omega_unmark_fullscreen_change_t)0x004b8d40;

// == Kant ==
typedef void (* CLASS_METHOD kant_rendering_rel_t)(UnknownKant1*, IDirect3DDevice8*, HWND);
static kant_rendering_rel_t kant_rendering_rel_v = (kant_rendering_rel_t)0x004605e0;

// == Moriarty ==
typedef void (* CLASS_METHOD mor_rendering_rel_t)(UnknownMoriarty1*, IDirect3DDevice8*);
static mor_rendering_rel_t mor_rendering_rel_v = (mor_rendering_rel_t)0x0052c820;

typedef void (* CLASS_METHOD mor_update_cursor_t)(UnknownMoriarty1*);
static mor_update_cursor_t mor_update_cursor_v = (mor_update_cursor_t)0x0052c590;

ASSERTS_AREA void asserts_game () {
    SIZE_CHK(SettingIdx, 4);
    SIZE_CHK(Game, 0x2cc);
}

#endif