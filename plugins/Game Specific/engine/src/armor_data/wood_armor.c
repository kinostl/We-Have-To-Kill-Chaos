#include "armor_data.h"
#include "class_data.h"
#pragma bank 255
#include "armor_data/wood_armor.h"

void wood_armor(struct armor_data *armor) OLDCALL BANKED {
  armor->id = 2;
  armor->type = ARMOR;
  armor->defense = 4;
  armor->weight = 8;
  armor->price = 50;

  add_fighter(armor->classes);
  add_thief(armor->classes);
  add_monk(armor->classes);

  add_red_mage(armor->classes);
}