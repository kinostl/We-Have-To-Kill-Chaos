#include "handle_submapping.h"
#include "load_font_into_bg.h"
#include <asm/types.h>
#include <gb/gb.h>
#include <ui.h>
#include <vm.h>
#pragma bank 255

unsigned char get_rendered_char(unsigned char d) {
  d = ReadBankedUBYTE(bg_font.recode_table + d, bg_font_bank);
  d += start_of_bkg_vram;
  return d;
}

void fs_clear_section(UBYTE x, UBYTE y, UBYTE w, UBYTE h, BOOLEAN instant) OLDCALL BANKED {
  for (int dy = y; dy < y + h; dy++) {
    for (int dx = x; dx < x + w; dx++) {
      if (!instant) {
        vsync();
      }
      set_bkg_tile_xy(dx, dy, get_rendered_char(' '));
    }
  }
}

void fs_menu_write_bg_font(UBYTE x, UBYTE y, UBYTE w, UBYTE h, BOOLEAN instant, BOOLEAN clear_area) OLDCALL BANKED {
  if (clear_area) {
    fs_clear_section(x, y, w, h, instant);
  }
  UBYTE ui_i = 0;
  UBYTE dx = x;
  UBYTE dy = y;
  UBYTE * d = ui_text_data;

  while(*d != '\0' && d <= &ui_text_data[TEXT_MAX_LENGTH]){
    if(*d == 0x03){
        dx = *++d;
        dy = *++d;
        dx--;
        dy--;
        d++;
        continue;
    }

    if(*d == 0x04){
        dx += *++d;
        dy += *++d;
        dx--;
        dy--;
        d++;
        continue;
    }

    if (*d == 0x05) {
      set_bkg_tile_xy(dx, dy, get_rendered_char('%'));
      d++;
      continue;
    }

    if(*d == '\n' || (dx - x) > w){
        dy++;
        dx = x;
        d++;
        continue;
    }

    if ((dy - y) < h && (dx - x) < w) {
      set_bkg_tile_xy(dx, dy, get_rendered_char(*d));
      dx++;
    }
    d++;
    if (!instant) {
      vsync();
    }
  }
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