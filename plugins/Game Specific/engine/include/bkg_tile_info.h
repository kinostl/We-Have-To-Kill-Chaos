#ifndef FF_BKG_TILE_INFO
#define FF_BKG_TILE_INFO

#include <gb/gb.h>
#include <gbs_types.h>
#include "bkg_tile_list.h" // IWYU pragma: export

void set_overworld_ptr(far_ptr_t * ptr, UBYTE x, UBYTE y) BANKED;

#endif