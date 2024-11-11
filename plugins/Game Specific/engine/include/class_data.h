#ifndef FF_CLASS_DATA
#define FF_CLASS_DATA
#include "macro.h"

typedef enum {
  FIGHTER = 1 << 0,
  THIEF = 1 << 1,
  MONK = 1 << 2,
  RED_MAGE = 1 << 3,
  WHITE_MAGE = 1 << 4,
  BLACK_MAGE = 1 << 5,
  BLUE_MAGE = 1 << 6
} JOB;

#define ALL_JOBS                                                               \
  (FIGHTER | THIEF | MONK | RED_MAGE | WHITE_MAGE | BLACK_MAGE | BLUE_MAGE)
#define ALL_CASTERS (WHITE_MAGE | BLACK_MAGE | BLUE_MAGE)
#define ALL_MELEE (FIGHTER | THIEF | MONK)
#endif