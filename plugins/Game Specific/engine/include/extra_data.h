#ifndef FF_EXTRA_DATA
#define FF_EXTRA_DATA
#include "entity_data.h"
#include "item_slot.h"
#include "weapon_data.h"

#define MAX_ITEM_SLOTS 20

extern struct entity_data * turn_slots;
extern struct item_slot * item_slots;
extern struct weapon_data * weapon_slots;
extern struct armor_data * armor_slots;

#endif