#ifndef STATE_OVERWORLD_H
#define STATE_OVERWORLD_H

#include "ff_types.h"
#include "states/topdown.h" // IWYU pragma: export
#include <gbdk/platform.h>

typedef enum overworld_quad {
  Q_CENTER,
  Q_TOP_LEFT,
  Q_TOP,
  Q_TOP_RIGHT,
  Q_RIGHT,
  Q_BOT_RIGHT,
  Q_BOT,
  Q_BOT_LEFT,
  Q_LEFT,
} overworld_quad;

void overworld_init(void) BANKED;
void overworld_update(void) BANKED;

#endif
