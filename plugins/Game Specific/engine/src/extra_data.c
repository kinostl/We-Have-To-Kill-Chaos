#include "entity_data.h"
#include "item_slot.h"
#include "weapon_data.h"
#include "armor_data.h"
#include <asm/types.h>
#include <data/game_globals.h>
#include <vm.h>
#pragma bank 255


#define entity_size (sizeof(struct entity_data) * 10) / sizeof(WORD)
#define weapon_size (sizeof(struct weapon_data) * 4) / sizeof(WORD)
#define armor_size (sizeof(struct armor_data) * 4) / sizeof(WORD)
#define item_size (sizeof(struct item_slot) * MAX_ITEM_SLOTS) / sizeof(WORD)

#define weapon_start MAX_GLOBAL_VARS + entity_size
#define armor_start weapon_start + weapon_size
#define item_start armor_start + armor_size

struct entity_data *turn_slots = (struct entity_data *)&VM_GLOBAL(MAX_GLOBAL_VARS);
struct weapon_data *weapon_slots = (struct weapon_data *)&VM_GLOBAL(weapon_start);
struct armor_data *armor_slots = (struct armor_data *)&VM_GLOBAL(armor_start);
struct item_slot *item_slots = (struct item_slot *)&VM_GLOBAL(item_start);