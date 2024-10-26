#pragma bank 255
#include "weapon_data.h"
#include "weapon_data/rune_sword.h"

void rune_sword (weapon_data *weapon) OLDCALL BANKED {
  weapon->id = 27;
  //TODO WRONG STATS ONLY ID AND NAME UPDATED
  weapon->attack = 18;
  weapon->hit_chance = 15;
  weapon->crit_chance = 5;
  weapon->price = 5000;
  weapon->classes = 0;
  weapon->color = PURPLE;
  weapon->type = SWORD_2;

  add_fighter(weapon->classes);
  add_thief(weapon->classes);
  add_red_mage(weapon->classes);
}