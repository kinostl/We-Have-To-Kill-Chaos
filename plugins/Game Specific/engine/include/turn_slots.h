#ifndef FF_TURN_SLOTS
#define FF_TURN_SLOTS
#include <asm/types.h>
#include <types.h>
#include "entity_data.h"
#include "vm.h"

void load_attacker(SCRIPT_CTX * THIS) OLDCALL BANKED;
void load_defender(SCRIPT_CTX * THIS) OLDCALL BANKED;

void load_player_atk(entity_data * player) OLDCALL BANKED;
void load_player_def(entity_data * player) OLDCALL BANKED;
void load_enemy_atk(entity_data * enemy) OLDCALL BANKED;
void load_enemy_def(entity_data * enemy) OLDCALL BANKED;
void load_name(entity_data * entity) OLDCALL BANKED;

typedef struct turn_slot_t {
  entity_data *entity;
  struct turn_slot_t *prev;
  struct turn_slot_t *next;
  UBYTE initiative_roll;
  BOOLEAN is_enemy;
} turn_slot_t;

inline BOOLEAN continue_enemy_turn(turn_slot_t *turn) {
  if(turn->prev && turn->prev->is_enemy) return TRUE;
}

#endif