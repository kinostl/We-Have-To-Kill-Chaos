#include "extra_data.h"
#include "states/rpg_combat.h"
#include <data/game_globals.h>
#include <macro.h>
#include <string.h>
#include <types.h>
#include <ui.h>
#include <vm.h>
#pragma bank 255
#include "action_definitions.h"
#include "action_handler.h"
#include <data/rpg_combat_animation_states.h>

BYTE action_head_cursor;
BYTE action_tail_cursor;
BYTE turn_cursor;

#define action_tail action_slots[action_tail_cursor]
#define action_head action_slots[action_head_cursor]
#define current_actor turn_order[turn_cursor]

void take_action(void) BANKED;
void animate(RPG_ANIMATION_STATE rpg_animation_state) BANKED;

void init_actions(void) BANKED {
  action_tail_cursor = 0;
  action_head_cursor = 0;
  ACTION_TYPE clean_action;

  for(int i=0;i<16;i++){
    memcpy(&action_slots[i], &clean_action, sizeof(ACTION_TYPE));
  }
}

void dispatch_action(ACTION_TYPE action_data) BANKED {
  action_tail = action_data;
  action_tail_cursor++;
}

void handle_action(ACTION_TYPE action_type) BANKED {
  switch (action_type) {
  case ATTACKER_Fight:
    break;
  case ATTACKER_StartNextTurn:
    turn_cursor--;
    if(turn_cursor < 0){
      dispatch_action(TURN_BuildInitiative);
    }else{
      dispatch_action(ATTACKER_TakeNextTurn);
    }
    break;
  case ATTACKER_TakeNextTurn:
    if (current_actor < 4 && current_actor > -1) {
      attacker_prepareNextTurn_Hero();
      //Panel Management
      dispatch_action(PANEL_HidePartyActors);
      dispatch_action(PANEL_ClosePanel);
      dispatch_action(PANEL_DisplayMenu);
      dispatch_action(PANEL_OpenPanel);
      dispatch_action(PANEL_DisplayCurrentActor);
      
      dispatch_action(PICK_GetPlayerChoice);
    } else if (current_actor > 3) {
      attacker_prepareNextTurn_Enemy();
    }
    break;
  case DEFENDER_TakeDamage:
    break;
  case PANEL_ClosePanel:
    dispatch_action(PANEL_OpenPanel);
    ui_move_to(20 << 3, 0 << 3, 1);
    ui_run_modal(UI_WAIT_WINDOW);
    break;
  case PANEL_DisplayCurrentActor:
    break;
  case PANEL_DisplayMenu:
    break;
  case PANEL_DisplayParty:
    break;
  case PANEL_DisplayPartyActors:
    break;
  case PANEL_HideCurrentActor:
    break;
  case PANEL_HidePartyActors:
    break;
  case PANEL_LoadItems:
    break;
  case PANEL_OpenPanel:
    dispatch_action(PANEL_ClosePanel);
    dispatch_action(PICK_GetPlayerChoice);
    ui_set_pos(20 << 3 , 0);
    ui_move_to(12 << 3, 0 << 3, 1);
    ui_run_modal(UI_WAIT_WINDOW);
    break;
  case PICK_GetPlayerChoice:
    animate(ANIMATE_PLAYER_ATTACKING);
    break;
  case PICK_Item:
    break;
  case PICK_Magic:
    break;
  case PICK_Run:
    break;
  case REPORT_AttackResults:
    break;
  case REPORT_Prepare:
    break;
  case REPORT_RejectMenuChoice:
    break;
  case SCENE_FadeIn:
    break;
  case TURN_BuildInitiative:
    dispatch_action(TURN_RollInitiative);
    dispatch_action(TURN_SortInitiative);
    dispatch_action(ATTACKER_StartNextTurn);
    break;
  case TURN_RollInitiative:
    turn_rollInitiative();
    break;
  case TURN_SortInitiative:
    turn_cursor = turn_sortInitiative();
    break;
  }
}

void take_action(void) BANKED {
  handle_action(action_head);
  action_head_cursor++;

  if(action_head_cursor>action_tail_cursor){
    action_head_cursor=0;
    action_tail_cursor=0;
  }
}

void animate(RPG_ANIMATION_STATE rpg_animation_state) BANKED {
  if (state_events[rpg_animation_state].script_addr != 0) {
    script_execute(state_events[rpg_animation_state].script_bank,
                   state_events[rpg_animation_state].script_addr, 0, 0);
  }
}