#pragma bank 255
// SpriteSheet: HandCursor

#include "gbs_types.h"
#include "data/sprite_handcursor_tileset.h"
#include "data/sprite_handcursor_bank2_tileset.h"

BANKREF(sprite_handcursor)

#define SPRITE_2_STATE_DEFAULT 0

const metasprite_t sprite_handcursor_metasprite_0[]  = {
    { 0, 8, 0, 7 }, { 0, -8, 0, 15 },
    {metasprite_end}
};

const metasprite_t * const sprite_handcursor_metasprites[] = {
    sprite_handcursor_metasprite_0
};

const struct animation_t sprite_handcursor_animations[] = {
    {
        .start = 0,
        .end = 0
    },
    {
        .start = 0,
        .end = 0
    },
    {
        .start = 0,
        .end = 0
    },
    {
        .start = 0,
        .end = 0
    },
    {
        .start = 0,
        .end = 0
    },
    {
        .start = 0,
        .end = 0
    },
    {
        .start = 0,
        .end = 0
    },
    {
        .start = 0,
        .end = 0
    }
};

const UWORD sprite_handcursor_animations_lookup[] = {
    SPRITE_2_STATE_DEFAULT
};

const struct spritesheet_t sprite_handcursor = {
    .n_metasprites = 1,
    .emote_origin = {
        .x = 0,
        .y = -16
    },
    .metasprites = sprite_handcursor_metasprites,
    .animations = sprite_handcursor_animations,
    .animations_lookup = sprite_handcursor_animations_lookup,
    .bounds = {
        .left = 0,
        .bottom = 7,
        .right = 15,
        .top = -8
    },
    .tileset = TO_FAR_PTR_T(sprite_handcursor_tileset),
    .cgb_tileset = TO_FAR_PTR_T(sprite_handcursor_bank2_tileset)
};
