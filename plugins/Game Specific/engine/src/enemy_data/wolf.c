#include <gb/gb.h>
BANKREF(ff_enemy_data_wolf)

#include "enemy_data/wolf.h"
#include "enemy_data.h"
const struct enemy_info wolf_data = {.name = "WOLF",
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
                                     .weakness = -1,
                                     .resists = -1};