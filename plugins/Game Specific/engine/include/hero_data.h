#ifndef FF_HERO_DATA
#define FF_HERO_DATA
#include <asm/types.h>

struct hero_data {
  // shared data
  BYTE slot_id;
  char name[7];
  BYTE job;
};

#endif