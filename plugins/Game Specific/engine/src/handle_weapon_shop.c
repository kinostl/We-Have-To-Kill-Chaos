#include "class_data.h"
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
#include <macro.h>
#include <string.h>
#include <ui.h>
#include <vm.h>
#include "states/menu.h"
#pragma bank 255

void setWeaponData(weapon_data * wepon, UBYTE weapon_choice) OLDCALL BANKED{
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

    weapon_data wepon;
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

    weapon_data wepon;
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
  BOOLEAN instant = *(BOOLEAN *)VM_REF_TO_PTR(FN_ARG1);
  BOOLEAN clear_area = *(BOOLEAN *)VM_REF_TO_PTR(FN_ARG2);
  weapon_data w_data;

//   set_weapon(menu_slots[check_id].id, &check_w);
  set_weapon(check_id, &w_data);

  strcpy(ui_text_data, "ATK\n");
  addShopStat(w_data.attack);

  strcat(ui_text_data, "\nACC\n");
  addShopStat(w_data.hit_chance);

  strcat(ui_text_data, "\nCRT\n");
  addShopStat(w_data.crit_chance);

  fs_menu_write_bg_font(1, 9, 5, 8, instant, clear_area);
}

void loadWeaponShopWeapons(SCRIPT_CTX * THIS) OLDCALL BANKED {
  BOOLEAN instant = *(BOOLEAN *)VM_REF_TO_PTR(FN_ARG0);
  BOOLEAN clear_area = *(BOOLEAN *)VM_REF_TO_PTR(FN_ARG1);
  strcpy(ui_text_data, "");
  unsigned char location[4] = {0x03, 18, 4, '\0'};
  unsigned char *price_str[4];
  weapon_data w_data;

  for (int i = 0; i < 5; i++) {
    weapon_name_short_cat(i + 1, ui_text_data);
    location[2]++;
    strcat(ui_text_data, location);
    set_weapon(i + 1, &w_data);
    itoa_format(w_data.price, price_str, 0);
    strcat(ui_text_data, price_str);
    strcat(ui_text_data, "\n");
  }

  fs_menu_write_bg_font(8, 4, 11, 5, instant, clear_area);
}

void loadWeaponShopUsages(SCRIPT_CTX * THIS) OLDCALL BANKED {
  THIS;
  UBYTE check_id = *(UBYTE *)VM_REF_TO_PTR(FN_ARG0);
  weapon_data w_data;
  set_weapon(check_id, &w_data);
  BYTE w_total = w_data.attack + w_data.crit_chance + w_data.hit_chance;

  if(CHK_FLAG(w_data.classes, BLACK_MAGE)){
    write_bg_char(8, 12, '+');

    if (w_total > 20) {
      write_bg_char(9, 12, '>');
    } else if (w_total < 20) {
      write_bg_char(9, 12, '<');
    } else {
      write_bg_char(9, 12, '=');
    }

  }else{
    write_bg_char(8, 12, '-');
    write_bg_char(9, 12, ' ');
  }

  if (CHK_FLAG(w_data.classes, FIGHTER)) {
    write_bg_char(13, 12, '+');

    if (w_total > 24) {
      write_bg_char(14, 12, '>');
    } else if (w_total < 24) {
      write_bg_char(14, 12, '<');
    } else {
      write_bg_char(14, 12, '=');
    }

  } else {
    write_bg_char(13, 12, '-');
    write_bg_char(14, 12, ' ');
  }

  if (CHK_FLAG(w_data.classes, MONK)) {
    write_bg_char(8, 15, '+');

    if (w_total > 22) {
      write_bg_char(9, 15, '>');
    } else if (w_total < 22) {
      write_bg_char(9, 15, '<');
    } else {
      write_bg_char(9, 15, '=');
    }

  } else {
    write_bg_char(8, 15, '-');
    write_bg_char(9, 15, ' ');
  }

  if(CHK_FLAG(w_data.classes, RED_MAGE)){
    write_bg_char(13, 15, '+');

    if (w_total > 7) {
      write_bg_char(14, 15, '>');
    } else if (w_total < 7) {
      write_bg_char(14, 15, '<');
    } else {
      write_bg_char(14, 15, '=');
    }

  }else{
    write_bg_char(13, 15, '-');
    write_bg_char(14, 15, ' ');
  }

}