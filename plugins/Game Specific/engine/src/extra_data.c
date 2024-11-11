#include "extra_data.h"
#include "action_handler.h"
#include "enemy_data.h"
#include "entity_data.h"
#include "enums.h"
#include "hero_data.h"
#include "item_slot.h"
#include "skill_data.h"
#include <asm/types.h>
#include <bankdata.h>
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
entity_data **turn_slots;

#define vtotal (VM_HEAP_SIZE + (VM_MAX_CONTEXTS * VM_CONTEXT_STACK_SIZE))
#define valloc(struct_name, count)                                             \
  (struct_name *)&VM_GLOBAL(MAX_GLOBAL_VARS + v_cursor);                       \
  v_cursor += ((sizeof(struct_name) * count) / sizeof(UWORD))

void init_extra_data(void) OLDCALL BANKED {
  UWORD v_cursor = 0;
  action_slots = valloc(ACTION_TYPE, 16);

  hero_slots = valloc(hero_data, 4);
  enemy_slots = valloc(enemy_data, 6);

  turn_order = valloc(BYTE, 10);

  item_slots = valloc(item_slot, MAX_ITEM_SLOTS);
  menu_slots = valloc(item_slot, MAX_ITEM_SLOTS);
  turn_slots = valloc(entity_data *, 10);

#ifdef STRICT
#include <gb/crash_handler.h>
#include <gb/emu_debug.h>

  if (MAX_GLOBAL_VARS + v_cursor >= 512) {
    EMU_MESSAGE("Ran out of Script Memory due to Valloc");
    __HandleCrash();
  }
#endif

  for (UBYTE i = 0; i < 4; i++) {
    hero_slots[i].job = i;
    strcpy(hero_slots[i].name, "      ");
    hero_slots[i].idx = i;
    turn_slots[i] = &hero_slots[i].ext;
    hero_slots[i].ext.skills[0] = FIGHT;
    hero_slots[i].ext.skills[1] = SHIELD_SKILL;
    hero_slots[i].ext.skills[2] = RUNE_SWORD_SKILL;
    hero_slots[i].ext.skills[3] = LUSTER;
    strcpy(hero_slots[i].name, "ONCLER");
    hero_slots[i].ap = 1;
  }
  for (UBYTE i = 0; i < 6; i++) {
    enemy_slots[i].idx = 4 + i;
    strcpy(enemy_slots[i].name, "       ");
    turn_slots[i + 4] = &enemy_slots[0].ext;
  }
}