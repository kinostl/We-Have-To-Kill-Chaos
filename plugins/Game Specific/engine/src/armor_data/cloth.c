#include "armor_data.h"
#include "class_data.h"
#pragma bank 255
#include "armor_data/cloth.h"

void cloth(struct armor_data *armor) OLDCALL BANKED {
  armor->id = 1;
  armor->type = ARMOR;
  armor->defense = 1;
  armor->weight = 2;
  armor->price = 10;

  add_fighter(armor->classes);
  add_thief(armor->classes);
  add_monk(armor->classes);

  add_red_mage(armor->classes);
  add_white_mage(armor->classes);
  add_black_mage(armor->classes);

  add_blue_mage(armor->classes);
}