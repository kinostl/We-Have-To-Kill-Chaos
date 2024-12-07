#include "enemy_data.h"
#include "enums.h"
#include <bankdata.h>
#include <gb/gb.h>

#pragma bank 255

const enemy_data enemy_db[] = {
    [EMPTY_ENEMY_SLOT] =
        {
            .name = "",
            .ext = {.status = DEAD},

        },
    [IMP] =
        {
            .name = "IMP",
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
                    .spell_chance = 0,
                    .skill_chance = 4,
                    .weakness = -1,
                    .resists = -1,
                    .family = GIANT,
                    .type = IMP,
                    .skills =
                        {
                            GOBLIN_PUNCH,
                            GOBLIN_PUNCH,
                            GOBLIN_PUNCH,
                            GOBLIN_PUNCH,
                        },
                },
        },
    [MADPONY] =
        {
            .name = "MADPONY",
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
                    .spell_chance = 0,
                    .skill_chance = 2,
                    .family = NO_ENEMY_FAMILY,
                    .type = MADPONY,
                    .weakness = -1,
                    .resists = -1,
                    .skills =
                        {
                            THRASH,
                            THRASH,
                            THRASH,
                            THRASH,
                        },
                },
        },
    [WOLF] =
        {
            .name = "WOLF",
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
                    .spell_chance = 0,
                    .skill_chance = 4,
                    .family = NO_ENEMY_FAMILY,
                    .type = WOLF,
                    .weakness = -1,
                    .resists = -1,
                    .skills =
                        {
                            HOWL,
                            HOWL,
                            HOWL,
                            HOWL,
                        },

                },
        },
};

BANKREF(FF_ENEMY_DATA)