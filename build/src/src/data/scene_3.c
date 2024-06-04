#pragma bank 255

// Scene: Corneria Battles

#include "gbs_types.h"
#include "data/bg_battle_concept.h"
#include "data/scene_3_collisions.h"
#include "data/palette_1.h"
#include "data/palette_3.h"
#include "data/sprite_handcursor.h"
#include "data/scene_3_actors.h"
#include "data/scene_3_triggers.h"
#include "data/scene_3_sprites.h"
#include "data/scene_3_init.h"

BANKREF(scene_3)

const struct scene_t scene_3 = {
    .width = 32,
    .height = 32,
    .type = SCENE_TYPE_TOPDOWN,
    .background = TO_FAR_PTR_T(bg_battle_concept),
    .collisions = TO_FAR_PTR_T(scene_3_collisions),
    .parallax_rows = {
        PARALLAX_STEP(0,0,0)
    },
    .palette = TO_FAR_PTR_T(palette_1),
    .sprite_palette = TO_FAR_PTR_T(palette_3),
    .reserve_tiles = 0,
    .player_sprite = TO_FAR_PTR_T(sprite_handcursor),
    .n_actors = 1,
    .n_triggers = 10,
    .n_sprites = 1,
    .n_projectiles = 0,
    .actors = TO_FAR_PTR_T(scene_3_actors),
    .triggers = TO_FAR_PTR_T(scene_3_triggers),
    .sprites = TO_FAR_PTR_T(scene_3_sprites),
    .script_init = TO_FAR_PTR_T(scene_3_init)
};
