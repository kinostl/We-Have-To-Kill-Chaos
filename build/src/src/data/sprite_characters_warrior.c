#pragma bank 255
// SpriteSheet: characters/warrior

#include "gbs_types.h"
#include "data/sprite_characters_warrior_tileset.h"
#include "data/sprite_characters_warrior_bank2_tileset.h"

BANKREF(sprite_characters_warrior)

#define SPRITE_3_STATE_DEFAULT 0

const metasprite_t sprite_characters_warrior_metasprite_0[]  = {
    { 0, 8, 0, 0 }, { -16, 0, 2, 0 }, { 16, -8, 0, 8 }, { -16, 0, 2, 8 },
    {metasprite_end}
};

const metasprite_t * const sprite_characters_warrior_metasprites[] = {
    sprite_characters_warrior_metasprite_0
};

const struct animation_t sprite_characters_warrior_animations[] = {
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

const UWORD sprite_characters_warrior_animations_lookup[] = {
    SPRITE_3_STATE_DEFAULT
};

const struct spritesheet_t sprite_characters_warrior = {
    .n_metasprites = 1,
    .emote_origin = {
        .x = 0,
        .y = -32
    },
    .metasprites = sprite_characters_warrior_metasprites,
    .animations = sprite_characters_warrior_animations,
    .animations_lookup = sprite_characters_warrior_animations_lookup,
    .bounds = {
        .left = 0,
        .bottom = 7,
        .right = 15,
        .top = -8
    },
    .tileset = TO_FAR_PTR_T(sprite_characters_warrior_tileset),
    .cgb_tileset = TO_FAR_PTR_T(sprite_characters_warrior_bank2_tileset)
};
