#include "bkg_tile_info.h"
#include "ff_types.h"
#include <bankdata.h>
#include <gbs_types.h>

#pragma bank 255

void set_overworld_ptr(overworld_far_ptr *ptr, UBYTE x, UBYTE y) BANKED {
  UBYTE pos = x + (y * 16);
  switch (pos) {
#define X(num)                                                                 \
  case num:                                                                    \
    ptr->bank = ((uint8_t) & __bank_bg_overworld_##num);                       \
    ptr->map_ptr = bg_overworld_##num##_map;                                   \
    ptr->attrs_ptr = bg_overworld_##num##_map_attributes;                      \
    break;
#include "bkg_tile_x_list.h"
#undef X
  }
}