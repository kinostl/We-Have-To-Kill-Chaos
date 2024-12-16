#include "skill_definitions.h"
#include "action_definitions.h"
#include "action_handler.h"
#include "animations.h"
#include "battle_headers.h"
#include "entity_data.h"
#include "enums.h"
#include "extra_data.h"
#include "ff_debug.h"
#include "ff_text.h"
#include "ff_util.h"
#include "position_data.h"
#include "skill_data.h"
#include "states/rpg_combat.h"
#include <asm/types.h>
#include <data/rpg_combat_animation_states.h>
#include <math.h>
#include <string.h>
#include <ui.h>

#pragma bank 255

void do_targetted_attack(entity_data *attacker, entity_data *defender,
                         BATTLE_SKILL skill) BANKED;

/*
Effect: An attack thats more powerful if you're close in level to the target

Normal Attack
* 0.75
* 8
* Small Max HP / Big Max HP

Short name: GobPun
*/
void skill_goblin_punch(entity_data *attacker, entity_data *defender) BANKED {
  WORD distance = DISTANCE(attacker->max_hp, defender->max_hp);
  WORD modifier = 8 - CLAMP(distance, 0, 7);

  const UBYTE atk_dmg = attacker->damage;
  UBYTE damage_calc = MAX(drand(atk_dmg, atk_dmg * 2), 1);
  damage_calc -= DIV_4(atk_dmg);
  damage_calc *= modifier;

  defender_TakeDamage(attacker, defender, damage_calc);
}

void skill_fight(entity_data *attacker, entity_data *defender) BANKED {
  const UBYTE atk_dmg = attacker->damage;
  const UBYTE damage_calc = MAX(drand(atk_dmg, atk_dmg * 2), 1);
  defender_TakeDamage(attacker, defender, damage_calc);
}

void skill_rune_sword(entity_data *attacker,
                                entity_data *defender) BANKED {
  const UBYTE atk_dmg = attacker->damage;
  const UBYTE damage_calc = MAX(drand(atk_dmg, atk_dmg * 2), 1);
  defender_TakeMagicDamage(attacker, defender, damage_calc, attacker->hit_chance);
  do_targetted_attack(attacker, defender, FIGHT);
}

ATTACK_RESULTS skill_cover(entity_data *attacker, entity_data *ally) BANKED {
  ally->status |= DEFENDING;
  return ATTACK_HIT;
}

void do_targetted_attack(entity_data *attacker, entity_data *defender,
                                   BATTLE_SKILL skill) BANKED {
  switch (skill) {
  case FIGHT:
    skill_fight(attacker, defender);
    break;
  case GOBLIN_PUNCH:
    skill_goblin_punch(attacker, defender);
    break;
  case LUSTER:
    skill_rune_sword(attacker, defender);
    break;
  default:
    return;
  }

  damage_queue_tail++;
}

ATTACK_RESULTS do_targetted_support(entity_data *attacker, entity_data *ally,
                                    BATTLE_SKILL skill) BANKED {
  switch (skill) {
  case COVER:
    return skill_cover(attacker, ally);
  default:
    return ATTACK_MISSED;
  }
}

void handle_targeted_attack(BATTLE_SKILL skill) BANKED {
  if (!current_turn->is_enemy) {
    LOG("+> is hero");
    const UBYTE target_enemy = rpg_get_target_enemy();
    current_enemy = &enemy_slots[target_enemy];
    do_targetted_attack(current_turn->entity, &current_enemy->ext, skill);

    setup_explosions(&current_enemy->ext.pos);
    dispatch_action(ANIMATE_PlayerAttacking);
    dispatch_action(ANIMATE_Explosions);
    dispatch_action(ANIMATE_DamageNumbers);
  } else {
    LOG("+> is enemy");
    UBYTE target_enemy = drand(0, 4);
    entity_data * target = &hero_slots[target_enemy].ext;
    while (target->status & DEAD) {
      target_enemy = drand(0, 4);
      target = &hero_slots[target_enemy].ext;
    }
    do_targetted_attack(current_turn->entity, target, skill);

    setup_explosions(&target->pos);
    dispatch_action(ANIMATE_EnemyAttacking);

    if (skill != FIGHT) {
      dispatch_action(MODAL_Open);
      dispatch_action(MODAL_Hold);
      dispatch_action(MODAL_Close);
    }

    dispatch_action(ANIMATE_Explosions);
    dispatch_action(ANIMATE_DamageNumbers);
    dispatch_action(PANEL_UpdateParty);
  }
}

void handle_targeted_support(BATTLE_SKILL skill) BANKED {
  const UBYTE target_ally = rpg_get_target_ally(FALSE);
  do_targetted_support(current_turn->entity, &hero_slots[target_ally].ext, skill);
  dispatch_action(PANEL_UpdateParty);
}

void prepare_for_skill(BATTLE_SKILL skill) BANKED {
  switch (skill) {
  case COVER:
    dispatch_action(ANIMATE_HideActivePlayer);
    dispatch_action(PANEL_ClosePanel);
    dispatch_action(PANEL_DisplayParty);
    dispatch_action(PANEL_OpenPanel);
    dispatch_action(PANEL_DisplayPartyActors);
    return;
  default:
    return;
  }
}

void handle_skill(BATTLE_SKILL skill) BANKED {
  switch (skill) {
  case FIGHT:
  case GOBLIN_PUNCH:
  case LUSTER:
    handle_targeted_attack(skill);
    break;
  case COVER:
    handle_targeted_support(skill);
    break;
  case BLADE_BLITZ:
  case FIRE:
  case ICE:
  case HARM:
  case HEAL:
  case HOWL:
  case THRASH:
  case BLANK:
    dispatch_action(PICK_GetPlayerActionChoice);
    return;
  }

  dispatch_action(ATTACKER_FinishTurn);
}

void display_skill(BATTLE_SKILL skill) BANKED{
  skill_data s_data;
  load_skill(&s_data, skill);
  load_battle_message(s_data.name);
}