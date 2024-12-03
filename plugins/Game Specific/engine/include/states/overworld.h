#ifndef STATE_OVERWORLD_H
#define STATE_OVERWORLD_H

#include "ff_types.h"
#include "states/topdown.h" // IWYU pragma: export
#include <gbdk/platform.h>

typedef enum overworld_quad {
  Q_TOP_LEFT,
  Q_TOP_RIGHT,
  Q_BOT_LEFT,
  Q_BOT_RIGHT
} overworld_quad;

extern overworld_far_ptr overworld_maps[4];
extern overworld_quad overworld_tile_quad;

void overworld_init(void) BANKED;
void overworld_update(void) BANKED;

#endif
