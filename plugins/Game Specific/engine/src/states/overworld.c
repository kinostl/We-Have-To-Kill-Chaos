#include <asm/types.h>
#include <interrupts.h>
#include <types.h>
#pragma bank 255

#include "states/overworld.h"

void overworld_init(void) BANKED {
  topdown_init();
}


void overworld_update(void) BANKED {
    topdown_update();
}
