#include "armor_data.h"
#include "class_data.h"
#pragma bank 255
#include "armor_data/cap.h"

void cap(armor_data *armor) OLDCALL BANKED {
  armor->id = 26;
  armor->type = HELMET;
  armor->defense = 1;
  armor->weight = 1;
  armor->price = 80;

  add_fighter(armor->classes);
  add_thief(armor->classes);
  add_monk(armor->classes);

  add_red_mage(armor->classes);
  add_white_mage(armor->classes);
  add_black_mage(armor->classes);

  add_blue_mage(armor->classes);
}