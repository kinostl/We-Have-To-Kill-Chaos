#include "enemy_data.h"
#include "entity_data.h"
#include "enums.h"
#include "extra_data.h"
#include "ff_text.h"
#include "ff_util.h"
#include "hero_data.h"
#include "load_font_into_bg.h"
#include "states/rpg_combat.h"
#include "turn_slots.h"
#include <actor.h>
#include <data/game_globals.h>
#include <gb/cgb.h>
#include <gb/gb.h>
#include <macro.h>
#include <stdbool.h>
#include <string.h>
#include <types.h>
#include <ui.h>
#include <vm.h>
#pragma bank 255
#include "action_definitions.h"
#include "action_handler.h"
#include "handle_menu.h"
#include "input.h"
#include "position.h"
#include "rand.h" // IWYU pragma: keep
#include <data/rpg_combat_animation_states.h>
#include <vm_ui.h>
#include "ff_debug.h"
#include "animations.h"
#include "skill_definitions.h"
#include "data/explosion_palettes.h"
#include <palette.h>

BYTE turn_cursor;
TURN_TYPE prev_turn_type=NO_TURN;
UBYTE player_choice;

void take_action(void) BANKED;


void init_actions(void) BANKED {

  for (int i = 0; i < 16; i++) {
    action_slots[i].action = EMPTY_ACTION;
  }
}

void dispatch_action(ACTION_TYPE action_data) BANKED {
#if VERBOSE
  switch (action_data) {
  case TURN_BuildInitiative:
    LOG("Dispatch: TURN_BuildInitiative");
    break;
  case ATTACKER_TakeNextTurn:
    LOG("Dispatch: ATTACKER_TakeNextTurn");
    break;
  case ATTACKER_StartNextTurn:
    LOG("Dispatch: ATTACKER_StartNextTurn");
    break;
  case PANEL_HidePartyActors:
    LOG("Dispatch: PANEL_HidePartyActors");
    break;
  case PANEL_ClosePanel:
    LOG("Dispatch: PANEL_ClosePanel");
    break;
  case PANEL_DisplayMenu:
    LOG("Dispatch: PANEL_DisplayMenu");
    break;
  case PANEL_OpenPanel:
    LOG("Dispatch: PANEL_OpenPanel");
    break;
  case PANEL_DisplayCurrentActor:
    LOG("Dispatch: PANEL_DisplayCurrentActor");
    break;
  case PICK_GetPlayerActionChoice:
    LOG("Dispatch: PICK_GetPlayerActionChoice");
    break;
  case PANEL_DisplayParty:
    LOG("Dispatch: PANEL_DisplayParty");
    break;
  case PANEL_UpdateParty:
    LOG("Dispatch: PANEL_UpdateParty");
    break;
  case PANEL_DisplayPartyActors:
    LOG("Dispatch: PANEL_DisplayPartyActors");
    break;
  case PICK_GetEnemyActionChoice:
    LOG("Dispatch: PICK_GetEnemyActionChoice");
    break;
  case EMPTY_ACTION:
    LOG("Dispatch: EMPTY_ACTION");
    break;
  case ATTACKER_FinishTurn:
    LOG("Dispatch: ATTACKER_FinishTurn");
    break;
  case PANEL_HideCurrentActor:
    LOG("Dispatch: PANEL_HideCurrentActor");
    break;
  case PANEL_LoadItems:
    LOG("Dispatch: PANEL_LoadItems");
    break;
  case PICK_Item:
    LOG("Dispatch: PICK_Item");
    break;
  case PICK_Magic:
    LOG("Dispatch: PICK_Magic");
    break;
  case PICK_Guard:
    LOG("Dispatch: PICK_Guard");
    break;
  case PICK_Run:
    LOG("Dispatch: PICK_Run");
    break;
  case REPORT_AttackResults:
    LOG("Dispatch: REPORT_AttackResults");
    break;
  case REPORT_Prepare:
    LOG("Dispatch: REPORT_Prepare");
    break;
  case REPORT_RejectMenuChoice:
    LOG("Dispatch: REPORT_RejectMenuChoice");
    break;
  case SCENE_FadeIn:
    LOG("Dispatch: SCENE_FadeIn");
    break;
  }

  if (action_tail->next->action != EMPTY_ACTION) {
    LOG("action_tail met action_head");
    __HandleCrash();
  }
#endif
  action_tail->action = action_data;
  action_tail = action_tail->next;
}


