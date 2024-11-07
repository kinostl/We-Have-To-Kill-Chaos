#include "extra_data.h"
#include "action_handler.h"
#include "armor_data.h"
#include "entity_data.h"
#include "hero_data.h"
#include "item_slot.h"
#include "weapon_data.h"
#include <asm/types.h>
#include <data/game_globals.h>
#include <string.h>
#include <vm.h>
#pragma bank 255

entity_data *turn_slots;
weapon_data *weapon_slots;
armor_data *armor_slots;
armor_data *shield_slots;
armor_data *helmet_slots;
armor_data *glove_slots;
item_slot *item_slots;
item_slot *menu_slots;
hero_data *hero_slots;
ACTION_TYPE *action_slots;
BYTE *turn_order;

#define valloc(struct_name, count) (struct_name *) &VM_GLOBAL(MAX_GLOBAL_VARS+v_cursor);\
v_cursor+=((sizeof(struct_name) * count) / sizeof(UWORD))

void init_extra_data(void) OLDCALL BANKED {
  BYTE v_cursor = MAX_GLOBAL_VARS;
  action_slots = valloc(ACTION_TYPE, 16);

  hero_slots = valloc(hero_data, 4);

  turn_order = valloc(BYTE, 10);
  turn_slots = valloc(entity_data, 10);

  weapon_slots = valloc(weapon_data, 4);

  armor_slots = valloc(armor_data, 4);
  shield_slots = valloc(armor_data, 4);
  helmet_slots = valloc(armor_data, 4);
  glove_slots = valloc(armor_data, 4);

  item_slots = valloc(item_slot, MAX_ITEM_SLOTS);
  menu_slots = valloc(item_slot, MAX_ITEM_SLOTS);

  for(UBYTE i=0;i<4;i++){
    hero_slots[i].job = i;
    strcpy(hero_slots[i].name, "");
    hero_slots[i].slot_id = i;
  }
}