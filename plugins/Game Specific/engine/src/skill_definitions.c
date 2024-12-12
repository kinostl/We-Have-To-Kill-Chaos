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
#include <math.h>
#include <string.h>
#include <ui.h>

#pragma bank 255

/*
Effect: An attack thats more powerful if you're close in level to the target

Normal Attack
* 0.75
* 8
* Small Max HP / Big Max HP

Short name: GobPun
*/
ATTACK_RESULTS skill_goblin_punch(entity_data *attacker,
                                  entity_data *defender) BANKED {
  WORD distance = DISTANCE(attacker->max_hp, defender->max_hp);
  WORD modifier = 8 - CLAMP(distance, 0, 7);

  const UBYTE atk_dmg = attacker->damage;
  UBYTE damage_calc = MAX(drand(atk_dmg, atk_dmg * 2), 1);
  damage_calc -= DIV_4(atk_dmg);
  damage_calc *= modifier;

  ATTACK_RESULTS attack_results =
      defender_TakeDamage(attacker, defender, damage_calc);

  return attack_results;
}

ATTACK_RESULTS skill_fight(entity_data *attacker,
                           entity_data *defender) BANKED {
  const UBYTE atk_dmg = attacker->damage;
  UBYTE damage_calc = MAX(drand(atk_dmg, atk_dmg * 2), 1);
  ATTACK_RESULTS attack_results =
      defender_TakeDamage(attacker, defender, damage_calc);

  return attack_results;
}

ATTACK_RESULTS skill_rune_sword(entity_data *attacker,
                                entity_data *defender) BANKED {
  const UBYTE atk_dmg = attacker->damage;
  UBYTE damage_calc = MAX(drand(atk_dmg, atk_dmg * 2), 1);
  ATTACK_RESULTS attack_results =
      defender_TakeMagicDamage(attacker, defender, damage_calc, attacker->hit_chance);

  return attack_results;
}

ATTACK_RESULTS do_targetted_attack(entity_data *attacker, entity_data *defender,
                                   BATTLE_SKILL skill) BANKED {
  switch (skill) {
  case FIGHT:
    return skill_fight(attacker, defender);
  case GOBLIN_PUNCH:
    return skill_goblin_punch(attacker, defender);
  case RUNE_SWORD_SKILL:
    return skill_rune_sword(attacker, defender);
  default:
    return ATTACK_MISSED;
  }
}

void handle_targeted_attack(BATTLE_SKILL skill, BYTE target_enemy) BANKED {
  if (!current_turn->is_enemy) {
    LOG("+> is hero");
    if (target_enemy < 0) {
      target_enemy = rpg_get_target_enemy();
    }
    current_enemy = &enemy_slots[target_enemy];
    const ATTACK_RESULTS attack_results=do_targetted_attack(current_turn->entity, &current_enemy->ext, skill);


    setup_explosions(&current_enemy->ext.pos);
    dispatch_action(ANIMATE_PlayerAttacking);
    dispatch_action(ANIMATE_EnemyDamaged);

    if (attack_results & CRITICAL_HIT) {
      // animate critical hit
    } else if (attack_results & ATTACK_HIT) {
      // animate hit
    } else if (attack_results & CRITICAL_MISS) {
      // animate critical miss
    } else if (attack_results & ATTACK_MISSED) {
      // animate miss
    }

    if (attack_results & TARGET_DEFEATED) {
      // animate target defeateated
    }

    if(skill == RUNE_SWORD_SKILL){
      return handle_targeted_attack(FIGHT, target_enemy);
    }

    if (attack_results & TARGET_DEFEATED) {
      dispatch_action(ANIMATE_EnemyDefeated);
    }
  } else {
    LOG("+> is enemy");
    UBYTE target_enemy = drand(0, 4);
    entity_data * target = &hero_slots[target_enemy].ext;
    while (target->status & DEAD) {
      target_enemy = drand(0, 4);
      target = &hero_slots[target_enemy].ext;
    }
    const ATTACK_RESULTS attack_results=do_targetted_attack(current_turn->entity, target, skill);

    dispatch_action(PANEL_UpdateParty);

    if (attack_results & CRITICAL_HIT) {
      // animate critical hit
    } else if (attack_results & ATTACK_HIT) {
      // animate hit
    } else if (attack_results & CRITICAL_MISS) {
      // animate critical miss
    } else if (attack_results & ATTACK_MISSED) {
      // animate miss
    }

    if (attack_results & TARGET_DEFEATED) {
      // animate target defeateated
    }

    setup_explosions(&target->pos);
    dispatch_action(ANIMATE_EnemyAttacking);
    dispatch_action(ANIMATE_EnemyDamaged);
  }
}

void handle_skill(BATTLE_SKILL skill) BANKED {
  switch (skill) {
  case FIGHT:
  case GOBLIN_PUNCH:
  case RUNE_SWORD_SKILL:
    handle_targeted_attack(skill, -1);
    break;
  case SHIELD_SKILL:
  case LUSTER:
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