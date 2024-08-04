#pragma bank 255
#include "weapon_data.h"
#include "weapon_data/iron_hammer.h"

void iron_hammer (struct weapon_data *weapon) OLDCALL BANKED {
  weapon->id = 5;
  weapon->attack = 9;
  weapon->hit_chance = 0;
  weapon->crit_chance = 1;
  weapon->price = 10;
  weapon->classes = 0;
  weapon->color = BROWN;
  weapon->type = HAMMER;

  add_fighter(weapon->classes);
  add_white_mage(weapon->classes);
}