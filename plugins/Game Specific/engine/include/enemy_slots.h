#ifndef FF_ENEMY_SLOTS
#define FF_ENEMY_SLOTS
#include <gb/gb.h>
#include <asm/types.h>
#include "entity_data.h"

struct enemy_slot {
  BYTE slot_id;
  BYTE hp;
  BYTE skill_idx;
  BOOLEAN alive;
  BYTE x;
  BYTE y;
  BYTE w;
  BYTE h;
  struct entity_data info;
};

void initialize_enemy_slot(struct enemy_slot * slot) OLDCALL BANKED;

extern struct enemy_slot * enemy_slots;
void load_enemy_atk(struct enemy_slot * enemy) OLDCALL BANKED;
void load_enemy_def(struct enemy_slot * enemy) OLDCALL BANKED;
#endif