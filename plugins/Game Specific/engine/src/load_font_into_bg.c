#include "menu_state_events.h"
#include <asm/types.h>
#include <gb/gb.h>
#include <gb/hardware.h>
#include <ui.h>
#include <vm.h>
#pragma bank 255
#include "data/font_gbs_mono.h"
#include "load_font_into_bg.h"
#include <bankdata.h>
#include <gbs_types.h>

UBYTE start_of_bkg_vram;
font_desc_t bg_font;
UBYTE bg_font_bank;
const UBYTE bank0size = (16 * 4) - 12;

void loadFontIntoUiSpace(void) OLDCALL BANKED {
  bg_font_bank = BANK(font_gbs_mono);
  start_of_bkg_vram = TEXT_BUFFER_START;
  MemcpyBanked(&bg_font, font_gbs_mono, sizeof(font_desc_t), bg_font_bank);

  SetBankedBkgData(TEXT_BUFFER_START, bank0size, bg_font.bitmaps, bg_font_bank);
  VBK_REG = VBK_BANK_1;
  SetBankedBkgData(TEXT_BUFFER_START_BANK1, (16 * 4),
                   bg_font.bitmaps + (bank0size * (16)), bg_font_bank);
  VBK_REG = VBK_BANK_0;
}

void loadFontIntoBkg(void) OLDCALL BANKED {}

inline unsigned char get_rendered_char(unsigned char d, BOOLEAN is_b1) {
  d = ReadBankedUBYTE(bg_font.recode_table + d, bg_font_bank);
  if (is_b1) {
    d += TEXT_BUFFER_START_BANK1;
    d -= (0x100 - TEXT_BUFFER_START);
    //For some reason the Bank lies or something
  } else {
    d += TEXT_BUFFER_START;
  }
  return d;
}


void render_char(UBYTE x, UBYTE y, unsigned char c,
                 BOOLEAN is_window) OLDCALL BANKED {
  unsigned char res[1];
  unsigned char attrs[1];
  const BOOLEAN is_b1 = c > 'T';
  if (is_b1) {
    attrs[0] = 0b00001111;
  } else {
    attrs[0] = 0b00000111;
  }

  res[0] = get_rendered_char(c, is_b1);

  if (is_window) {
    VBK_REG = VBK_ATTRIBUTES;
    set_win_tiles(x, y, 1, 1, attrs);
    VBK_REG = VBK_TILES;
    set_win_tiles(x, y, 1, 1, res);

  } else {
    VBK_REG = VBK_ATTRIBUTES;
    set_bkg_tiles(x, y, 1, 1, attrs);
    VBK_REG = VBK_TILES;
    set_bkg_tiles(x, y, 1, 1, res);
  }
}

void write_bg_char(UBYTE x, UBYTE y, unsigned char c) OLDCALL BANKED {
  render_char(x, y, c, FALSE);
}

void write_win_char(UBYTE x, UBYTE y, unsigned char c) OLDCALL BANKED {
  render_char(x, y, c, TRUE);
}

void fs_clear_section(UBYTE x, UBYTE y, UBYTE w, UBYTE h,
                             BOOLEAN instant, BOOLEAN is_window) OLDCALL BANKED{
  if (!instant) {
    for (int dy = y; dy < y + h; dy++) {
      for (int dx = x; dx < x + w; dx++) {
        vsync();
        render_char(x, y, ' ', is_window);
      }
    }
  }else{
    if(is_window){
      fill_win_rect(x,y,w,h,ui_bg_tile);
    }else{
      fill_bkg_rect(x,y,w,h,ui_bg_tile);
    }
  }
}

void render_text(UBYTE x, UBYTE y, UBYTE w, UBYTE h, BOOLEAN instant,
                        BOOLEAN clear_area, BOOLEAN is_window) OLDCALL BANKED{
  if (clear_area) {
    fs_clear_section(x, y, w, h, instant, is_window);
  }
  UBYTE ui_i = 0;
  UBYTE dx = x;
  UBYTE dy = y;
  UBYTE *d = ui_text_data;

  while (*d != '\0' && d <= &ui_text_data[TEXT_MAX_LENGTH]) {
    if (*d == 0x03) {
      dx = *++d;
      dy = *++d;
      dx--;
      dy--;
      d++;
      continue;
    }

    if (*d == 0x04) {
      dx += *++d;
      dy += *++d;
      dx--;
      dy--;
      d++;
      continue;
    }

    if (*d == 0x05) {
      render_char(dx, dy, '%', is_window);
      d++;
      continue;
    }

    if (*d == '\n' || (dx - x) > w) {
      dy++;
      dx = x;
      d++;
      continue;
    }

    if ((dy - y) < h && (dx - x) < w) {
      render_char(dx, dy, *d, is_window);
      dx++;
    }
    d++;
    if (!instant) {
      vsync();
    }
  }
}
void write_bg_font(UBYTE x, UBYTE y, UBYTE w, UBYTE h) BANKED{
  render_text(x, y, w, h, TRUE, TRUE, FALSE);
}

void write_win_font(UBYTE x, UBYTE y, UBYTE w, UBYTE h) BANKED{
  render_text(x, y, w, h, TRUE, TRUE, TRUE);
}

void fs_menu_write_bg_font(UBYTE x, UBYTE y, UBYTE w, UBYTE h, BOOLEAN instant,
                           BOOLEAN clear_area) BANKED {
  render_text(x, y, w, h, instant, clear_area, FALSE);
}

void writeTextToBg(SCRIPT_CTX *THIS) OLDCALL BANKED {
  BOOLEAN clear_area = *(BOOLEAN *)VM_REF_TO_PTR(FN_ARG5);
  BOOLEAN instant = *(BOOLEAN *)VM_REF_TO_PTR(FN_ARG4);
  UBYTE x = *(UBYTE *)VM_REF_TO_PTR(FN_ARG3);
  UBYTE y = *(UBYTE *)VM_REF_TO_PTR(FN_ARG2);
  UBYTE w = *(UBYTE *)VM_REF_TO_PTR(FN_ARG1);
  UBYTE h = *(UBYTE *)VM_REF_TO_PTR(FN_ARG0);

  fs_menu_write_bg_font(x, y, w, h, instant, clear_area);
}