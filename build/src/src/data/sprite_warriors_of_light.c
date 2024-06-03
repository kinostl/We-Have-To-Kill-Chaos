#pragma bank 255
// SpriteSheet: warriors_of_light

#include "gbs_types.h"
#include "data/sprite_warriors_of_light_tileset.h"
#include "data/sprite_warriors_of_light_bank2_tileset.h"

BANKREF(sprite_warriors_of_light)

#define SPRITE_0_STATE_DEFAULT 0

const metasprite_t sprite_warriors_of_light_metasprite_0[]  = {
    { 0, 8, 0, 8 }, { 0, -8, 2, 8 },
    {metasprite_end}
};

const metasprite_t sprite_warriors_of_light_metasprite_1[]  = {
    { 0, 0, 0, 0 }, { 0, 8, 2, 0 },
    {metasprite_end}
};

const metasprite_t sprite_warriors_of_light_metasprite_2[]  = {
    { 0, 8, 4, 0 }, { 0, -8, 6, 0 },
    {metasprite_end}
};

const metasprite_t sprite_warriors_of_light_metasprite_3[]  = {
    { 0, 8, 0, 32 }, { 0, -8, 2, 32 },
    {metasprite_end}
};

const metasprite_t sprite_warriors_of_light_metasprite_4[]  = {
    { 0, 0, 0, 40 }, { 0, 8, 2, 40 },
    {metasprite_end}
};

const metasprite_t sprite_warriors_of_light_metasprite_5[]  = {
    { 0, 0, 4, 8 }, { 0, 8, 6, 8 },
    {metasprite_end}
};

const metasprite_t sprite_warriors_of_light_metasprite_6[]  = {
    { 0, 0, 4, 32 }, { 0, 8, 6, 32 },
    {metasprite_end}
};

const metasprite_t sprite_warriors_of_light_metasprite_7[]  = {
    { 0, 8, 4, 40 }, { 0, -8, 6, 40 },
    {metasprite_end}
};

const metasprite_t * const sprite_warriors_of_light_metasprites[] = {
    sprite_warriors_of_light_metasprite_0,
    sprite_warriors_of_light_metasprite_1,
    sprite_warriors_of_light_metasprite_2,
    sprite_warriors_of_light_metasprite_3,
    sprite_warriors_of_light_metasprite_0,
    sprite_warriors_of_light_metasprite_4,
    sprite_warriors_of_light_metasprite_1,
    sprite_warriors_of_light_metasprite_5,
    sprite_warriors_of_light_metasprite_2,
    sprite_warriors_of_light_metasprite_6,
    sprite_warriors_of_light_metasprite_3,
    sprite_warriors_of_light_metasprite_7
};

const struct animation_t sprite_warriors_of_light_animations[] = {
    {
        .start = 0,
        .end = 0
    },
    {
        .start = 1,
        .end = 1
    },
    {
        .start = 2,
        .end = 2
    },
    {
        .start = 3,
        .end = 3
    },
    {
        .start = 4,
        .end = 5
    },
    {
        .start = 6,
        .end = 7
    },
    {
        .start = 8,
        .end = 9
    },
    {
        .start = 10,
        .end = 11
    }
};

const UWORD sprite_warriors_of_light_animations_lookup[] = {
    SPRITE_0_STATE_DEFAULT
};

const struct spritesheet_t sprite_warriors_of_light = {
    .n_metasprites = 12,
    .emote_origin = {
        .x = 0,
        .y = -16
    },
    .metasprites = sprite_warriors_of_light_metasprites,
    .animations = sprite_warriors_of_light_animations,
    .animations_lookup = sprite_warriors_of_light_animations_lookup,
    .bounds = {
        .left = 0,
        .bottom = 7,
        .right = 15,
        .top = -8
    },
    .tileset = TO_FAR_PTR_T(sprite_warriors_of_light_tileset),
    .cgb_tileset = TO_FAR_PTR_T(sprite_warriors_of_light_bank2_tileset)
};
