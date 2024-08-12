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
#pragma bank 255

void set_weapon(BYTE weapon_id, struct weapon_data *weapon) OLDCALL BANKED {
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