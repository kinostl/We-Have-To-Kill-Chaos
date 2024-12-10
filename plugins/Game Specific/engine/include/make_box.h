#ifndef FF_MAKE_BOX
#define FF_MAKE_BOX

#include <asm/types.h>

#define ui_frame_tl_tiles 0xC0u
#define ui_frame_bl_tiles 0xC6u
#define ui_frame_tr_tiles 0xC2u
#define ui_frame_br_tiles 0xC8u
#define ui_frame_t_tiles  0xC1u
#define ui_frame_b_tiles  0xC7u
#define ui_frame_l_tiles  0xC3u
#define ui_frame_r_tiles  0xC5u
#define ui_frame_bg_tiles 0xC4u

void render_frame(UBYTE x, UBYTE y, UBYTE w, UBYTE h, BOOLEAN is_window) BANKED;
void draw_bkg_frame(UBYTE x, UBYTE y, UBYTE w, UBYTE h) BANKED;
void draw_win_frame(UBYTE x, UBYTE y, UBYTE w, UBYTE h) BANKED;

#endif