#include "enums.h"
#include "extra_data.h"
#include "states/rpg_combat.h"
#include <data/game_globals.h>
#include <macro.h>
#include <stdbool.h>
#include <types.h>
#include <ui.h>
#include <vm.h>
#pragma bank 255
#include "action_definitions.h"
#include "action_handler.h"
#include "handle_menu.h"
#include "position.h"
#include <data/rpg_combat_animation_states.h>
#include <vm_ui.h>
#include "input.h"
#include "rand.h" // IWYU pragma: keep

BYTE turn_cursor;

#define current_actor turn_order[turn_cursor]

void take_action(void) BANKED;
void animate(RPG_ANIMATION_STATE rpg_animation_state) BANKED;
void ui_draw_frame(UBYTE x, UBYTE y, UBYTE width, UBYTE height) BANKED;
void handle_skill(UBYTE skill_id) BANKED;

inline void ui_display_text(void) {
  // Could technically call vm_display_text but vm calls are bad practice
  ui_draw_frame(0, 0, 8, 18);
  INPUT_RESET;
  text_options = TEXT_OPT_DEFAULT;
  text_drawn = text_ff = FALSE;
  ui_set_start_tile(TEXT_BUFFER_START, 0);
  ui_run_modal(UI_WAIT_TEXT);
}

inline void ui_move_to_xy(UBYTE x, UBYTE y, UBYTE speed){
    win_dest_pos_y = y << 3;
    win_dest_pos_x = x << 3;
    win_speed = speed;
}

inline void ui_set_pos_to_xy(UBYTE x, UBYTE y) {
  win_pos_y = win_dest_pos_y = (y << 3);
  win_pos_x = win_dest_pos_x = (x << 3);
}

void init_actions(void) BANKED {
  ACTION_TYPE clean_action;

  for (int i = 0; i < 16; i++) {
    action_slots[i].action = clean_action;
  }
}

void dispatch_action(ACTION_TYPE action_data) BANKED {
  action_tail->action = action_data;
  action_tail = action_tail->next;
}

void handle_action(ACTION_TYPE action_type) BANKED {
  switch (action_type) {
  case ATTACKER_Fight: {
    if (current_actor < 4) {
      const UBYTE target_enemy = rpg_get_target_enemy() + 4;
      ATTACK_RESULTS attack_results = defender_TakeDamage(
          turn_slots[current_actor], turn_slots[target_enemy]);

      if (attack_results & CRITICAL_HIT) {
        // animate critical hit
      } else if (attack_results & ATTACK_HIT) {
        animate(ANIMATE_PLAYER_ATTACKING);
      } else if (attack_results & CRITICAL_MISS) {
        // animate critical miss
      } else if (attack_results & ATTACK_MISSED) {
        // animate miss
      }

      if (attack_results & TARGET_DEFEATED) {
        // animate target defeateated
      }
    } else {
      const UBYTE target_enemy = rand() % 4;
      ATTACK_RESULTS attack_results = defender_TakeDamage(
          turn_slots[current_actor], turn_slots[target_enemy]);

      animate(ANIMATE_ENEMY_ATTACKING);
      if (attack_results & CRITICAL_HIT) {
        // animate critical hit
      } else if (attack_results & ATTACK_HIT) {
        // animate attack
      } else if (attack_results & CRITICAL_MISS) {
        // animate critical miss
      } else if (attack_results & ATTACK_MISSED) {
        // animate miss
      }

      if (attack_results & TARGET_DEFEATED) {
        // animate target defeateated
      }
    }

    dispatch_action(ATTACKER_StartNextTurn);
    break;
  }
  case ATTACKER_StartNextTurn: {
    BOOLEAN enemies_still_alive = FALSE;
    for (UBYTE i = 0; i < 6; i++) {
      if (enemy_slots[i].ext.alive) {
        enemies_still_alive = TRUE;
        break;
      }
    }

    if (!enemies_still_alive) {
      // handle winning
      break;
    }

    BOOLEAN heros_still_alive = FALSE;
    for (UBYTE i = 0; i < 6; i++) {
      if (hero_slots[i].ext.alive) {
        heros_still_alive = TRUE;
        break;
      }
    }

    if (!heros_still_alive) {
      // handle losing
      break;
    }

    turn_cursor--;
    if (turn_cursor < 0) {
      dispatch_action(TURN_BuildInitiative);
    } else {
      dispatch_action(ATTACKER_TakeNextTurn);
    }
    break;
  }
  case ATTACKER_TakeNextTurn:

    if (!turn_slots[current_actor]->alive) {
      dispatch_action(ATTACKER_StartNextTurn);
      break;
    }

    if (current_actor < 4) {
      dispatch_action(PANEL_HidePartyActors);
      dispatch_action(PANEL_ClosePanel);
      dispatch_action(PANEL_DisplayMenu);
      dispatch_action(PANEL_OpenPanel);
      dispatch_action(PANEL_DisplayCurrentActor);

      dispatch_action(PICK_GetPlayerActionChoice);
    } else if (current_actor > 3) {
      dispatch_action(PANEL_HidePartyActors);
      dispatch_action(PANEL_ClosePanel);
      dispatch_action(PANEL_DisplayParty);
      dispatch_action(PANEL_OpenPanel);
      dispatch_action(PANEL_DisplayPartyActors);

      dispatch_action(PICK_GetEnemyActionChoice);
    }
    break;

  case PANEL_ClosePanel:
    ui_move_to_xy(20, 0, text_out_speed);
    ui_run_modal(UI_WAIT_WINDOW);
    break;
  case PANEL_DisplayCurrentActor:
    if (current_actor < 4) {
      hero_slots[current_actor].actor->pos.x = pos(14);
      hero_slots[current_actor].actor->pos.y = pos(4);
      hero_slots[current_actor].actor->hidden = FALSE;
    }
    break;
  case PANEL_DisplayMenu:
    loadHeroMenu();
    ui_display_text();
    break;
  case PANEL_DisplayParty:
    loadPartyMenu();
    ui_display_text();
    break;
  case PANEL_DisplayPartyActors:
    for(BYTE i=0;i<4;i++){
      hero_slots[i].actor->pos.x = pos(14);
      hero_slots[i].actor->pos.y = pos(4 + (4*i));
      hero_slots[i].actor->hidden = FALSE;
    }
    break;
  case PANEL_HideCurrentActor:
    break;
  case PANEL_HidePartyActors:
    for(BYTE i=0;i<4;i++){
      hero_slots[i].actor->hidden = TRUE;
    }
    break;
  case PANEL_LoadItems:
    break;
  case PANEL_OpenPanel:
    ui_set_pos_to_xy(20, 0);
    ui_move_to_xy(12, 0, text_in_speed);
    ui_run_modal(UI_WAIT_WINDOW);
    break;
  case PICK_GetPlayerActionChoice: {
    UBYTE player_choice = rpg_run_menu();
    switch (player_choice) {
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
      handle_skill(player_choice);
      break;
    }
    dispatch_action(ATTACKER_StartNextTurn);
    break;
  }
  case PICK_GetEnemyActionChoice:
    dispatch_action(ATTACKER_Fight);
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
  handle_action(action_head->action);
  action_head = action_head->next;
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