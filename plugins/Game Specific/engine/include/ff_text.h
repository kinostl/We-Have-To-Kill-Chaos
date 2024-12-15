#ifndef FF_TEXT
#define FF_TEXT

#include "load_font_into_bg.h"
#include <gb/gb.h>

extern BOOLEAN show_message;
void load_battle_message(unsigned char * message) OLDCALL BANKED;
void show_battle_message(void) OLDCALL BANKED;
void close_battle_message(void) OLDCALL BANKED;
void ui_draw_frame(UBYTE x, UBYTE y, UBYTE width, UBYTE height) BANKED;
inline void ui_display_text(void) {
  // Could technically call vm_display_text but vm calls are bad practice
  ui_draw_frame(0, 0, 8, 18);
  write_win_font(1, 1, 6, 16);
  // INPUT_RESET;
  // text_options = TEXT_OPT_DEFAULT;
  // text_drawn = text_ff = FALSE;
  // ui_set_start_tile(TEXT_BUFFER_START, 0);
  // ui_run_modal(UI_WAIT_TEXT);
}

inline void ui_update_text(void) {
  // write_win_font(1, 1, 6, 16);
  render_text(1, 1, 6, 16, TRUE, FALSE, TRUE);
  // INPUT_RESET;
  // text_options = TEXT_OPT_DEFAULT;

  // text_drawn = text_ff = FALSE;
  // ui_set_start_tile(TEXT_BUFFER_START, 0);
  // ui_run_modal(UI_WAIT_TEXT);
}
#endif