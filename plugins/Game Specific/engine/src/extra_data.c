#include "extra_data.h"
#include "action_handler.h"
#include "enemy_data.h"
#include "entity_data.h"
#include "enums.h"
#include "hero_data.h"
#include "item_slot.h"
#include <asm/types.h>
#include <bankdata.h>
#include <data/game_globals.h>
#include <string.h>
#include <types.h>
#include <vm.h>

#pragma bank 255

item_slot *item_slots;
item_slot *menu_slots;
hero_data *hero_slots;
enemy_data *enemy_slots;
action_t * action_slots;
action_t * action_head;
action_t * action_tail;
turn_slot_t * turn_slots;
turn_slot_t * current_turn;

#define valloc(struct_name, count)                                             \
  (struct_name *)&VM_GLOBAL(MAX_GLOBAL_VARS + v_cursor);                       \
  v_cursor += ((sizeof(struct_name) * count) / sizeof(UWORD));                 \
  v_cursor++;

void init_extra_data(void) OLDCALL BANKED {
  UWORD v_cursor = 0;
  action_slots = valloc(action_t, 16);

  hero_slots = valloc(hero_data, 4);
  enemy_slots = valloc(enemy_data, 6);

  item_slots = valloc(item_slot, MAX_ITEM_SLOTS);
  menu_slots = valloc(item_slot, MAX_ITEM_SLOTS);
  turn_slots = valloc(turn_slot_t, 10);

#ifdef STRICT
#include <gb/crash_handler.h>
#include <gb/emu_debug.h>

  if (MAX_GLOBAL_VARS + v_cursor >= 512) {
    EMU_MESSAGE("Ran out of Script Memory due to Valloc");
    __HandleCrash();
  }
#endif

  for (UBYTE i = 0; i < 15; i++) {
    action_slots[i].next = &action_slots[i + 1];
  }

  action_slots[15].next = &action_slots[0];

  action_head = &action_slots[0];
  action_tail = &action_slots[0];

  for (UBYTE i = 0; i < 4; i++) {
    hero_slots[i].job = i;
    strcpy(hero_slots[i].name, "      ");
    hero_slots[i].idx = i;
    hero_slots[i].ext.skills[0] = FIGHT;
    hero_slots[i].ext.skills[1] = SHIELD_SKILL;
    hero_slots[i].ext.skills[2] = RUNE_SWORD_SKILL;
    hero_slots[i].ext.skills[3] = LUSTER;
    strcpy(hero_slots[i].name, "ONCLER");
    hero_slots[i].ap = 1;

    turn_slots[i].entity = &hero_slots[i].ext;
  }

  for (UBYTE i = 0; i < 6; i++) {
    enemy_slots[i].idx = i;
    strcpy(enemy_slots[i].name, "       ");

    turn_slots[i+4].entity = &enemy_slots[i].ext;
  }
}