void handle_action(ACTION_TYPE action_type) BANKED {
  EMU_BREAKPOINT;
  switch (action_type) {
  case EMPTY_ACTION:
#if VERBOSE
    LOG("Attempted to handle empty action");
    __HandleCrash();
#endif
    break;
  case ANIMATE_EnemyDefeated:
    animate(ANIMATE_ENEMY_DEFEATED);
    break;
  case ANIMATE_DamageNumbers:
    animate(ANIMATE_DAMAGE_NUMBERS);
    break;
  case ANIMATE_PlayerAttacking:
    animate(ANIMATE_PLAYER_ATTACKING);
    break;
  case ANIMATE_EnemyAttacking:
    animate(ANIMATE_ENEMY_ATTACKING);
    break;
  case ANIMATE_EndPlayerTurn:
    animate(ANIMATE_HIDE_ACTIVE_PLAYER);
    break;
  case ANIMATE_Explosions:
    animate(ANIMATE_EXPLOSIONS);
    break;
  case ANIMATE_HideActivePlayer:
    animate(ANIMATE_HIDE_ACTIVE_PLAYER);
    break;
  case MODAL_Open:
    ui_move_to_xy(0, 15, text_in_speed);
    ui_run_modal(UI_WAIT_WINDOW);
    break;
  case MODAL_Hold:
    for(UBYTE i=0;i<30;i++){
      vsync();
    }
    break;
  case MODAL_Close:
    close_battle_message();
    break;
  case ATTACKER_FinishTurn: {
    LOG("handle: ATTACKER_FinishTurn");

    if (current_turn->is_enemy) {
      prev_turn_type = ENEMY_TURN;
    } else {
      prev_turn_type = PLAYER_TURN;
    }

    current_turn = current_turn->next;
    dispatch_action(ANIMATE_EndPlayerTurn);
    dispatch_action(ATTACKER_StartNextTurn);
    break;
  }
  case EXPLOSIONS_SetDefault:
    load_explosion_palette(FALSE, 5, EXPLOSION_DEFAULT);
    break;
  case EXPLOSIONS_SetYellow:
    load_explosion_palette(FALSE, 5, EXPLOSION_YELLOW);
    break;
  case EXPLOSIONS_SetWhite:
    load_explosion_palette(FALSE, 5, EXPLOSION_WHITE);
    break;
  case ATTACKER_StartNextTurn: {
    LOG("handle: ATTACKER_StartNextTurn");

    BOOLEAN enemies_are_dead = TRUE;
    for (UBYTE i = 0; i < 6; i++) {
      if (enemy_slots[i].ext.status & DEAD)
        continue;
      enemies_are_dead = FALSE;
      break;
    }

    if (enemies_are_dead) {
      LOG("+> enemies dead");
      LOG("===");
      animate(ANIMATE_PARTY_WIN);
      // handle winning
      break;
    }
    LOG("+> enemies alive");

    BOOLEAN heros_are_dead = TRUE;
    for (UBYTE i = 0; i < 4; i++) {
      if (hero_slots[i].ext.status & DEAD)
        continue;
      heros_are_dead = FALSE;
      break;
    }

    if (heros_are_dead) {
      LOG("+> heroes dead");
      LOG("===");
      animate(ANIMATE_PARTY_LOSE);
      // handle losing
      break;
    }
    LOG("+> heroes alive");

    if (current_turn == NULL) {
      LOG("+-reset initiative");
      dispatch_action(TURN_BuildInitiative);
    } else {
      LOG("+-take turn");
      dispatch_action(ATTACKER_TakeNextTurn);
    }
    break;
  }
  case ATTACKER_TakeNextTurn:
    LOG("handle: ATTACKER_TakeNextTurn");
    if (current_turn->entity->status & DEAD) {
      LOG("entity dead, skip turn");
      current_turn = current_turn->next;
      dispatch_action(ATTACKER_StartNextTurn);
      break;
    }
    if (current_turn->is_enemy) {
      LOG("enemy alive, take turn");
      current_enemy = &enemy_slots[current_turn->entity->idx];
      current_hero = NULL;

      if (prev_turn_type == PLAYER_TURN) {
        dispatch_action(PANEL_HidePartyActors);
        dispatch_action(PANEL_ClosePanel);
        dispatch_action(PANEL_DisplayParty);
        dispatch_action(PANEL_OpenPanel);
        dispatch_action(PANEL_DisplayPartyActors);
      }

      dispatch_action(PICK_GetEnemyActionChoice);
    } else {
      LOG("hero alive, take turn");
      current_hero = &hero_slots[current_turn->entity->idx];
      current_enemy = NULL;
      dispatch_action(PANEL_HidePartyActors);
      dispatch_action(PANEL_ClosePanel);
      dispatch_action(PANEL_DisplayMenu);
      dispatch_action(PANEL_OpenPanel);
      dispatch_action(PANEL_DisplayCurrentActor);

      dispatch_action(PICK_GetPlayerActionChoice);
    }
    break;

  case PANEL_ClosePanel:
    LOG("handle: PANEL_ClosePanel");
    ui_move_to_xy(20, 0, text_out_speed);
    ui_run_modal(UI_WAIT_WINDOW);
    break;
  case PANEL_DisplayCurrentActor:
    LOG("handle: PANEL_DisplayCurrentActor");
    VM_GLOBAL(VAR_1_C) = hero_slots[current_turn->entity->idx].job;
    animate(BEGIN_PLAYER_TURN);
    break;
  case PANEL_DisplayMenu:
    LOG("handle: PANEL_DisplayMenu");
    loadHeroMenu(&hero_slots[current_turn->entity->idx]);
    ui_display_text();
    break;
  case PANEL_DisplayParty:
    LOG("handle: PANEL_DisplayParty");
    loadPartyMenu();
    ui_display_text();
    break;
  case PANEL_UpdateParty:
    LOG("handle: PANEL_UpdateParty");
    loadPartyMenu();
    ui_update_text();
    break;
  case PANEL_DisplayPartyActors:
    LOG("handle: PANEL_DisplayPartyActors");
    for (BYTE i = 0; i < 4; i++) {
      hero_slots[i].actor->pos.x = pos(14);
      hero_slots[i].actor->pos.y = pos(4 + (4 * i));
      hero_slots[i].actor->hidden = FALSE;
    }
    break;
  case PANEL_HideCurrentActor:
    break;
  case PANEL_HidePartyActors:
    LOG("handle: PANEL_HidePartyActors");
    for (BYTE i = 0; i < 4; i++) {
      hero_slots[i].actor->hidden = TRUE;
    }
    break;
  case PANEL_LoadItems:
    break;
  case PANEL_OpenPanel:
    LOG("handle: PANEL_OpenPanel");
    ui_set_pos_to_xy(20, 0);
    ui_move_to_xy(12, 0, text_in_speed);
    ui_run_modal(UI_WAIT_WINDOW);
    break;
  case PICK_GetPlayerActionChoice: {
    LOG("handle: PICK_GetPlayerActionChoice");
    player_choice = rpg_run_menu();
    switch (player_choice) {
    case 4:
      dispatch_action(PICK_Item);
      break;
    case 5:
      dispatch_action(PICK_Magic);
      break;
    case 6:
      dispatch_action(PICK_Guard);
      break;
    case 7:
      dispatch_action(PICK_Run);
      break;
    default: {
      current_hero = &hero_slots[current_turn->entity->idx];
      const BATTLE_SKILL skill = current_hero->ext.skills[player_choice];
      prepare_for_skill(skill);
      dispatch_action(PICK_Skill);
      break;
    }
    }
    break;
  }
  case PICK_GetEnemyActionChoice:{
    LOG("handle: PICK_GetEnemyActionChoice");

    enemy_data * actor = &enemy_slots[current_turn->entity->idx];
    const UBYTE spell_roll = drand(0, actor->ext.spell_chance);
    const UBYTE skill_roll = drand(0, actor->ext.skill_chance);

    if (spell_roll > 0) {
      // Check to see if theres spell stuff.
      // Do spell stuff
      handle_skill(FIGHT);
    } else if (skill_roll > 0) {
      BATTLE_SKILL skill = actor->ext.skills[actor->skill_idx];
      display_skill(skill);
      handle_skill(skill);
      actor->skill_idx++;
      if(actor->skill_idx > 3){
        actor->skill_idx = 0;
      }
    } else {
      handle_skill(FIGHT);
    }
    break;
  }
  case PICK_Item:
    break;
  case PICK_Magic:
    break;
  case PICK_Guard: {
    current_hero = &hero_slots[current_turn->entity->idx];
    if (current_hero->ap < 3) {
      current_hero->ap++;
    }
    animate(ANIMATE_PLAYER_CASTING);
    dispatch_action(ATTACKER_FinishTurn);
    break;
  }
  case PICK_Run:
    break;
  case PICK_Skill: {
    current_hero = &hero_slots[current_turn->entity->idx];
    const BATTLE_SKILL skill = current_hero->ext.skills[player_choice];
    handle_skill(skill);
    break;
  } 
  case TURN_BuildInitiative:
    LOG("handle: TURN_BuildInitiative");
    turn_rollInitiative();
    dispatch_action(ATTACKER_StartNextTurn);
    break;
  case TURN_EndTurn:
    break;
  }
}

void take_action(void) BANKED {
  handle_action(action_head->action);
  action_head->action = EMPTY_ACTION;
  action_head = action_head->next;
}

