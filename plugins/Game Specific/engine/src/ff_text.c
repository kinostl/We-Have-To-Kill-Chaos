#pragma bank 255
#include "ff_text.h"
#include "ff_util.h"
#include <ui.h>
#include "scroll.h"

void ui_draw_frame(UBYTE x, UBYTE y, UBYTE width, UBYTE height) BANKED;

void flash_battle_message(void) OLDCALL BANKED {
  VBK_REG=VBK_ATTRIBUTES;
  set_bkg_submap(12, 0, 8, 18, GetWinAddr()-12, 32);
  VBK_REG=VBK_TILES;
  set_bkg_submap(12, 0, 8, 18, GetWinAddr()-12, 32);

  ui_set_pos_to_xy(0, 18);
  ui_draw_frame(0, 0, 20, 3);

  INPUT_RESET;
  text_options = TEXT_OPT_DEFAULT;

  text_drawn = text_ff = FALSE;
  ui_set_start_tile(256 - 16, 1);
  ui_run_modal(UI_WAIT_TEXT);

  ui_move_to_xy(0, 15, text_in_speed);
  ui_run_modal(UI_WAIT_WINDOW);
  for (UBYTE i = 0; i < 3; i++) {
    vsync();
  }
}

void fix_panel_area(void) BANKED {
  ui_move_to_xy(0, 18, text_out_speed);
  ui_run_modal(UI_WAIT_WINDOW);

  VBK_REG = VBK_ATTRIBUTES;
  set_win_submap(0, 0, 8, 18, GetBkgAddr() + 12, 32);
  VBK_REG = VBK_TILES;
  set_win_submap(0, 0, 8, 18, GetBkgAddr() + 12, 32);

  ui_set_pos_to_xy(12, 0);

  VBK_REG = VBK_ATTRIBUTES;
  fill_bkg_rect(12, 0, 8, 18, TEXT_BKG_FILL_B);
  VBK_REG = VBK_TILES;
  fill_bkg_rect(12, 0, 8, 18, TEXT_BKG_FILL_B);
}