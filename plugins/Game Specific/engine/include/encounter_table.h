#ifndef FF_ENCOUNTER_TABLE
#define FF_ENCOUNTER_TABLE

#include "entity_data.h"
#include <asm/types.h>
#include <bankdata.h>

void setup_encounter_table(BYTE encounter_table_id,
                           struct entity_data encounter_table[4]) OLDCALL BANKED;
#endif