#pragma bank 255

// Scene: Overworld

#include "gbs_types.h"
#include "data/bg_overworld.h"
#include "data/scene_1_collisions.h"
#include "data/palette_0.h"
#include "data/palette_2.h"
#include "data/sprite_warriors_of_light.h"
#include "data/scene_1_init.h"

BANKREF(scene_1)

const struct scene_t scene_1 = {
    .width = 87,
    .height = 106,
    .type = SCENE_TYPE_TOPDOWN,
    .background = TO_FAR_PTR_T(bg_overworld),
    .collisions = TO_FAR_PTR_T(scene_1_collisions),
    .parallax_rows = {
        PARALLAX_STEP(0,0,0)
    },
    .palette = TO_FAR_PTR_T(palette_0),
    .sprite_palette = TO_FAR_PTR_T(palette_2),
    .reserve_tiles = 0,
    .player_sprite = TO_FAR_PTR_T(sprite_warriors_of_light),
    .n_actors = 0,
    .n_triggers = 0,
    .n_sprites = 0,
    .n_projectiles = 0,
    .script_init = TO_FAR_PTR_T(scene_1_init)
};
