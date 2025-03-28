#include "extra_data.h"
#include "action_handler.h"
#include "class_data.h"
#include "enemy_data.h"
#include "entity_data.h"
#include "hero_data.h"
#include "item_slot.h"
#include "skill_definitions.h"
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
turn_slot_t *head_slot;
hero_data * current_hero;
enemy_data * current_enemy;
ATTACK * damage_queue;
ATTACK * damage_queue_head;
ATTACK * damage_queue_tail;

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
  damage_queue = valloc(ATTACK, 18);
  damage_queue_head = damage_queue;
  damage_queue_tail = damage_queue;

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

  load_hero(&hero_slots[0], MONK);
  load_hero(&hero_slots[1], THIEF);
  load_hero(&hero_slots[2], RED_MAGE);
  load_hero(&hero_slots[3], BLACK_MAGE);

  strcpy(hero_slots[0].name, "ONCLER");
  strcpy(hero_slots[1].name, "TWOFER");
  strcpy(hero_slots[2].name, "THREEF");
  strcpy(hero_slots[3].name, "FOURNA");

  for (UBYTE i = 0; i < 4; i++) {
    hero_slots[i].ext.idx = i;
    hero_slots[i].ext.hp = hero_slots[i].ext.max_hp;
    hero_slots[i].ext.pos.w = 3;
    hero_slots[i].ext.pos.h = 3;
    hero_slots[i].ext.pos.x = 13;
    hero_slots[i].ext.pos.y = 2 + (i * 4);
    hero_slots[i].ext.damage = MAX(1, hero_slots[i].strength / 2);
    if (hero_slots[i].job == THIEF_ID)
      hero_slots[i].ext.damage = MAX(1, hero_slots[i].agility / 2);
    hero_slots[i].ext.matk = 1 + (hero_slots[i].intel / 4);
    turn_slots[i].entity = &hero_slots[i].ext;
  }

  for (UBYTE i = 0; i < 6; i++) {
    enemy_slots[i].ext.idx = i;
    turn_slots[i+4].entity = &enemy_slots[i].ext;
  }
}