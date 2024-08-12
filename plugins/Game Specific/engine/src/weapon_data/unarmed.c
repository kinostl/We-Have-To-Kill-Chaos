#pragma bank 255
#include "weapon_data.h"
#include "weapon_data/unarmed.h"

void unarmed(struct weapon_data *weapon) OLDCALL BANKED {
  weapon->id = 0;
  weapon->attack = 0;
  weapon->hit_chance = 0;
  weapon->crit_chance = 0;
  weapon->price = 0;
  weapon->classes = 0;
  weapon->color = DMG;
  weapon->type = UNARMED;

  add_fighter(weapon->classes);
  add_thief(weapon->classes);
  add_monk(weapon->classes);

  add_red_mage(weapon->classes);
  add_white_mage(weapon->classes);
  add_black_mage(weapon->classes);

  add_blue_mage(weapon->classes);
}