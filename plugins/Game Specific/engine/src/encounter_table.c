#include "encounter_table.h"
#include "enums.h"
#include <bankdata.h>
#include <gb/gb.h>

#pragma bank 255

void set_encounter_table(ENEMY_TYPE encounter_table[4],
                         BYTE encounter_table_id) BANKED {
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