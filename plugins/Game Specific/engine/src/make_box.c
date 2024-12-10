#include "make_box.h"
#include "vm.h"
#include "vm_ui.h"
#include <asm/types.h>
#include <gb/hardware.h>

#pragma bank 255

void makeBox(SCRIPT_CTX *THIS) OLDCALL BANKED {
  UBYTE x = *(UBYTE *)VM_REF_TO_PTR(FN_ARG0);
  UBYTE y = *(UBYTE *)VM_REF_TO_PTR(FN_ARG1);
  UBYTE w = *(UBYTE *)VM_REF_TO_PTR(FN_ARG2);
  UBYTE h = *(UBYTE *)VM_REF_TO_PTR(FN_ARG3);
  // UBYTE color = *(UBYTE *) VM_REF_TO_PTR(FN_ARG4);
  // UBYTE opts = *(UBYTE *) VM_REF_TO_PTR(FN_ARG5);

  UBYTE color = 1;
  UBYTE options = 0 | 1;

  vm_overlay_clear(THIS, x, y, w, h, color, options);
}

void render_frame(UBYTE x, UBYTE y, UBYTE w, UBYTE h,
                  BOOLEAN is_window) BANKED {
  if (is_window) {
    draw_win_frame(x, y, w, h);
  } else {
    draw_bkg_frame(x, y, w, h);
  }
}

void draw_bkg_frame(UBYTE x, UBYTE y, UBYTE w, UBYTE h) BANKED {
  w--;
  h--;
  VBK_REG = VBK_ATTRIBUTES;
  fill_bkg_rect(x, y, w, h, 0b00000111);
  VBK_REG = VBK_TILES;
  fill_bkg_rect(x + 1, y + 1, w - 2, h - 2, ui_frame_bg_tiles);

  fill_bkg_rect(x, y, w, 1, ui_frame_t_tiles);
  fill_bkg_rect(x, y + h, w, 1, ui_frame_b_tiles);
  fill_bkg_rect(x, y, 1, h, ui_frame_l_tiles);
  fill_bkg_rect(x + w, y, 1, h, ui_frame_r_tiles);

  fill_bkg_rect(x, y, 1, 1, ui_frame_tl_tiles);
  fill_bkg_rect(x + w, y, 1, 1, ui_frame_tr_tiles);
  fill_bkg_rect(x, y + h, 1, 1, ui_frame_bl_tiles);
  fill_bkg_rect(x + w, y + h, 1, 1, ui_frame_br_tiles);
}

void draw_win_frame(UBYTE x, UBYTE y, UBYTE w, UBYTE h) BANKED {
  w--;
  h--;
  VBK_REG = VBK_ATTRIBUTES;
  fill_win_rect(x, y, w, h, 0b00000111);
  VBK_REG = VBK_TILES;
  fill_win_rect(x, y, w, h, ui_frame_bg_tiles);

  fill_win_rect(x, y, w, 1, ui_frame_t_tiles);
  fill_win_rect(x, y + h, w, 1, ui_frame_b_tiles);
  fill_win_rect(x, y, 1, h, ui_frame_l_tiles);
  fill_win_rect(x + w, y, 1, h, ui_frame_r_tiles);

  fill_win_rect(x, y, 1, 1, ui_frame_tl_tiles);
  fill_win_rect(x + w, y, 1, 1, ui_frame_tr_tiles);
  fill_win_rect(x, y + h, 1, 1, ui_frame_bl_tiles);
  fill_win_rect(x + w, y + h, 1, 1, ui_frame_br_tiles);
}