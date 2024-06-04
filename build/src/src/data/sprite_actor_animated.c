#pragma bank 255
// SpriteSheet: actor_animated

#include "gbs_types.h"
#include "data/sprite_actor_animated_tileset.h"
#include "data/sprite_actor_animated_bank2_tileset.h"

BANKREF(sprite_actor_animated)

#define SPRITE_1_STATE_DEFAULT 0
#define SPRITE_1_STATE_INACTIVE 0
#define SPRITE_1_STATE_FLASHING 0

const metasprite_t sprite_actor_animated_metasprite_0[]  = {
    { 0, 8, 6, 0 }, { 0, -8, 8, 0 },
    {metasprite_end}
};

const metasprite_t sprite_actor_animated_metasprite_1[]  = {
    { 0, 8, 0, 0 }, { 0, -8, 2, 0 },
    {metasprite_end}
};

const metasprite_t sprite_actor_animated_metasprite_2[]  = {
    { 0, 8, 4, 0 }, { 0, -8, 4, 32 },
    {metasprite_end}
};

const metasprite_t sprite_actor_animated_metasprite_3[]  = {
    { 0, 0, 0, 32 }, { 0, 8, 2, 32 },
    {metasprite_end}
};

const metasprite_t sprite_actor_animated_metasprite_4[]  = {
    { 0, 8, 6, 8 }, { 0, -8, 8, 8 },
    {metasprite_end}
};

const metasprite_t sprite_actor_animated_metasprite_5[]  = {
    { 0, 8, 0, 8 }, { 0, -8, 2, 8 },
    {metasprite_end}
};

const metasprite_t sprite_actor_animated_metasprite_6[]  = {
    { 0, 8, 4, 8 }, { 0, -8, 4, 40 },
    {metasprite_end}
};

const metasprite_t sprite_actor_animated_metasprite_7[]  = {
    { 0, 0, 0, 40 }, { 0, 8, 2, 40 },
    {metasprite_end}
};

const metasprite_t * const sprite_actor_animated_metasprites[] = {
    sprite_actor_animated_metasprite_0,
    sprite_actor_animated_metasprite_1,
    sprite_actor_animated_metasprite_2,
    sprite_actor_animated_metasprite_3,
    sprite_actor_animated_metasprite_4,
    sprite_actor_animated_metasprite_0,
    sprite_actor_animated_metasprite_5,
    sprite_actor_animated_metasprite_1,
    sprite_actor_animated_metasprite_6,
    sprite_actor_animated_metasprite_2,
    sprite_actor_animated_metasprite_7,
    sprite_actor_animated_metasprite_3
};

const struct animation_t sprite_actor_animated_animations[] = {
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

const UWORD sprite_actor_animated_animations_lookup[] = {
    SPRITE_1_STATE_DEFAULT
};

const struct spritesheet_t sprite_actor_animated = {
    .n_metasprites = 12,
    .emote_origin = {
        .x = 0,
        .y = -16
    },
    .metasprites = sprite_actor_animated_metasprites,
    .animations = sprite_actor_animated_animations,
    .animations_lookup = sprite_actor_animated_animations_lookup,
    .bounds = {
        .left = 0,
        .bottom = 7,
        .right = 15,
        .top = 0
    },
    .tileset = TO_FAR_PTR_T(sprite_actor_animated_tileset),
    .cgb_tileset = TO_FAR_PTR_T(sprite_actor_animated_bank2_tileset)
};
