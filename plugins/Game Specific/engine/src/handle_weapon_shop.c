#include "item_slot.h"
#include "load_font_into_bg.h"
#include "menu_helper.h"
#include "weapon_data.h"
#include "weapon_data/iron_hammer.h"
#include "weapon_data/rapier.h"
#include "weapon_data/wood_staff.h"
#include "weapon_data/small_knife.h"
#include "weapon_data/wood_nunchucks.h"
#include "extra_data.h"
#include <asm/types.h>
#include <data/game_globals.h>
#include <string.h>
#include <ui.h>
#include <vm.h>
#include "states/menu.h"
#pragma bank 255

void setWeaponData(struct weapon_data * wepon, UBYTE weapon_choice) OLDCALL BANKED{
    switch (weapon_choice) {
    case 1:
      wood_staff(wepon);
      break;
    case 2:
      small_knife(wepon);
      break;
    case 3:
      wood_nunchucks(wepon);
      break;
    case 4:
      rapier(wepon);
      break;
    case 5:
      iron_hammer(wepon);
      break;
    default:
      break;
    }
}

void handleWeaponShop(SCRIPT_CTX * THIS) OLDCALL BANKED {
    UBYTE weapon_choice = *(UBYTE *) VM_REF_TO_PTR(FN_ARG0);

    struct weapon_data wepon;
    setWeaponData(&wepon, weapon_choice);

    // Set Weapon Data

    VM_GLOBAL(VAR_1WEAPON_TYPE) = wepon.type;
    VM_GLOBAL(VAR_1WEAPON_COLORS) = wepon.color;

    unsigned char *d = ui_text_data;
    UBYTE weapon_info[18 * 8] = "";
    strcpy(d, "");
    load_weapon_info_text(wepon, weapon_info, 18, 0);
    strcpy(d, weapon_info);
    strcat(d, "\nPay ");
    unsigned char * price_str[4];
    itoa_format(wepon.price, price_str, 0);
    strcat(d, price_str);
    strcat(d, "G?");
}

void purchaseWeaponToInventory(SCRIPT_CTX * THIS) OLDCALL BANKED {
    UBYTE weapon_choice = *(UBYTE *) VM_REF_TO_PTR(FN_ARG0);

    struct weapon_data wepon;
    setWeaponData(&wepon, weapon_choice);
    addWeaponItem(wepon.id);
    VM_GLOBAL(VAR_1_C) = weapon_choice;
    VM_GLOBAL(VAR_2_C) = wepon.id;
    VM_GLOBAL(VAR_3_C) = wepon.price;

    strcpy(ui_text_data, "You pay ");
    unsigned char * price_str[4];
    itoa_format(wepon.price, price_str, 0);
    strcat(ui_text_data, price_str);
    strcat(ui_text_data, "G.");
}

void addShopStat(UBYTE a) OLDCALL BANKED {
  unsigned char a_str[4];
  itoa_format(a, a_str, 3);

  strcat(ui_text_data, "  ");
  strcat(ui_text_data, a_str);
  strcat(ui_text_data, "\n");
}

void loadWeaponShopArea(SCRIPT_CTX *THIS) OLDCALL BANKED {
  THIS;
  UBYTE check_id = *(UBYTE *)VM_REF_TO_PTR(FN_ARG0);
  struct weapon_data w_data;

//   set_weapon(menu_slots[check_id].id, &check_w);
  set_weapon(check_id, &w_data);

  strcpy(ui_text_data, "ATK\n");
  addShopStat(w_data.attack);

  strcat(ui_text_data, "\nACC\n");
  addShopStat(w_data.hit_chance);

  strcat(ui_text_data, "\nCRT\n");
  addShopStat(w_data.crit_chance);

  write_bg_font(1, 9, 5, 8);
}

void loadWeaponShopWeapons(void) OLDCALL BANKED {
  strcpy(ui_text_data, "");
  unsigned char location[4] = {0x03, 18, 4, '\0'};
  unsigned char *price_str[4];
  struct weapon_data w_data;

  for (int i = 0; i < 5; i++) {
    weapon_name_short_cat(i + 1, ui_text_data);
    location[2]++;
    strcat(ui_text_data, location);
    set_weapon(i + 1, &w_data);
    itoa_format(w_data.price, price_str, 0);
    strcat(ui_text_data, price_str);
    strcat(ui_text_data, "\n");
  }

  fs_menu_write_bg_font(8, 4, 11, 5);
}