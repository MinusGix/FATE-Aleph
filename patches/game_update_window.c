// 1eac0 1ee0f

#include "general.h"
#include "general_func.h"
#include "game.h"
#include <d3d8types.h>

// ARGB
#define CLEAR_COLOR 0xff000000

void update_dim_helper (Game* self) {
    game_update_screen_dimensions_v(
        self,
        omega_get_setting_value_v(self->omega, SETTING_ScreenWidth),
        omega_get_setting_value_v(self->omega, SETTING_ScreenHeight)
    );
    if (*gblMor != NULL) {
        mor_update_cursor_v(*gblMor);
    }
}


PATCH_FUNC
VIRTUAL_CLASS_METHOD
unsigned int game_update_window (Game* self) {
    IDirect3DDevice8* d3d_dev = self->d3d_dev;

    if (self->gamma_ramp_rel == false) {
        return 0;
    }

    if (self->field_0x2c4 == false) {
        self->field_0x2c4 = true;
    } else if (self->mm_has_set_gamma_ramp == false) {
        game_set_gamma_ramp_v(self);
        self->mm_has_set_gamma_ramp = true;
    }

    if (self->field_0x203 != false) {
        uint32_t fsaa = omega_get_setting_value_v(self->omega, SETTING_FSAA);
        uint32_t aa = 1;
        if (fsaa == 0) {
            aa = 0;
        } else {
            const bool unk = self->mm_has_window_style;
            if (unk == false) {
                if (self->mm_bool2_rel_fsaa == 0) {
                    aa = 0;
                }
            } else if (self->unk_bool == false && (unk != false || self->mm_bool2_rel_fsaa == 0)) {
                aa = 0;
            }
        }
        d3d_dev->lpVtbl->SetRenderState(self->d3d_dev, D3DRS_MULTISAMPLEANTIALIAS, aa);
    }

    game_unk_transforms_rel_v(self);
    int status = d3d_dev->lpVtbl->BeginScene(d3d_dev);
    uint32_t status_checked = status < 0;
    if (status_checked != 0) {
        return status_checked;
    }

    UnknownMoriarty1* mor = *gblMor;
    UnknownKant1* kant = *gblKant;

    D3DVIEWPORT8 viewport = {
        .X = 0,
        .Y = 0,
        .Width = omega_get_setting_value_v(self->omega, SETTING_ScreenWidth),
        .Height = omega_get_setting_value_v(self->omega, SETTING_ScreenHeight),
        .MinZ = 0.0,
        .MaxZ = 1.0,
    };
    d3d_dev->lpVtbl->SetViewport(d3d_dev, &viewport);

    d3d_dev->lpVtbl->Clear(d3d_dev, 0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, CLEAR_COLOR, 1.0, 0);

    AlfaId id = self->alfa->id;
    if (id == ALFA_Unknown3 || id == ALFA_Unknown5) {
        if (mor != NULL) {
            mor_rendering_rel_v(mor, self->d3d_dev);
        }
    } else if (id == ALFA_Unknown9) {
        if (kant != NULL) {
            kant_rendering_rel_v(kant, self->d3d_dev, self->mHWND);
        }
    }

    if (self->mm_has_set_gamma_ramp != false) {
        game_fun0041df60_v(self);
    }

    d3d_dev->lpVtbl->EndScene(d3d_dev);

    const bool screen_dim_changed = omega_unmark_screen_dim_change_v(self->omega);
    if (screen_dim_changed != false) {
        update_dim_helper(self);
    }

    const bool fullscreen_has_changed = omega_unmark_fullscreen_change_v(self->omega);
    if (fullscreen_has_changed != false) {
        game_fullscreen_rel_v(self);
        if (mor != NULL) {
            mor_update_cursor_v(mor);
        }
    }

    if (self->field_0x203 != false) {
        return 0;
    }

    uint32_t fsaa = omega_get_setting_value_v(self->omega, SETTING_FSAA);
    if (fsaa != 0) {
        if (self->mm_has_window_style != false) {
            if (self->field_0x202 != 0 && self->mm_bool == 0) {
                self->mm_bool = 1;
                goto Continue;
            }
            // if (self->mm_has_window_style != false) {
            // }
        }

        if (self->field_0x201 != 0 && self->mm_bool == 0) {
            self->mm_bool = 1;
            goto Continue;
        }

        return 0;
    }
    // fsaa = omega_get_setting_value_v(self->omega, SETTING_FSAA);
    // if (fsaa != 0) {
    //     return 0;
    // }

    if (self->mm_has_window_style != false) {
        if (self->unk_bool != false) {
            self->mm_bool = 0;
            goto Continue;
        }
        return 0;
    }

    if (self->mm_bool2_rel_fsaa == 0) {
        return 0;
    }

Continue: ;
    update_dim_helper(self);
    return 0;
}