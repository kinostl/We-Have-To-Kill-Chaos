#include "weapon_data.h"
#include "class_data.h"
#include "enums.h"
#include "menu_helper.h"
#include <asm/types.h>
#include <string.h>

#pragma bank 255

const weapon_data weapon_db[] = {
    [UNARMED] =
        {
            .id = UNARMED,
            .type = NO_WEAPON_FAMILY,
            .color = DMG,
            .attack = 0,
            .hit_chance = 0,
            .crit_chance = 0,
            .price = 0,
            .classes = ALL_JOBS,
        },
    [WOOD_NUNCHUCKS] =
        {
            .id = WOOD_NUNCHUCKS,
            .type = NUNCHUCKS,
            .color = BROWN,
            .attack = 12,
            .hit_chance = 0,
            .crit_chance = 10,
            .price = 10,
            .classes = MONK,
        },
    [SMALL_KNIFE] =
        {
            .id = SMALL_KNIFE,
            .attack = 5,
            .hit_chance = 10,
            .crit_chance = 5,
            .price = 5,
            .color = GREY,
            .type = DAGGER,
            .classes = FIGHTER | THIEF | RED_MAGE | BLACK_MAGE,
        },
    [WOOD_STAFF] =
        {

            .id = WOOD_STAFF,
            .attack = 6,
            .hit_chance = 0,
            .crit_chance = 1,
            .price = 5,
            .color = BROWN,
            .type = STAFF,
            .classes = ALL_JOBS & ~THIEF,
        },
    [RAPIER] =
        {
            .id = WOOD_STAFF,
            .attack = 9,
            .hit_chance = 5,
            .crit_chance = 10,
            .price = 10,
            .color = GREY,
            .type = SWORD_1,
            .classes = FIGHTER | THIEF | RED_MAGE,
        },
    [IRON_HAMMER] =
        {
            .id = IRON_HAMMER,
            .attack = 9,
            .hit_chance = 0,
            .crit_chance = 1,
            .price = 10,
            .color = BROWN,
            .type = HAMMER,
            .classes = FIGHTER | WHITE_MAGE,
        },
    [WERE_SWORD] =
        {
            .id = WERE_SWORD,
            // TODO WRONG STATS ONLY ID AND NAME UPDATED
            .attack = 18,
            .hit_chance = 15,
            .crit_chance = 5,
            .price = 5000,
            .color = PURPLE,
            .type = SWORD_2,
            .classes = FIGHTER | THIEF | RED_MAGE,
        },
    [RUNE_SWORD] =
        {
            .id = RUNE_SWORD,
            .attack = 18,
            .hit_chance = 15,
            .crit_chance = 5,
            .price = 6000,
            .color = PINK,
            .type = SWORD_3,
            .classes = FIGHTER | RED_MAGE,
        },
};

inline void writeItemDesc(BYTE item_id, unsigned char *item_s) {

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

void load_weapon_info_text(weapon_data w_data, unsigned char *item_s,
                           UBYTE width, UBYTE offset) OLDCALL BANKED {
  width;
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

BANKREF(FF_WEAPON_DATA)