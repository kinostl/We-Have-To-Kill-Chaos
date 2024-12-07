#include "action_definitions.h"
#include "extra_data.h"
#include "ff_debug.h"
#include "ff_util.h"
#include "states/rpg_combat.h"
#include <asm/types.h>
#include "skill_definitions.h"
#include "animations.h"

#pragma bank 255

void skill_fight() BANKED {
  if (!current_turn->is_enemy) {
    LOG("+> is hero");
    const UBYTE target_enemy = rpg_get_target_enemy();
    current_enemy = &enemy_slots[target_enemy];
    ATTACK_RESULTS attack_results =
        defender_TakeDamage(current_turn->entity, &current_enemy->ext);

    setup_explosions(&enemy_slots[target_enemy].ext.pos);

    animate(ANIMATE_PLAYER_ATTACKING);
    animate(ANIMATE_ENEMY_DAMAGED);
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
      dispatch_action(ANIMATE_EnemyDefeated);
      // animate target defeateated
    }
  } else {
    LOG("+> is enemy");
    const UBYTE target_enemy = drand(0, 4);
    ATTACK_RESULTS attack_results = defender_TakeDamage(
        current_turn->entity, &hero_slots[target_enemy].ext);

    setup_explosions(&hero_slots[target_enemy].ext.pos);

    animate(ANIMATE_ENEMY_ATTACKING);
    animate(ANIMATE_ENEMY_DAMAGED);

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
  }
}

void handle_skill(BATTLE_SKILL skill) BANKED {
  switch (skill) {
  case FIGHT:
    skill_fight();
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
    return;
  }

  dispatch_action(ATTACKER_FinishTurn);
}