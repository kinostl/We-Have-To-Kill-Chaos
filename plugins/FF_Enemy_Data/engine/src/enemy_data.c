#pragma bank 255
#include "vm.h"
#include "enemy_data.h"

BANKREF(ff_enemy_data)

const struct enemy_info enemy_db[128]={
    [IMP] = { .name = "IMP", .hp = 8, .gold = 6, .exp = 6, .damage = 4, .hits = 1, .hit_chance = 85, .status = -1, .crit_chance = 1, .absorb = 4, .evade = 3, .mdef = 8, .morale = 13, .magic = 0, .spatk = 0, .family = GIANT, .weakness = -1, .resists = -1 },
    [WOLF] = { .name = "WOLF", .hp = 20, .gold = 6, .exp = 24, .damage = 8, .hits = 1, .hit_chance = 86, .status = -1, .crit_chance = 1, .absorb = 0, .evade = 18, .mdef = 14, .morale = 13, .magic = 0, .spatk = 0, .family = NONE, .weakness = -1, .resists = -1 },
    [MADPONY] = { .name = "MADPONY", .hp = 64, .gold = 15, .exp = 63, .damage = 10, .hits = 2, .hit_chance = 92, .status = -1, .crit_chance = 1, .absorb = 2, .evade = 11, .mdef = 20, .morale = 13, .magic = 0, .spatk = 0, .family = NONE, .weakness = -1, .resists = -1 }
};