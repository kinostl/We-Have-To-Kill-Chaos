#include "ff_types.h"
#include <asm/types.h>
#include <interrupts.h>
#include <types.h>
#pragma bank 255

#include "states/overworld.h"
#include "bkg_tile_info.h"

void overworld_init(void) BANKED {
  topdown_init();
  overworld_far_ptr number;
  set_overworld_ptr(&number, 0, 0);
}


void overworld_update(void) BANKED {
    topdown_update();
}
