#include <bankdata.h>
#include <gb/gb.h>
#include <string.h>
#include "enemy_data.h"
#include "db/enemy.h"
#include "encounter_table.h"
#include "enums.h"

#pragma bank 255


void set_enemy_data(enemy_data * entity, ENEMY_TYPE enemy_id) OLDCALL BANKED {
  memcpy(&entity, enemy_db[enemy_id], sizeof(enemy_data));
}

void set_encounter_table(ENEMY_TYPE encounter_table[4], BYTE encounter_table_id)
                        OLDCALL BANKED{
  switch (encounter_table_id) {
  case 0:
    encounter_table[0] = IMP;
    encounter_table[1] = WOLF;
    encounter_table[2] = MADPONY;
    encounter_table[3] = MADPONY;
    return;
  default:
    encounter_table[0] = IMP;
    encounter_table[1] = IMP;
    encounter_table[2] = MADPONY;
    encounter_table[3] = MADPONY;
    return;
  }
}