#include "action_definitions.h"
#include "action_handler.h"
#include "extra_data.h"
#include <actor.h>
#include <asm/types.h>
#include <gbs_types.h>
#include <ui.h>
#include <vm.h>
#pragma bank 255

#include "states/rpg_combat.h"

RPG_ANIMATION_STATE rpg_animation_state;
BYTE rpg_lock=0;

script_state_t state_events[RPG_ANIMATION_STATE_LENGTH];

void rpg_combat_init(void) BANKED {
  overlay_priority = 0;
  PLAYER.hidden = TRUE;
  ui_set_pos(20 << 3, 0 << 3);
  dispatch_action(TURN_BuildInitiative);
}

void rpg_combat_update(void) BANKED {
  if (!rpg_lock) {
    take_action();
  }
}

void assign_state_script(SCRIPT_CTX * THIS) OLDCALL BANKED {
    UWORD *slot = VM_REF_TO_PTR(FN_ARG2);
    UBYTE *bank = VM_REF_TO_PTR(FN_ARG1);
    UBYTE **ptr = VM_REF_TO_PTR(FN_ARG0);
    state_events[*slot].script_bank = *bank;
    state_events[*slot].script_addr = *ptr;
}

void assign_hero_actors(SCRIPT_CTX *THIS) OLDCALL BANKED {
  UBYTE actor_ids[4] = {
      *(UBYTE *)VM_REF_TO_PTR(FN_ARG0),
      *(UBYTE *)VM_REF_TO_PTR(FN_ARG1),
      *(UBYTE *)VM_REF_TO_PTR(FN_ARG2),
      *(UBYTE *)VM_REF_TO_PTR(FN_ARG3),
  };

  for (UBYTE i = 0; i < 4; i++) {
    hero_slots[i].actor = &actors[actor_ids[i]];
  }
}


void assign_damage_actors(SCRIPT_CTX *THIS) OLDCALL BANKED {
  UBYTE actor_ids[3] = {
      *(UBYTE *)VM_REF_TO_PTR(FN_ARG0),
      *(UBYTE *)VM_REF_TO_PTR(FN_ARG1),
      *(UBYTE *)VM_REF_TO_PTR(FN_ARG2),
  };

  for (UBYTE i = 0; i < 3; i++) {
    damage_numbers[i] = &actors[actor_ids[i]];
  }
}