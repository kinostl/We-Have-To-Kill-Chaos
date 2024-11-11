#ifndef FF_ENEMY_DATA_WOLF
#define FF_ENEMY_DATA_WOLF

#include "enemy_data.h"
#include "skill_data.h"
#include <asm/types.h>
#include <gb/gb.h>

const enemy_data wolf = {
    .name = "WOLF",
    .w = 5,
    .h = 4,
    .ext =
        {
            .max_hp = 20,
            .gold = 6,
            .exp = 24,
            .damage = 8,
            .hits = 1,
            .hit_chance = 86,
            .status = -1,
            .crit_chance = 1,
            .absorb = 0,
            .evade = 18,
            .mdef = 14,
            .morale = 13,
            .magic = 0,
            .spatk = 0,
            .family = NONE,
            .type = WOLF,
            .weakness = -1,
            .resists = -1,
            .skills =
                {
                    HOWL,
                    FIGHT,
                    FIGHT,
                    FIGHT,
                },

        },
};

#endif