#include <asm/types.h>
#include <ui.h>
#pragma bank 255
#include "armor_data.h"
#include "weapon_data.h"
#include "menu_helper.h"

void add_armor_sym(unsigned char *d, enum A_TYPE sym_id) OLDCALL BANKED {
  unsigned char sym_base = 144;
  switch (sym_id) {
  case ARMOR:
    break;
  case SHIELD:
    sym_base += 1;
    break;
  case HELMET:
    sym_base += 2;
    break;
  case GAUNTLET:
    sym_base += 3;
    break;
  case BRACELET:
    sym_base += 4;
    break;
  case ROBE:
    sym_base += 5;
    break;
  default:
    sym_base = ' ';
    break;
  }
  const unsigned char sym[2] = {sym_base, '\0'};
  strcat(d, sym);
}

void add_weapon_sym(unsigned char *d, enum W_TYPE sym_id) OLDCALL BANKED {
  unsigned char sym_base = 137;
  switch (sym_id) {
  case SWORD_1:
  case SWORD_2:
  case SWORD_3:
    break;
  case HAMMER:
    sym_base += 1;
    break;
  case DAGGER:
    sym_base += 2;
    break;
  // case AXE:
  // sym_base+=3;
  // break;
  case STAFF:
    sym_base += 4;
    break;
  case NUNCHUCKS:
    sym_base += 5;
    break;
  default:
    sym_base = ' ';
    break;
  }
  const unsigned char sym[2] = {sym_base, '\0'};
  strcat(d, sym);
}
