#include "extra_data.h"
#include "action_handler.h"
#include "armor_data.h"
#include "enemy_data.h"
#include "entity_data.h"
#include "hero_data.h"
#include "item_slot.h"
#include "weapon_data.h"
#include <asm/types.h>
#include <data/game_globals.h>
#include <string.h>
#include <vm.h>
#pragma bank 255

item_slot *item_slots;
item_slot *menu_slots;
hero_data *hero_slots;
enemy_data *enemy_slots;
ACTION_TYPE *action_slots;
BYTE *turn_order;

#define valloc(struct_name, count) (struct_name *) &VM_GLOBAL(MAX_GLOBAL_VARS+v_cursor);\
v_cursor+=((sizeof(struct_name) * count) / sizeof(UWORD))

void init_extra_data(void) OLDCALL BANKED {
  BYTE v_cursor = MAX_GLOBAL_VARS;
  action_slots = valloc(ACTION_TYPE, 16);

  hero_slots = valloc(hero_data, 4);
  enemy_slots = valloc(enemy_data, 6);

  turn_order = valloc(BYTE, 10);

  item_slots = valloc(item_slot, MAX_ITEM_SLOTS);
  menu_slots = valloc(item_slot, MAX_ITEM_SLOTS);

  for(UBYTE i=0;i<4;i++){
    hero_slots[i].job = i;
    strcpy(hero_slots[i].name, "");
    hero_slots[i].idx = i;
  }
}