#include "extra_data.h"
#include "load_font_into_bg.h"
#include "make_box.h"
#include <asm/types.h>
#include <string.h>
#pragma bank 255
#include "ff_text.h"
#include "ff_util.h"
#include <ui.h>
#include "handle_menu.h"

void ui_draw_frame(UBYTE x, UBYTE y, UBYTE width, UBYTE height) BANKED;
BOOLEAN show_message;

void load_battle_message(unsigned char * message) OLDCALL BANKED {
  loadPartyMenuOffset(12);
  draw_bkg_frame(12, 0, 8, 18);
  write_bg_font(13, 1, 6, 16);

  ui_set_pos_to_xy(0, 18);
  ui_draw_frame(0, 0, 20, 3);

  strcpy(ui_text_data, message);
  write_win_font(1, 1, 16, 1);
  show_message = TRUE;
}

void show_battle_message(void) OLDCALL BANKED {
  if (show_message) {
    ui_move_to_xy(0, 15, text_in_speed);
    ui_run_modal(UI_WAIT_WINDOW);
  }
}

void idle_battle_message(void) OLDCALL BANKED {
  if(show_message){
    for(UBYTE i=0;i<30;i++){
      vsync();
    }
  }
}

void close_battle_message(void) OLDCALL BANKED {
  if (show_message) {
    ui_move_to_xy(0, 18, text_out_speed);
    ui_run_modal(UI_WAIT_WINDOW);

    loadPartyMenu();
    ui_draw_frame(0, 0, 8, 18);
    write_win_font(1, 1, 6, 16);

    ui_set_pos_to_xy(12, 0);

    VBK_REG = VBK_ATTRIBUTES;
    fill_bkg_rect(12, 0, 8, 18, 0b00000111);
    VBK_REG = VBK_TILES;
    fill_bkg_rect(12, 0, 8, 18, ui_white_tile);
    show_message = FALSE;
  }
}