#include <asm/types.h>
#include "entity_data.h"
#include "item_slot.h"
#include "weapon_data.h"
#include <data/game_globals.h>
#include <vm.h>
#pragma bank 255

struct entity_data *turn_slots = (struct entity_data *)&VM_GLOBAL(MAX_GLOBAL_VARS + 1);
struct weapon_data * weapon_slots = (struct weapon_data *) &turn_slots + (sizeof(struct entity_data) * 11);
struct item_slot * item_slots = (struct item_slot *) &weapon_slots + (sizeof(struct weapon_data) * 5);