#pragma bank 255
#include "weapon_data.h"
#include "weapon_data/wood_nunchucks.h"

void wood_nunchucks(struct weapon_data *weapon) OLDCALL BANKED {
  weapon->id = 1;
  weapon->attack = 12;
  weapon->hit_chance = 0;
  weapon->crit_chance = 10;
  weapon->price = 10;
  weapon->classes = 0;
  weapon->color = BROWN;
  weapon->type = NUNCHUCKS;

  add_monk(weapon->classes);
}