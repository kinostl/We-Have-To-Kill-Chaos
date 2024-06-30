#ifndef FF_ENEMY_SLOTS
#define FF_ENEMY_SLOTS
#include "enemy_data.h"
#include <asm/types.h>
struct enemy_slot {
  BYTE hp;
  BYTE skill_idx;
  BOOLEAN alive;
  BYTE x;
  BYTE y;
  BYTE w;
  BYTE h;
  struct enemy_info info;
};

void initialize_enemy_slot(struct enemy_slot * slot) OLDCALL BANKED;

extern struct enemy_slot * enemy_slots;
#endif