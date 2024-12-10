#ifndef FF_LOAD_FONT_IN_BG
#define FF_LOAD_FONT_IN_BG
#include <asm/types.h>
#include "gbs_types.h"

extern UBYTE start_of_bkg_vram;
extern font_desc_t bg_font;
extern UBYTE bg_font_bank;


void write_bg_font(UBYTE x, UBYTE y, UBYTE w, UBYTE h) BANKED;
void write_win_font(UBYTE x, UBYTE y, UBYTE w, UBYTE h) BANKED;
void loadFontIntoUiSpace(void) OLDCALL BANKED;
void write_bg_char(UBYTE x, UBYTE y, unsigned char c) OLDCALL BANKED;
void render_text(UBYTE x, UBYTE y, UBYTE w, UBYTE h, BOOLEAN instant,
                 BOOLEAN clear_area, BOOLEAN is_window) OLDCALL BANKED;

#endif