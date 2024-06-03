#pragma bank 255

// Scene: Corneria Battles
// Actors

#include "gbs_types.h"
#include "data/sprite_characters_warrior.h"

BANKREF(scene_3_actors)

const struct actor_t scene_3_actors[] = {
    {
        // Actor 1,
        .pos = {
            .x = 112 * 16,
            .y = 56 * 16
        },
        .bounds = {
            .left = 0,
            .bottom = 7,
            .right = 15,
            .top = -8
        },
        .dir = DIR_DOWN,
        .sprite = TO_FAR_PTR_T(sprite_characters_warrior),
        .move_speed = 16,
        .anim_tick = 15,
        .pinned = FALSE,
        .persistent = FALSE,
        .collision_group = COLLISION_GROUP_NONE,
        .collision_enabled = TRUE,
        .reserve_tiles = 0
    }
};
