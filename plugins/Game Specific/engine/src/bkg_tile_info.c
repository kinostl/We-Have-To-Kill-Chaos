#include "bkg_tile_info.h"
#include "ff_types.h"
#include <bankdata.h>
#include <gbs_types.h>

#pragma bank 255


const overworld_far_ptr overworld_db[] = {
#define X(num)                                                                 \
  {                                                                            \
      .bank = BANK(bg_overworld_##num),                                        \
      .map_ptr = bg_overworld_##num##_map,                                     \
      .attrs_ptr = bg_overworld_##num##_map_attributes,                        \
  },
#include "bkg_tile_x_list.h"
#undef X
};

BANKREF(overworld_db)