#ifndef FF_HERO_DATA
#define FF_HERO_DATA
#include <asm/types.h>

typedef struct {
  // shared data
  BYTE slot_id;
  char name[7];
  BYTE job;
} hero_data;

#endif