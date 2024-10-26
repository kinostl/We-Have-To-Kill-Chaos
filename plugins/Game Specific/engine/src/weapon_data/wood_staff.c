#pragma bank 255
#include "weapon_data.h"
#include "weapon_data/wood_staff.h"

void wood_staff(weapon_data *weapon) OLDCALL BANKED {
  weapon->id = 3;
  weapon->attack = 6;
  weapon->hit_chance = 0;
  weapon->crit_chance = 1;
  weapon->price = 5;
  weapon->classes = 0;
  weapon->color = BROWN;
  weapon->type = STAFF;

  add_fighter(weapon->classes);
  add_monk(weapon->classes);
  add_red_mage(weapon->classes);
  add_white_mage(weapon->classes);
  add_black_mage(weapon->classes);
  add_blue_mage(weapon->classes);
}