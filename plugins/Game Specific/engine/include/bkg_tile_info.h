#ifndef FF_BKG_TILE_INFO
#define FF_BKG_TILE_INFO

#include <gb/gb.h>
#include <gbs_types.h>
#include "bkg_tile_list.h" // IWYU pragma: export
#include "ff_types.h"

void set_overworld_ptr(overworld_far_ptr * ptr, UBYTE x, UBYTE y) BANKED;

#endif