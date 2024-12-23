#ifndef FF_EXTRA_DATA
#define FF_EXTRA_DATA

#include "action_handler.h"
#include "enemy_data.h"
#include "hero_data.h"
#include "item_slot.h"
#include "turn_slots.h"

#define MAX_ITEM_SLOTS 20
#define ITEM_NOT_FOUND MAX_ITEM_SLOTS + 1

extern item_slot * item_slots;
extern item_slot * menu_slots;
extern hero_data * hero_slots;
extern enemy_data * enemy_slots;
extern action_t * action_slots;
extern action_t * action_head;
extern action_t * action_tail;
extern turn_slot_t * turn_slots;
extern turn_slot_t * current_turn;
extern turn_slot_t *head_slot;
extern enemy_data * current_enemy;
extern hero_data * current_hero;

#endif