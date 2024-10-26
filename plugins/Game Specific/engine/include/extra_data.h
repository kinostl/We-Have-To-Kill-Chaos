#ifndef FF_EXTRA_DATA
#define FF_EXTRA_DATA

#include "action_handler.h"
#include "armor_data.h"
#include "entity_data.h"
#include "hero_data.h"
#include "item_slot.h"
#include "weapon_data.h"

#define MAX_ITEM_SLOTS 20
#define ITEM_NOT_FOUND MAX_ITEM_SLOTS + 1

extern entity_data * turn_slots;
extern item_slot * item_slots;
extern item_slot * menu_slots;
extern weapon_data * weapon_slots;
extern armor_data * armor_slots;
extern armor_data * shield_slots;
extern armor_data * glove_slots;
extern armor_data * helmet_slots;
extern hero_data * hero_slots;
extern ACTION_TYPE * action_slots;
extern BYTE * turn_order;

#endif