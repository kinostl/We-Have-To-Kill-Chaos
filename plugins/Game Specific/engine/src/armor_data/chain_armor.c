#include "armor_data.h"
#include "class_data.h"
#pragma bank 255
#include "armor_data/chain_armor.h"

void chain_armor(struct armor_data *armor) OLDCALL BANKED {
  armor->id = 3;
  armor->type = ARMOR;
  armor->defense = 15;
  armor->weight = 15;
  armor->price = 80;

  add_fighter(armor->classes);
  add_red_mage(armor->classes);
}