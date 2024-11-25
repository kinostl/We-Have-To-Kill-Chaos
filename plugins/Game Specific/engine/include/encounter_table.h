#ifndef FF_ENCOUNTER_TABLE
#define FF_ENCOUNTER_TABLE

#include <asm/types.h>
#include <bankdata.h>
#include "enums.h"

void load_encounter(ENEMY_TYPE encounter_table[6], UBYTE world_x,
                         UBYTE world_y) BANKED;
#endif