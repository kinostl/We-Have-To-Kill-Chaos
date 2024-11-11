#include "enemy_data.h"
#include "enums.h"
#include <string.h>

#pragma bank 255

const enemy_data enemy_db[] = {
    [IMP] =
        {
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
        },
    [MADPONY] =
        {
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
                    .family = NO_ENEMY_FAMILY,
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
        },
    [WOLF] =
        {
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
                    .family = NO_ENEMY_FAMILY,
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
        },
};

void load_enemy(enemy_data *enemy, ENEMY_TYPE enemy_id) BANKED {
  memcpy(&enemy, &enemy_db[enemy_id], sizeof(enemy_data));
}