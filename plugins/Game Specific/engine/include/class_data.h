#ifndef FF_CLASS_DATA
#define FF_CLASS_DATA
#include "macro.h"

enum W_CLASSES {
  FIGHTER = 1 << 0,
  THIEF = 1 << 1,
  MONK = 1 << 2,
  RED_MAGE = 1 << 3,
  WHITE_MAGE = 1 << 4,
  BLACK_MAGE = 1 << 5,
  BLUE_MAGE = 1 << 6
};

#define add_fighter(c) SET_FLAG(c, FIGHTER)
#define add_thief(c) SET_FLAG(c, THIEF)
#define add_monk(c) SET_FLAG(c, MONK)
#define add_red_mage(c) SET_FLAG(c, RED_MAGE)
#define add_white_mage(c) SET_FLAG(c, WHITE_MAGE)
#define add_black_mage(c) SET_FLAG(c, BLACK_MAGE)
#define add_blue_mage(c) SET_FLAG(c, BLUE_MAGE)
#endif