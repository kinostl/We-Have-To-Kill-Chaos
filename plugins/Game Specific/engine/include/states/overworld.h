#ifndef STATE_OVERWORLD_H
#define STATE_OVERWORLD_H

#include <gbdk/platform.h>
#include "ff_types.h"
#include "states/topdown.h" // IWYU pragma: export

extern overworld_far_ptr overworld_maps[4];
extern UBYTE overworld_tile_quad;

void overworld_init(void) BANKED;
void overworld_update(void) BANKED;

#endif
