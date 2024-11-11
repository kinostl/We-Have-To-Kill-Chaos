#ifndef FF_ENEMY_DATA_IMP
#define FF_ENEMY_DATA_IMP

#include "enemy_data.h"
#include <asm/types.h>
#include <gb/gb.h>

const enemy_data imp = {
    .name = "IMP",
    .w = 5,
    .h = 4,
    .ext =
        {
            .max_hp = 8,
            .gold = 6,
            .exp = 6,
            .damage = 4,
            .hits = 1,
            .hit_chance = 85,
            .status = -1,
            .crit_chance = 1,
            .absorb = 4,
            .evade = 3,
            .mdef = 8,
            .morale = 13,
            .magic = 0,
            .spatk = 0,
            .weakness = -1,
            .resists = -1,
            .family = GIANT,
            .type = IMP,
            .skills =
                {
                    GOBLIN_PUNCH,
                    FIGHT,
                    FIGHT,
                    FIGHT,
                },
        },
};

#endif