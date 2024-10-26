#pragma bank 255
#include "weapon_data.h"
#include "weapon_data/rapier.h"

void rapier (weapon_data *weapon) OLDCALL BANKED {
  weapon->id = 4;
  weapon->attack = 9;
  weapon->hit_chance = 5;
  weapon->crit_chance = 10;
  weapon->price = 10;
  weapon->classes = 0;
  weapon->color = GREY;
  weapon->type = SWORD_1;

  add_fighter(weapon->classes);
  add_thief(weapon->classes);
  add_red_mage(weapon->classes);
}