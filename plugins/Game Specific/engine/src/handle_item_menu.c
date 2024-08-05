#include "extra_data.h"
#include "menu_helper.h"
#include <asm/types.h>
#include <gb/gb.h>
#include <gbs_types.h>
#include <string.h>
#include <ui.h>
#include <vm.h>
#include "data/font_gbs_mono.h"
#include "data/bg_inventory_tileset.h"
#include <bankdata.h>
#include "data/game_globals.h"
#pragma bank 255

UBYTE start_of_bkg_vram;
font_desc_t _font;

inline void add_item_sym(unsigned char *d, BYTE sym) {
  *d = '~' + 2 + sym;
}

UBYTE write_item_name(BYTE item_id, unsigned char *d) OLDCALL BANKED {
  // TODO should display item type symbol then name
  // Also should make so and so wide
  // Max Count is 99 I guess
  char item_s[15] = "";
  switch (item_id) {
  default:
    break;
  case 1:
    add_item_sym(d++, 2);
    strcat(item_s, "WOOD NUNCHAKU");
    break;
  case 2:
    add_item_sym(d++, 0);
    strcat(item_s, "SMALL DAGGER");
    break;
  case 3:
    add_item_sym(d++, 3);
    strcat(item_s, "WOOD ROD");
    break;
  case 4:
    add_item_sym(d++, 4);
    strcat(item_s, "RAPIER");
    break;
  }
  BYTE item_len = strlen(item_s);
  for (BYTE i = 0; i < item_len; i++) {
    *d++ = item_s[i];
  }
  return item_len+1;
}

void loadItemMenu(SCRIPT_CTX *THIS) OLDCALL BANKED {
  THIS;
  unsigned char *d = ui_text_data;
  for (BYTE i = 0; i < 4; i++) {
    d += write_item_name(item_slots[i].type, d);
    *d++ = '\n';
  }
  *d++ = '\0';
}

void drawMenu(SCRIPT_CTX *THIS) OLDCALL BANKED {
  THIS;
  UBYTE menu[20 * 18] = {' '};
  item_slots[0].count=1;
  item_slots[0].type=1;
  item_slots[1].count=1;
  item_slots[1].type=2;
  item_slots[2].count=1;
  item_slots[2].type=3;
  item_slots[3].count=1;
  item_slots[3].type=4;
  UBYTE s_i=0;
  const char item_header[9] = "<Items>";
  for (BYTE i = 0; i < strlen(item_header); i++) {
    menu[s_i] = item_header[i];
    s_i++;
  }
  menu[s_i++] = ' ';
  menu[s_i++] = '1';
  menu[s_i++] = '/';
  menu[s_i++] = '1';
  while (s_i % 20 != 0) {
    menu[s_i] = ' ';
    s_i++;
  }
  menu[s_i - 4] = '#';
  for (UBYTE i = 0; i<s_i; i++) {
    UBYTE t = menu[i];
    menu[i] = ReadBankedUBYTE(_font.recode_table + t, BANK(font_gbs_mono));
    menu[i] += start_of_bkg_vram;
  }
  set_bkg_tiles(2, 0, 17, 1, menu);
  if(item_slots[0].type == NULL){
    VM_GLOBAL(VAR_TEMP_FRAME) = 0;
    return;
  }

  s_i = 0;
  VM_GLOBAL(VAR_TEMP_FRAME) = 9;
  for (BYTE i = 0; i < 10; i++) {
    if (item_slots[i].type == NULL) {
      VM_GLOBAL(VAR_TEMP_FRAME) = i - 1;
      break;
    }
    for (BYTE j = 0; j < 3; j++) {
      menu[s_i] = ' ';
      s_i++;
    }
    s_i += write_item_name(item_slots[i].type, &menu[s_i]);
    while (s_i % 20 != 0) {
      menu[s_i] = ' ';
      s_i++;
    }
    itoa_format(item_slots[i].count, &menu[s_i - 2], 0);
  }
  for (UBYTE i = 0; i<(20*10); i++) {
    UBYTE t = menu[i];
    menu[i] = ReadBankedUBYTE(_font.recode_table + t, BANK(font_gbs_mono));
    menu[i] += start_of_bkg_vram;
  }
  set_bkg_tiles(0, 2, 20, 10, menu);
  // draw_window();
}

void loadFontIntoBkg(SCRIPT_CTX * THIS) OLDCALL BANKED {
  THIS;
  MemcpyBanked(&start_of_bkg_vram, &bg_inventory_tileset.n_tiles,
               sizeof(UBYTE), BANK(bg_inventory_tileset));
  MemcpyBanked(&_font, font_gbs_mono, sizeof(font_desc_t), BANK(font_gbs_mono));
  SetBankedBkgData(start_of_bkg_vram, 16*7, _font.bitmaps, BANK(font_gbs_mono));
}