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

inline void write_weapon_name(BYTE item_id, unsigned char *item_s) {
  // TODO should display item type symbol then name
  // Also should make so and so wide
  // Max Count is 99 I guess
  switch (item_id) {
  default:
    break;
  case 1:
    add_item_sym(item_s, 2);
    strcat(item_s, "WOOD NUNCHAKU");
    break;
  case 2:
    add_item_sym(item_s, 0);
    strcat(item_s, "SMALL DAGGER");
    break;
  case 3:
    add_item_sym(item_s, 3);
    strcat(item_s, "WOOD ROD");
    break;
  case 4:
    add_item_sym(item_s, 4);
    strcat(item_s, "RAPIER");
    break;
  }
}

void drawMenu(SCRIPT_CTX *THIS) OLDCALL BANKED {
  THIS;
  UBYTE header[18] = "";
  // Staged data
  item_slots[0].count=1;
  item_slots[0].type=1;
  item_slots[1].count=1;
  item_slots[1].type=2;
  item_slots[2].count=1;
  item_slots[2].type=3;
  item_slots[3].count=1;
  item_slots[3].type=4;

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
    write_weapon_name(item_slots[i].type, menu);
    draw_amt(menu, item_slots[i].count);
  }
  for (UBYTE i = 0; i<(20*10); i++) {
    UBYTE t = menu[i];
    menu[i] = ReadBankedUBYTE(bg_font.recode_table + t, bg_font_bank);
    menu[i] += start_of_bkg_vram;
  }
  set_bkg_tiles(0, 2, 20, 10, menu);
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

void drawItemInfoBox(SCRIPT_CTX * THIS) OLDCALL BANKED {
  THIS;
  make_box(0, 12, 20,6);
}

void loadWeaponInfo(SCRIPT_CTX *THIS) OLDCALL BANKED {
  THIS;
  UBYTE menu[18 * 8] = "";
  UWORD item_idx = VM_GLOBAL(VAR_TEMP_Y);

  struct item_slot i_slot;
  i_slot = item_slots[item_idx];
  struct weapon_data w_data;
  set_weapon(i_slot.type, &w_data);
  writeItemDesc(w_data.id, menu);
  add_new_line(menu, 18);
  progress_blanks(menu, 5);
  strcat(menu, "Atk : ");
  unsigned char t[4];
  itoa_format(w_data.attack, t, 3);
  strcat(menu, t);

  add_new_line(menu, 18);
  progress_blanks(menu, 5);
  strcat(menu, "Hit : ");
  itoa_format(w_data.hit_chance, t, 3);
  strcat(menu, t);
  strcat(menu, "%");

  add_new_line(menu, 18);
  progress_blanks(menu, 5);
  strcat(menu, "Crit: ");
  itoa_format(w_data.crit_chance, t, 3);
  strcat(menu, t);
  strcat(menu, "%");

  for (UBYTE i = 0; i<(20*8); i++) {
    UBYTE j = menu[i];
    menu[i] = ReadBankedUBYTE(bg_font.recode_table + j, bg_font_bank);
    menu[i] += start_of_bkg_vram;
  }

  set_bkg_tiles(1, 13, 18, 4, menu);
}