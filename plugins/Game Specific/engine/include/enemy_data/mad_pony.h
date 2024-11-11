#ifndef FF_ENEMY_DATA_MAD_PONY
#define FF_ENEMY_DATA_MAD_PONY

#include "enemy_data.h"
#include "skill_data.h"
#include <asm/types.h>
#include <gb/gb.h>

const enemy_data mad_pony = {
    .name = "MADPONY",
    .w = 6,
    .h = 6,
    .ext =
        {
            .max_hp = 64,
            .gold = 15,
            .exp = 63,
            .damage = 10,
            .hits = 2,
            .hit_chance = 92,
            .status = -1,
            .crit_chance = 1,
            .absorb = 2,
            .evade = 11,
            .mdef = 20,
            .morale = 13,
            .magic = 0,
            .spatk = 0,
            .family = NONE,
            .type = MADPONY,
            .weakness = -1,
            .resists = -1,
            .skills =
                {
                    THRASH,
                    FIGHT,
                    FIGHT,
                    FIGHT,
                },
        },
};

#endif