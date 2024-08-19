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

void weapon_name_short_cat(BYTE item_id, unsigned char *item_s) OLDCALL BANKED{
  // TODO should display item type symbol then name
  // Also should make so and so wide
  // Max Count is 99 I guess
  switch (item_id) {
  default:
  case 0:
    add_weapon_sym(item_s, SWORD_1);
    strcat(item_s, " ");
    break;
  case 1:
    add_weapon_sym(item_s, NUNCHUCKS);
    strcat(item_s, "WOOD");
    break;
  case 2:
    add_weapon_sym(item_s, DAGGER);
    strcat(item_s, "SMALL");
    break;
  case 3:
    add_weapon_sym(item_s, STAFF);
    strcat(item_s, "WOOD");
    break;
  case 4:
    add_weapon_sym(item_s, SWORD_1);
    strcat(item_s, "RAPIER");
    break;
  case 5:
    add_weapon_sym(item_s, HAMMER);
    strcat(item_s, "IRON");
    break;
  }
}

void armor_name_short_cat(BYTE item_id, enum A_TYPE type,unsigned char *item_s) OLDCALL BANKED{
  // TODO should display item type symbol then name
  // Also should make so and so wide
  // Max Count is 99 I guess
  switch (item_id) {
  default:
    add_armor_sym(item_s, type);
    strcat(item_s, " ");
    break;
  case 1:
    add_armor_sym(item_s, ROBE);
    strcat(item_s, "CLOTH");
    break;
  case 2:
    add_armor_sym(item_s, ARMOR);
    strcat(item_s, "WOOD");
    break;
  case 3:
    add_armor_sym(item_s, ARMOR);
    strcat(item_s, "CHAIN");
    break;
  case 26:
    add_armor_sym(item_s, HELMET);
    strcat(item_s, "CAP");
    break;
  }
}