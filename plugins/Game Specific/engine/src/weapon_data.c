#include "weapon_data.h"
#include "weapon_data/iron_hammer.h"
#include "weapon_data/rapier.h"
#include "weapon_data/rune_sword.h"
#include "weapon_data/small_knife.h"
#include "weapon_data/were_sword.h"
#include "weapon_data/wood_nunchucks.h"
#include "weapon_data/wood_staff.h"
#include "weapon_data/unarmed.h"
#include <asm/types.h>
#include <string.h>
#include "menu_helper.h"

#pragma bank 255


void set_weapon(BYTE weapon_id, struct weapon_data *weapon) OLDCALL BANKED {
  unarmed(weapon);
  weapon->classes=0;

  switch (weapon_id) {
  default:
  case 0:
    // If not monk
    // Unarmed
    // else
    // Fists
    unarmed(weapon);
    break;
  case 1:
    wood_nunchucks(weapon);
    break;
  case 2:
    small_knife(weapon);
    break;
  case 3:
    wood_staff(weapon);
    break;
  case 4:
    rapier(weapon);
    break;
  case 5:
    iron_hammer(weapon);
    break;
  case 26:
    were_sword(weapon);
    break;
  case 27:
    rune_sword(weapon);
    break;
  }
}

inline void writeItemDesc(BYTE item_id, unsigned char *item_s){

  switch (item_id) {
  default:
  case 0:
    strcat(item_s, "");
    break;
  case 1:
    strcat(item_s, "Wooden Nunchucks");
    break;
  case 2:
    strcat(item_s, "Small Dagger");
    break;
  case 3:
    strcat(item_s, "Wood Rod");
    break;
  case 4:
    strcat(item_s, "Rapier");
    break;
  }
}

void load_weapon_info_text(struct weapon_data w_data, unsigned char * item_s, UBYTE width, UBYTE offset) OLDCALL BANKED {
  unsigned char t[4];

  writeItemDesc(w_data.id, item_s);
  strcat(item_s, "\n");
  progress_blanks(item_s, offset);
  strcat(item_s, "Atk : ");

  itoa_format(w_data.attack, t, 3);
  strcat(item_s, t);

  strcat(item_s, "\n");
  progress_blanks(item_s, offset);
  strcat(item_s, "Hit : ");
  itoa_format(w_data.hit_chance, t, 3);
  strcat(item_s, t);
  strcat(item_s, "%");

  strcat(item_s, "\n");
  progress_blanks(item_s, offset);
  strcat(item_s, "Crit: ");
  itoa_format(w_data.crit_chance, t, 3);
  strcat(item_s, t);
  strcat(item_s, "%");

}