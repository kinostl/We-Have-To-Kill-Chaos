#ifndef FF_MENU_STATE_EVENTS
#define FF_MENU_STATE_EVENTS

#include <asm/types.h>

void fs_menu_write_bg_font(UBYTE x, UBYTE y, UBYTE w, UBYTE h, BOOLEAN instant, BOOLEAN clear_area) OLDCALL BANKED;
void fs_menu_write_win_font(UBYTE x, UBYTE y, UBYTE w, UBYTE h, BOOLEAN instant, BOOLEAN clear_area) OLDCALL BANKED;
#endif