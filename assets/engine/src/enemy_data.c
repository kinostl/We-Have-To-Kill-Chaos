#pragma bank 255
#include "vm.h" // IWYU pragma: keep
BANKREF(ff_enemy_data)

#include "enemy_data.h" // IWYU pragma: keep
#include "imp.h"
#include "mad_pony.h"
#include "wolf.h"

struct enemy_info get_enemy_data(BYTE enemy_id) {
  switch (enemy_id) {
  case IMP:
    return imp_data;
  case WOLF:
    return wolf_data;
  case MADPONY:
    return mad_pony_data;
  default:
    return imp_data;
    break;
  }
}

void setup_encounter_table(BYTE encounter_table_id,
                           struct enemy_info encounter_table[4]) {
  switch (encounter_table_id) {
  case 0:
    encounter_table[0] = get_enemy_data(IMP);
    encounter_table[1] = get_enemy_data(WOLF);
    encounter_table[2] = get_enemy_data(MADPONY);
    encounter_table[3] = get_enemy_data(MADPONY);
    return;
  default:
    encounter_table[0] = get_enemy_data(IMP);
    encounter_table[1] = get_enemy_data(IMP);
    encounter_table[2] = get_enemy_data(MADPONY);
    encounter_table[3] = get_enemy_data(MADPONY);
    return;
  }
}