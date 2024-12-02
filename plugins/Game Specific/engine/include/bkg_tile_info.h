#ifndef FF_BKG_TILE_INFO
#define FF_BKG_TILE_INFO

#include <gb/gb.h>
#include <gbs_types.h>
#include "ff_types.h"
#include "bkg_tile_list.h" // IWYU pragma: export


extern const overworld_far_ptr overworld_db[];

BANKREF_EXTERN(overworld_db)

inline void set_overworld_ptr(overworld_far_ptr *ptr, UBYTE x, UBYTE y) {
  UBYTE pos = x + (y * 16);
  MemcpyBanked(ptr, &overworld_db[pos], sizeof(overworld_far_ptr), BANK(overworld_db));
}

#endif