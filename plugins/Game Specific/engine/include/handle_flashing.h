#ifndef FF_EVENT_HANDLE_FLASHING
#define FF_EVENT_HANDLE_FLASHING

#include "enemy_data.h"
#include "extra_data.h"
#include <asm/types.h>

void handle_bkg_flash(WORD color_1, WORD color_2, WORD x, WORD y, WORD w, WORD h) OLDCALL BANKED;
void handle_bkg_set_color(WORD color, WORD x, WORD y, WORD w, WORD h) OLDCALL BANKED;
void handle_bkg_set_color_slow(WORD color, WORD x, WORD y, WORD w, WORD h) OLDCALL BANKED;
void handle_enemy_defeated(UBYTE enemy_id) BANKED;


#endif