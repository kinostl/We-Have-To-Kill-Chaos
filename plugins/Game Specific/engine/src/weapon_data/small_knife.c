#pragma bank 255
#include "weapon_data.h"
#include "weapon_data/small_knife.h"

void small_knife (weapon_data *weapon) OLDCALL BANKED {
  weapon->id = 2;
  weapon->attack = 5;
  weapon->hit_chance = 10;
  weapon->crit_chance = 5;
  weapon->price = 5;
  weapon->classes = 0;
  weapon->color = GREY;
  weapon->type = DAGGER;

  add_fighter(weapon->classes);
  add_thief(weapon->classes);
  add_red_mage(weapon->classes);
  add_black_mage(weapon->classes);
}