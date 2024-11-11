#ifndef FF_ENCOUNTER_TABLE
#define FF_ENCOUNTER_TABLE

#include <asm/types.h>
#include <bankdata.h>
#include "enums.h"

void set_encounter_table(ENEMY_TYPE encounter_table[4], BYTE encounter_table_id) BANKED;
void setupEnemySlots(void) BANKED;
#endif