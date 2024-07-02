#pragma bank 255
#include <bankdata.h>
#include <gb/gb.h>
#include "enemy_data.h" // IWYU pragma: keep

#include "enemy_data/imp.h"
#include "enemy_data/wolf.h"
#include "enemy_data/mad_pony.h"

BANKREF(ff_enemy_data)



struct entity_data get_enemy_data(BYTE enemy_id) OLDCALL BANKED{
  struct entity_data res;
  switch (enemy_id) {
  default:
  case IMP:
    MemcpyBanked(&res, &imp_data, sizeof(res), BANK(ff_enemy_data_imp));
    break;
  case WOLF:
    MemcpyBanked(&res, &wolf_data, sizeof(res), BANK(ff_enemy_data_wolf));
    break;
  case MADPONY:
    MemcpyBanked(&res, &mad_pony_data, sizeof(res), BANK(ff_enemy_data_mad_pony));
    break;
  }
  return res;
}

void setup_encounter_table(BYTE encounter_table_id,
                           struct entity_data encounter_table[4]) OLDCALL BANKED{
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