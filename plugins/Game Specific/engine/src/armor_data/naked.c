#include "armor_data.h"
#include "class_data.h"
#pragma bank 255
#include "armor_data/naked.h"

void naked(armor_data *armor) OLDCALL BANKED {
  armor->id = 0;
  armor->type = UNARMORED;
  armor->defense = 0;
  armor->weight = 0;
  armor->price = 0;

  add_fighter(armor->classes);
  add_thief(armor->classes);
  add_monk(armor->classes);

  add_red_mage(armor->classes);
  add_white_mage(armor->classes);
  add_black_mage(armor->classes);

  add_blue_mage(armor->classes);
}