#ifndef FF_ENEMY_DATA
#define FF_ENEMY_DATA
#include <asm/types.h>
#include <gb/gb.h>

BANKREF_EXTERN(ff_enemy_data)
#include "entity_data.h"

enum enemy_family {
    NONE,
    GIANT
};

enum enemy_name {
    IMP,
    GrIMP,
    WOLF,
    MADPONY
};

void setup_encounter_table(BYTE encounter_table_id,
                           struct entity_data encounter_table[4]) OLDCALL BANKED;
#endif