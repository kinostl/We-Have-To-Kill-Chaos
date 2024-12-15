#ifndef FF_UTIL
#define FF_UTIL

#include "rand.h" // IWYU pragma: export
#include <asm/types.h>
#include <input.h>
#include <ui.h>


#define drand(min, max) (min + rand() / (RAND_MAX / (max - min + 1) + 1))
#define ui_move_to_xy(x,y,speed) ui_move_to((x<<3), (y<<3), speed)
#define ui_set_pos_to_xy(x,y) ui_set_pos((x<<3), (y<<3))


#endif