#include <asm/types.h>
#include <ui.h>
#pragma bank 255
#include "load_font_into_bg.h"
#include "data/font_gbs_mono.h"
#include "data_manager.h"
#include <bankdata.h>
#include <gbs_types.h>

UBYTE start_of_bkg_vram;
font_desc_t bg_font;
UBYTE bg_font_bank;

void loadFontIntoBkg(void) OLDCALL BANKED {
  bg_font_bank = BANK(font_gbs_mono);
  scene_t c_scene;
  MemcpyBanked(&c_scene, current_scene.ptr, sizeof(scene_t),
               current_scene.bank);

  background_t c_bkg;
  MemcpyBanked(&c_bkg, c_scene.background.ptr, sizeof(background_t),
               c_scene.background.bank);

  tileset_t c_tiles;
  MemcpyBanked(&c_tiles, c_bkg.tileset.ptr, sizeof(tileset_t),
               c_bkg.tileset.bank);

  start_of_bkg_vram = c_tiles.n_tiles;
  MemcpyBanked(&bg_font, font_gbs_mono, sizeof(font_desc_t), bg_font_bank);
  SetBankedBkgData(start_of_bkg_vram,16*12 - start_of_bkg_vram, bg_font.bitmaps, bg_font_bank);
}

void write_bg_font(UBYTE x, UBYTE y, UBYTE w, UBYTE h) OLDCALL BANKED {
  UBYTE menu[TEXT_MAX_LENGTH] = "";
  BYTE ui_i=-1;
  BYTE nl_count=w;
  BOOLEAN end_of_arr = FALSE;
  for (UBYTE i = 0; i<(w*h); i++) {
    if (end_of_arr) {
      menu[i] =
          ReadBankedUBYTE(bg_font.recode_table + (UBYTE)' ', bg_font_bank);
        menu[i] += start_of_bkg_vram;
      continue;
    }

    ui_i++;
    if(ui_text_data[ui_i] == '\0'){
      menu[i] =
          ReadBankedUBYTE(bg_font.recode_table + (UBYTE)' ', bg_font_bank);
        menu[i] += start_of_bkg_vram;
      end_of_arr = TRUE;
      continue;
    }

    if(ui_text_data[ui_i] == '\n'){
      for (BYTE n_count = 0; n_count < nl_count; n_count++) {
        menu[i+n_count] = ReadBankedUBYTE(bg_font.recode_table + (UBYTE) ' ',
                                  bg_font_bank);
        menu[i+n_count] += start_of_bkg_vram;
      }
      i+=nl_count - 1;
      nl_count=w;
      continue;
    }
    
    menu[i] = ReadBankedUBYTE(bg_font.recode_table + ui_text_data[ui_i], bg_font_bank);
    menu[i] += start_of_bkg_vram;
    nl_count--;
    if(nl_count<0) nl_count = w;
  }

  set_bkg_tiles(x, y, w, h, menu);
}