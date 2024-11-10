#ifndef FF_EXTRA_DATA
#define FF_EXTRA_DATA

#include "action_handler.h"
#include "enemy_data.h"
#include "hero_data.h"
#include "item_slot.h"

#define MAX_ITEM_SLOTS 20
#define ITEM_NOT_FOUND MAX_ITEM_SLOTS + 1

extern item_slot * item_slots;
extern item_slot * menu_slots;
extern hero_data * hero_slots;
extern enemy_data * enemy_slots;
extern ACTION_TYPE * action_slots;
extern BYTE * turn_order;

#endif