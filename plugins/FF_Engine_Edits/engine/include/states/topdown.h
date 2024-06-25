#ifndef STATE_TOP_DOWN_H
#define STATE_TOP_DOWN_H

#include <gbdk/platform.h>

void topdown_init(void) BANKED;
void topdown_update(void) BANKED;

extern UBYTE topdown_grid;
extern UBYTE safe_from_monsters;
extern UBYTE half_hidden;

#endif
