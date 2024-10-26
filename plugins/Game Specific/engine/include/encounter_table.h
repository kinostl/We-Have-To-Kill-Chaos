#ifndef FF_ENCOUNTER_TABLE
#define FF_ENCOUNTER_TABLE

#include <asm/types.h>
#include <bankdata.h>
#include "entity_data.h"

void set_enemy_data(entity_data * entity, BYTE enemy_id) OLDCALL BANKED;
void set_encounter_table(BYTE encounter_table[4], BYTE encounter_table_id) OLDCALL BANKED;
#endif