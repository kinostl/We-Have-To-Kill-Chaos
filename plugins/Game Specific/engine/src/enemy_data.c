#include <bankdata.h>
#include <gb/gb.h>
#include "enemy_data.h" // IWYU pragma: keep
#include "encounter_table.h"

#include "enemy_data/imp.h"
#include "enemy_data/wolf.h"
#include "enemy_data/mad_pony.h"
#include "entity_data.h"

#pragma bank 255

struct entity_data set_enemy_data(struct entity_data * entity, BYTE enemy_id) OLDCALL BANKED {
  switch (enemy_id) {
  default:
  case IMP:
    set_to_imp(entity);
    break;
  case WOLF:
    set_to_wolf(entity);
    break;
  case MADPONY:
    set_to_mad_pony(entity);
    break;
  }
}

void setup_encounter_table(BYTE encounter_table_id,
                           struct entity_data encounter_table[4]) OLDCALL BANKED{
  switch (encounter_table_id) {
  case 0:
    set_enemy_data(&encounter_table[0], IMP);
    set_enemy_data(&encounter_table[1], WOLF);
    set_enemy_data(&encounter_table[2], MADPONY);
    set_enemy_data(&encounter_table[3], MADPONY);
    return;
  default:
    set_enemy_data(&encounter_table[0], IMP);
    set_enemy_data(&encounter_table[1], IMP);
    set_enemy_data(&encounter_table[2], MADPONY);
    set_enemy_data(&encounter_table[3], MADPONY);
    return;
  }
}