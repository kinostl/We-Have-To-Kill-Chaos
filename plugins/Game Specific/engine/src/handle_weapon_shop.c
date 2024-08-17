#include "item_slot.h"
#include "menu_helper.h"
#include "weapon_data.h"
#include "weapon_data/iron_hammer.h"
#include "weapon_data/rapier.h"
#include "weapon_data/wood_staff.h"
#include "weapon_data/small_knife.h"
#include "weapon_data/wood_nunchucks.h"
#include <asm/types.h>
#include <data/game_globals.h>
#include <string.h>
#include <ui.h>
#include <vm.h>
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