#include "enums.h"
#include "extra_data.h"
#include "states/rpg_combat.h"
#include <data/game_globals.h>
#include <macro.h>
#include <stdbool.h>
#include <string.h>
#include <types.h>
#include <ui.h>
#include <vm.h>
#pragma bank 255
#include "action_definitions.h"
#include "action_handler.h"
#include <data/rpg_combat_animation_states.h>
#include "handle_menu.h"
#include <vm_ui.h>

BYTE action_head_cursor;
BYTE action_tail_cursor;
BYTE turn_cursor;
UBYTE rpg_player_choice;

#define action_tail action_slots[action_tail_cursor]
#define action_head action_slots[action_head_cursor]
#define current_actor turn_order[turn_cursor]

void take_action(void) BANKED;
void animate(RPG_ANIMATION_STATE rpg_animation_state) BANKED;
void ui_draw_frame(UBYTE x, UBYTE y, UBYTE width, UBYTE height) BANKED;
void handle_skill(UBYTE skill_id) BANKED;

inline void ui_display_text() {
  // Could technically call vm_display_text but vm calls are bad practice
  ui_draw_frame(0, 0, 8, 18);
  text_drawn = text_ff = FALSE;
  ui_set_start_tile(TEXT_BUFFER_START, 0);
  ui_run_modal(UI_WAIT_TEXT);
}

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
    current_actor = 0;
    if (current_actor < 4 && current_actor > -1) {
      dispatch_action(PANEL_HidePartyActors);
      dispatch_action(PANEL_ClosePanel);
      dispatch_action(PANEL_DisplayMenu);
      dispatch_action(PANEL_OpenPanel);
      dispatch_action(PANEL_DisplayCurrentActor);
      
      dispatch_action(PICK_GetPlayerActionChoice);
    } else if (current_actor > 3) {
      attacker_prepareNextTurn_Enemy();
    }
    break;
  case DEFENDER_TakeDamage:
    defender_TakeDamage(&hero_slots[current_actor].ext,
                        &enemy_slots[rpg_player_choice].ext);
    animate(ANIMATE_PLAYER_ATTACKING);
    break;
  case PANEL_ClosePanel:
    ui_move_to(20 << 3, 0 << 3, text_out_speed);
    ui_run_modal(UI_WAIT_WINDOW);
    break;
  case PANEL_DisplayCurrentActor:
    break;
  case PANEL_DisplayMenu:
    loadHeroMenu();
    ui_display_text();
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
    ui_set_pos(20 << 3 , 0);
    ui_move_to(12 << 3, 0 << 3, text_in_speed);
    ui_run_modal(UI_WAIT_WINDOW);
    break;
  case PICK_GetPlayerActionChoice:
    rpg_player_choice = rpg_run_menu();
    switch (rpg_player_choice) {
    case 5:
      dispatch_action(PICK_Item);
      break;
    case 6:
      dispatch_action(PICK_Magic);
      break;
    case 7:
      dispatch_action(PICK_Block);
      break;
    case 8:
      dispatch_action(PICK_Run);
      break;
    default:
      handle_skill(rpg_player_choice);
      break;
    }
    dispatch_action(ATTACKER_StartNextTurn);
    break;
  case PICK_GetPlayerTargetAlly:
    rpg_player_choice = rpg_get_target_ally();
    break;
  case PICK_GetPlayerTargetEnemy:
    rpg_player_choice = rpg_get_target_enemy();
    break;
  case PICK_Item:
    break;
  case PICK_Magic:
    break;
  case PICK_Block:
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
    turn_rollInitiative();
    turn_cursor = turn_sortInitiative();
    dispatch_action(ATTACKER_StartNextTurn);
    break;
  }
}

void take_action(void) BANKED {
  if(action_tail_cursor == 0){
    return;
  }

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

void handle_skill(UBYTE menu_id) BANKED {
  const BATTLE_SKILL skill = hero_slots[0].ext.skills[menu_id];
  switch (skill) {
  case FIGHT:
    dispatch_action(PICK_GetPlayerTargetEnemy);
    dispatch_action(DEFENDER_TakeDamage);
    dispatch_action(ATTACKER_Fight);
    break;
  case SHIELD_SKILL:
  case LUSTER:
  case FIRE:
  case ICE:
  case HARM:
  case HEAL:
  case GOBLIN_PUNCH:
  case HOWL:
  case THRASH:
  case RUNE_SWORD_SKILL:
  case BLANK:
    dispatch_action(PICK_GetPlayerActionChoice);
    break;
  }
}