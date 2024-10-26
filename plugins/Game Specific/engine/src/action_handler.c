#include "extra_data.h"
#include "states/rpg_combat.h"
#include <data/game_globals.h>
#include <macro.h>
#include <string.h>
#include <types.h>
#include <vm.h>
#pragma bank 255
#include "action_definitions.h"
#include "action_handler.h"
#include "data/action_flags.h"

BYTE action_cursor;
BYTE turn_cursor;
#define action_ptr action_slots[action_cursor]
#define current_actor turn_order[turn_cursor]

void take_action(void) BANKED;

void init_actions(void) BANKED {
  action_cursor = 0;
  ACTION_TYPE clean_action;

  for(int i=0;i<16;i++){
    memcpy(&action_slots[i], &clean_action, sizeof(ACTION_TYPE));
  }
}

void dispatch_action(ACTION_TYPE action_data) BANKED {
  action_cursor++;
  action_ptr = action_data;
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
      SET_FLAG(VM_GLOBAL(VAR_ACTION), ACTION_NAMED_FLAG);
      dispatch_action(PANEL_HidePartyActors);
      dispatch_action(PANEL_ClosePanel);
      dispatch_action(PANEL_DisplayMenu);
      dispatch_action(PANEL_OpenPanel);
      dispatch_action(PANEL_DisplayCurrentActor);
      
      dispatch_action(PICK_EnablePlayer);
    } else if (current_actor > 3) {
      attacker_prepareNextTurn_Enemy();
    }
    break;
  case DEFENDER_TakeDamage:
    break;
  case PANEL_ClosePanel:
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
    break;
  case PICK_ChoiceMade:
    break;
  case PICK_EnablePlayer:
    rpg_menu_mode = RPG_SELECT_MENU_ITEM_MODE;
    break;
  case PICK_HandleChoice:
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

  take_action();
}

void take_action(void) BANKED {
  handle_action(action_ptr);
  action_cursor--;
}
