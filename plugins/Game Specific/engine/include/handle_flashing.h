#ifndef FF_EVENT_HANDLE_FLASHING
#define FF_EVENT_HANDLE_FLASHING

#include <asm/types.h>
void handle_bkg_flash(WORD color_1, WORD color_2, WORD x, WORD y, WORD w, WORD h) OLDCALL BANKED;

#endif