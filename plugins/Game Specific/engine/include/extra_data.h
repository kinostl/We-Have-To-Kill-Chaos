#ifndef FF_EXTRA_DATA
#define FF_EXTRA_DATA
#include "entity_data.h"
#include "hero_data.h"
#include "item_slot.h"
#include "weapon_data.h"

#define MAX_ITEM_SLOTS 20
#define ITEM_NOT_FOUND MAX_ITEM_SLOTS + 1

extern struct entity_data * turn_slots;
extern struct item_slot * item_slots;
extern struct item_slot * menu_slots;
extern struct weapon_data * weapon_slots;
extern struct armor_data * armor_slots;
extern struct armor_data * shield_slots;
extern struct armor_data * glove_slots;
extern struct armor_data * helmet_slots;
extern struct hero_data * hero_slots;

#endif