#ifndef FF_CLASS_DATA
#define FF_CLASS_DATA
#include "macro.h"

typedef enum {
  FIGHTER_ID,
  THIEF_ID,
  MONK_ID,
  RED_MAGE_ID,
  WHITE_MAGE_ID,
  BLACK_MAGE_ID,
  BLUE_MAGE_ID
} JOB_ID;

typedef enum {
  FIGHTER = 1 << FIGHTER_ID,
  THIEF = 1 << THIEF_ID,
  MONK = 1 << MONK_ID,
  RED_MAGE = 1 << RED_MAGE_ID,
  WHITE_MAGE = 1 << WHITE_MAGE_ID,
  BLACK_MAGE = 1 << BLACK_MAGE_ID,
  BLUE_MAGE = 1 << BLUE_MAGE_ID,
  // SECRET = 1 << 7
  /* Lying probably */
} JOB;

#define ALL_JOBS                                                               \
  (FIGHTER | THIEF | MONK | RED_MAGE | WHITE_MAGE | BLACK_MAGE | BLUE_MAGE)
#define ALL_CASTERS (WHITE_MAGE | BLACK_MAGE | BLUE_MAGE)
#define ALL_MELEE (FIGHTER | THIEF | MONK)
#endif