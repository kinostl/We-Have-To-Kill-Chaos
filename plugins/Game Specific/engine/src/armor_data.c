#include "armor_data.h"
#include "armor_data/naked.h"
#include "armor_data/cloth.h"
#include "armor_data/wood_armor.h"
#include "armor_data/chain_armor.h"
#include "armor_data/cap.h"
#include <asm/types.h>
#pragma bank 255

void set_armor(BYTE armor_id, struct armor_data *armor) OLDCALL BANKED {
  switch (armor_id) {
  default:
  case 0:
    naked(armor);
    break;
  case 1:
    cloth(armor);
    break;
  case 2:
    wood_armor(armor);
    break;
  case 3:
    chain_armor(armor);
    break;
  case 26:
    cap(armor);
    break;
  }
}