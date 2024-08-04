#pragma bank 255
#include "weapon_data.h"
#include "weapon_data/were_sword.h"

void were_sword (struct weapon_data *weapon) OLDCALL BANKED {
  weapon->id = 26;
  weapon->attack = 18;
  weapon->hit_chance = 15;
  weapon->crit_chance = 5;
  weapon->price = 6000;
  weapon->classes = 0;
  weapon->color = PINK;
  weapon->type = SWORD_3;

  add_fighter(weapon->classes);
  add_red_mage(weapon->classes);
}