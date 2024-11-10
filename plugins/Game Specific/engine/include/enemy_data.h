#ifndef FF_ENEMY_DATA
#define FF_ENEMY_DATA

#include "entity_data.h"


typedef struct {
  BYTE skill_idx;
  BYTE x;
  BYTE y;
  BYTE w;
  BYTE h;

  char name[8];
  entity_data ext;

  BYTE idx;
} enemy_data;

#endif