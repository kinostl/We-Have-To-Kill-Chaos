#include "action_handler.h"
#include <asm/sm83/types.h>
#include <asm/types.h>
#include <data/game_globals.h>
#include <data/rpg_combat_animation_states.h>
#include <game_time.h>
#include <gb/gb.h>
#include <ui.h>
#include <vm.h>
#pragma bank 255

#include "load_font_into_bg.h"
#include "states/rpg_combat.h"

RPG_ANIMATION_STATE rpg_animation_state;

script_state_t state_events[RPG_ANIMATION_STATE_LENGTH];

void rpg_combat_init(void) BANKED {
  loadFontIntoBkg();
  ui_set_pos(20 << 3, 0);
  dispatch_action(ATTACKER_TakeNextTurn);
}

void rpg_combat_update(void) BANKED {
  take_action();
}

void assign_state_script(SCRIPT_CTX * THIS) OLDCALL BANKED {
    UWORD *slot = VM_REF_TO_PTR(FN_ARG2);
    UBYTE *bank = VM_REF_TO_PTR(FN_ARG1);
    UBYTE **ptr = VM_REF_TO_PTR(FN_ARG0);
    state_events[*slot].script_bank = *bank;
    state_events[*slot].script_addr = *ptr;
}