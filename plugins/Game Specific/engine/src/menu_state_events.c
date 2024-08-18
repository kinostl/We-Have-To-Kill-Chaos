#include "load_font_into_bg.h"
#include <asm/types.h>
#include <vm.h>
#include <ui.h>
#pragma bank 255

unsigned char get_rendered_char(unsigned char d) {
  d = ReadBankedUBYTE(bg_font.recode_table + d, bg_font_bank);
  d += start_of_bkg_vram;
  return d;
}

unsigned char *fs_menu_render_char(UBYTE *d, UBYTE *menu_ptr,
                                   UBYTE w, BYTE nl_count, UBYTE *menu, UBYTE x) OLDCALL BANKED {
  UBYTE dx, dy;

  switch (*d) {
  case 0x00:
  case 0x01:
  case 0x02:
    // set current font
  case 0x03:
    // gotoxy
  case 0x04:
    // relative gotoxy
  case 0x06:
    // wait for input not supported
  case 0x07:
    // color inversion not supported
  case 0x08:
    // text direction (left-to-right or right-to-left)
  case 0x09:
  case 0x0b:
    // area palettes;
  case '\r': // 0x0d
    // \r not supported
    break;
  case '\n': // 0x0a
    for (BYTE n_count = 0; n_count < nl_count; n_count++) {
      *menu_ptr++ = get_rendered_char(' ');
    }
    break;
  case 0x05:
    *menu_ptr = get_rendered_char('%');
    break;
  default:
    *menu_ptr = get_rendered_char(*d);
    break;
  }
    return menu_ptr;
}

void fs_menu_write_bg_font(UBYTE x, UBYTE y, UBYTE w, UBYTE h) OLDCALL BANKED {
  UBYTE menu[TEXT_MAX_LENGTH];
  UBYTE * menu_ptr = &menu[0];
  UBYTE ui_i=0;
  BYTE nl_count=w;
  BOOLEAN end_of_arr = FALSE;
  for (UBYTE i = 0; i < (w * h); i++) {
    menu[i] = get_rendered_char(' ');
  }
  for (UBYTE i = 0; i < (w * h); i++) {
    if (end_of_arr) {
      *menu_ptr++ = get_rendered_char(' ');
      continue;
    }

    if (ui_text_data[ui_i] == '\0') {
      *menu_ptr++ = get_rendered_char(' ');
      end_of_arr = TRUE;
      continue;
    }

    menu_ptr = fs_menu_render_char(&ui_text_data[ui_i], menu_ptr, w, nl_count, &menu[0], x);

    if (ui_text_data[ui_i] == 0x03 || ui_text_data[ui_i] == 0x04) {
      ui_i += 2;
    }

    nl_count--;
    if (nl_count < 0)
      nl_count = w;

    menu_ptr++;
    ui_i++;
  }

  set_bkg_tiles(x, y, w, h, menu);
}

void writeTextToBg(SCRIPT_CTX * THIS) OLDCALL BANKED {

    UBYTE x = *(UBYTE *) VM_REF_TO_PTR(FN_ARG3);
    UBYTE y = *(UBYTE *) VM_REF_TO_PTR(FN_ARG2);
    UBYTE w = *(UBYTE *) VM_REF_TO_PTR(FN_ARG1);
    UBYTE h = *(UBYTE *) VM_REF_TO_PTR(FN_ARG0);

    fs_menu_write_bg_font(x, y, w, h);

}   