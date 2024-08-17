#include "extra_data.h"
#include "item_slot.h"
#include "menu_helper.h"
#include <asm/types.h>
#include <gb/gb.h>
#include <gbs_types.h>
#include <string.h>
#include <ui.h>
#include <vm.h>
#include <bankdata.h>
#include "data/game_globals.h"
#include "weapon_data.h"
#include "load_font_into_bg.h"
#pragma bank 255

inline void draw_amt(unsigned char *d, UBYTE i){
  unsigned char a[3];
  itoa_format(item_slots[i].count, a, 0);

  UBYTE rem = 20 - (strlen(d) % 20);
  rem -= strlen(a);
  rem--;

  progress_blanks(d, rem);
  strcat(d, a);
  progress_blanks(d, 1);
}

inline void write_weapon_name(BYTE weapon_id, unsigned char *weapon_s) {
  // TODO should display item type symbol then name
  // Also should make so and so wide
  // Max Count is 99 I guess
  switch (weapon_id) {
  default:
    break;
  case 1:
    add_weapon_sym(weapon_s, NUNCHUCKS);
    strcat(weapon_s, "WOOD NUNCHAKU");
    break;
  case 2:
    add_weapon_sym(weapon_s, DAGGER);
    strcat(weapon_s, "SMALL DAGGER");
    break;
  case 3:
    add_weapon_sym(weapon_s, STAFF);
    strcat(weapon_s, "WOOD ROD");
    break;
  case 4:
    add_weapon_sym(weapon_s, SWORD_1);
    strcat(weapon_s, "RAPIER");
    break;
  }
}

void drawMenu(SCRIPT_CTX *THIS) OLDCALL BANKED {
  THIS;
  UBYTE header[18] = "";

  // Item Header
  strcpy(header, "Items 1/1");
  add_new_line(header, 20);
  header[strlen(header) - 4] = '#';
  for (UBYTE i = 0; i<strlen(header); i++) {
    UBYTE t = header[i];
    header[i] = ReadBankedUBYTE(bg_font.recode_table + t, bg_font_bank);
    header[i] += start_of_bkg_vram;
  }
  set_bkg_tiles(2, 0, 17, 1, header);

  if(item_slots[0].type == NULL){
    VM_GLOBAL(VAR_TEMP_FRAME) = 0;
    return;
  }

  VM_GLOBAL(VAR_TEMP_FRAME) = 9;


  // Item List
  UBYTE menu[20 * 10] = "";
  for (BYTE i = 0; i < 10; i++) {
    if (item_slots[i].type == NULL) {
      VM_GLOBAL(VAR_TEMP_FRAME) = i - 1;
      break;
    }
    progress_blanks(menu, 3);
    write_weapon_name(item_slots[i].id, menu);
    draw_amt(menu, i);
  }
  for (UBYTE i = 0; i<(20*10); i++) {
    UBYTE t = menu[i];
    menu[i] = ReadBankedUBYTE(bg_font.recode_table + t, bg_font_bank);
    menu[i] += start_of_bkg_vram;
  }
  set_bkg_tiles(0, 2, 20, 10, menu);
}


void drawItemInfoBox(SCRIPT_CTX * THIS) OLDCALL BANKED {
  THIS;
  make_box(0, 12, 20,6);
}


void loadWeaponInfo(SCRIPT_CTX *THIS) OLDCALL BANKED {
  THIS;
  if(item_slots[0].type == NULL){
    strcpy(ui_text_data, "You have no items.");
    write_bg_font(1, 13, 18, 4);
    return;
  }
  UWORD item_idx = VM_GLOBAL(VAR_TEMP_Y);
  strcpy(ui_text_data, "");


  struct item_slot i_slot;
  i_slot = item_slots[item_idx];

  struct weapon_data w_data;
  set_weapon(i_slot.id, &w_data);

  load_weapon_info_text(w_data, ui_text_data, 18, 5);
  write_bg_font(1, 13, 18, 4);
}