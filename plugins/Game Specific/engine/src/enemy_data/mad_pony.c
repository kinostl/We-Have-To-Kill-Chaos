#include "entity_data.h"
#include <gb/gb.h>
BANKREF(ff_enemy_data_mad_pony)
#include "enemy_data/mad_pony.h"
#include "enemy_data.h"

#pragma bank 255

const struct entity_data mad_pony_data = {.name = "MADPONY",
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
                                   .resists = -1};