#include <gb/gb.h>
BANKREF(ff_enemy_data_imp)

#include "enemy_data/imp.h"
#include "enemy_data.h"
const struct enemy_info imp_data = {.name = "IMP",
                               .hp = 8,
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
                               .family = GIANT,
                               .weakness = -1,
                               .resists = -1};