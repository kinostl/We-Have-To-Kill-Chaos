#include "extra_data.h"
#include <string.h>
#include <types.h>
#include <vm.h>
#pragma bank 255
#include "action_data.h"
#include <gb/crash_handler.h>

BYTE action_cursor;
#define action_ptr action_slots[action_cursor]

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
    break;
  case ATTACKER_TakeNextTurn:
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
    break;
  case TURN_RollInitiative:
    break;
  case TURN_SortInitiative:
    break;
  }
}
void take_action(void) BANKED {
  handle_action(action_ptr);
  action_cursor--;
  if (action_cursor < 0) {
    action_cursor = 0;
  }
}
