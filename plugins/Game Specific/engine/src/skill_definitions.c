#include "skill_definitions.h"
#include "action_definitions.h"
#include "action_handler.h"
#include "animations.h"
#include "entity_data.h"
#include "enums.h"
#include "extra_data.h"
#include "ff_debug.h"
#include "ff_text.h"
#include "ff_util.h"
#include "hero_data.h"
#include "position_data.h"
#include "skill_data.h"
#include "states/rpg_combat.h"
#include "turn_slots.h"
#include <asm/types.h>
#include <data/explosion_palettes.h>
#include <data/rpg_combat_animation_states.h>
#include <math.h>
#include <string.h>
#include <types.h>
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
*/
void skill_goblin_punch(entity_data *attacker, entity_data *defender) BANKED {
  WORD distance = DISTANCE(attacker->max_hp, defender->max_hp);
  WORD modifier = 8 - CLAMP(distance, 0, 7);

  const UBYTE atk_dmg = attacker->damage;
  UBYTE damage_calc = MAX(drand(atk_dmg, atk_dmg * 2), 1);
  damage_calc -= DIV_4(atk_dmg);
  damage_calc *= modifier;

  defender_ReceiveAttack(attacker, defender, damage_calc);
}

void skill_fight(entity_data *attacker, entity_data *defender) BANKED {
  const UBYTE atk_dmg = attacker->damage;
  const UBYTE damage_calc = MAX(drand(atk_dmg, atk_dmg * 2), 1);
  defender_ReceiveAttack(attacker, defender, damage_calc);
}

void skill_wreck(entity_data *attacker, entity_data *defender) BANKED {
  const UBYTE atk_dmg = attacker->damage;
  const UBYTE damage_calc = MAX(atk_dmg * 2, 1);
  defender_ReceiveAttack(attacker, defender, damage_calc);
  attacker->status |= WEAKENED;
}

void skill_rune_sword(entity_data *attacker,
                                entity_data *defender) BANKED {
  const UBYTE atk_dmg = attacker->damage;
  const UBYTE damage_calc = MAX(drand(atk_dmg, atk_dmg * 2), 1);
  defender_TakeMagicDamage(attacker, defender, damage_calc, attacker->hit_chance);
}

void skill_cover(entity_data *user, entity_data *target) BANKED {
  target->status |= DEFENDING;
}

void skill_weak(entity_data *user, entity_data *target) BANKED {
  target->status |= WEAKENED;
}

/*
Effect: Attack with Fight 8 times, but no base hit rate
*/
void skill_thrash(entity_data *attacker, entity_data *defender) BANKED {
  const UBYTE atk_dmg = attacker->damage;
  const UBYTE BACKUP_EVADE = defender->evade;
  defender->evade = 168; //Offset base hit rate

  ATTACK attack_total;
  memcpy(&attack_total, damage_queue_tail, sizeof(ATTACK));

  attack_total.number_of_hits = 0;
  attack_total.damage = 0;

  for (UBYTE i = 0; i < 8; i++) {
    memcpy(damage_queue_tail, 0, sizeof(ATTACK));

    const UBYTE damage_calc = MAX(drand(atk_dmg, atk_dmg * 2), 1);
    defender_RollToHit(attacker, defender);
    defender_RollForDamage(defender, damage_calc);

    if (damage_queue_tail->attack_results & CRITICAL_HIT) {
      attack_total.attack_results |= CRITICAL_HIT;
    }

    if (damage_queue_tail->attack_results & ATTACK_HIT) {
      attack_total.attack_results = ATTACK_HIT;
      attack_total.number_of_hits++;
      attack_total.damage += damage_queue_tail->damage;
    }
  }

  memcpy(damage_queue_tail, &attack_total, sizeof(ATTACK));
  defender_TakeDamage(defender);

  defender->evade = BACKUP_EVADE;
}
void skill_blade_blitz(entity_data *user, BOOLEAN is_enemy) BANKED {
  UBYTE target_idx[6];
  UBYTE list_i=0;
  for(turn_slot_t * current_target = &turn_slots[0]; current_target->next; current_target=current_target->next){
    if(current_target->is_enemy == is_enemy) continue;
    if(current_target->entity->status & DEAD) continue;
    target_idx[list_i] = current_target->entity->idx;
    list_i++;
  }

  list_i++;

  for (UBYTE attack_count = 0; attack_count < 6; attack_count++) {
    entity_data *entity;
    if(is_enemy){
      entity = &hero_slots[attack_count % list_i].ext;
    }else{
      entity = &enemy_slots[attack_count % list_i].ext;
    };

    damage_queue_tail->color = EXPLOSION_DEFAULT;
    const UBYTE BACKUP_EVADE = entity->evade;
    entity->evade=0;

    skill_fight(user, entity);
    entity->evade = BACKUP_EVADE;

    damage_queue_tail->target = entity;
    damage_queue_tail++;
  }
}

void skill_pierce(entity_data *user, BOOLEAN is_enemy) BANKED {
  const UBYTE atk_dmg = user->damage;
  const UBYTE damage_calc = MAX(drand(atk_dmg, atk_dmg * 2), 1);

  UBYTE target_idx[6];
  UBYTE list_i=0;
  for(turn_slot_t * current_target = &turn_slots[0]; current_target->next; current_target=current_target->next){
    if(current_target->is_enemy == is_enemy) continue;
    if(current_target->entity->status & DEAD) continue;
    target_idx[list_i] = current_target->entity->idx;
    list_i++;
  }

  list_i++;

  for (UBYTE attack_count = 0; attack_count < 6; attack_count++) {
    entity_data *entity;
    if(is_enemy){
      entity = &hero_slots[attack_count % list_i].ext;
    }else{
      entity = &enemy_slots[attack_count % list_i].ext;
    };

    damage_queue_tail->color = EXPLOSION_DEFAULT;

    defender_RollToHit(user, entity);
    damage_queue_tail->attack_results |= CRITICAL_HIT;

    defender_RollForDamage(user, damage_calc);
    defender_TakeDamage(entity);


    damage_queue_tail->target = entity;
    damage_queue_tail++;
  }
}

void skill_sneak(entity_data *attacker, entity_data *defender) BANKED {
  const UBYTE backup_evade = defender->evade;
  const UBYTE backup_absorb = defender->absorb;
  defender->evade = 0;
  defender->absorb = 0;
  skill_fight(attacker, defender);
  defender->evade = backup_evade;
  defender->absorb = backup_absorb;
}

void skill_stun(entity_data *attacker, entity_data *defender) BANKED {
  defender->status |= PARALYZED;
}

void do_targetted_attack(entity_data *attacker, entity_data *defender,
                                   BATTLE_SKILL skill) BANKED {
  damage_queue_tail->target = defender;
  damage_queue_tail->number_of_hits = 1;
  damage_queue_tail->color = EXPLOSION_DEFAULT;

  switch (skill) {
  case FIGHT:
    skill_fight(attacker, defender);
    break;
  case GOBLIN_PUNCH:
    skill_goblin_punch(attacker, defender);
    break;
  case THRASH:
    skill_thrash(attacker, defender);
    break;
  case LUSTER:
    damage_queue_tail->color = EXPLOSION_WHITE;
    skill_rune_sword(attacker, defender);
    damage_queue_tail++;
    damage_queue_tail->target = defender;
    damage_queue_tail->color = EXPLOSION_DEFAULT;
    skill_fight(attacker, defender);
    break;
  case SNEAK:
    skill_sneak(attacker, defender);
    break;
  case WEAK:
    damage_queue_tail->attack_results = SKILL_HIT;
    skill_weak(attacker, defender);
    break;
  case STUN:
    damage_queue_tail->attack_results = SKILL_HIT;
    skill_stun(attacker, defender);
    break;
  case WRECK:
    skill_wreck(attacker, defender);
    break;
  default:
    return;
  }

  damage_queue_tail++;
}

void do_targetted_support(entity_data *user, entity_data *target,
                          BATTLE_SKILL skill) BANKED {
  switch (skill) {
  case COVER:
    skill_cover(user, target);
    break;
  default:
    break;
  }
}

void do_group_attack(entity_data *user, BOOLEAN is_enemy,
                     BATTLE_SKILL skill) BANKED {

  switch (skill) {
  case BLADE_BLITZ:
    skill_blade_blitz(user, is_enemy);
    break;
  case PIERCE:
    skill_pierce(user, is_enemy);
    break;
  default:
    break;
  }
}

void do_personal_support(entity_data *user, BATTLE_SKILL skill) BANKED {
  switch (skill) {
  case GUARD:
    user->status |= DEFENDING;
    break;
  default:
    // case FOCUS:
    break;
  }
}

void handle_targeted_attack(BATTLE_SKILL skill) BANKED {
  if (!current_turn->is_enemy) {
    LOG("+> is hero");
    const UBYTE target_enemy = rpg_get_target_enemy();
    current_enemy = &enemy_slots[target_enemy];
    do_targetted_attack(current_turn->entity, &current_enemy->ext, skill);

    dispatch_action(ANIMATE_PlayerAttacking);
  } else {
    LOG("+> is enemy");
    UBYTE target_enemy = drand(0, 4);
    entity_data * target = &hero_slots[target_enemy].ext;
    while (target->status & DEAD) {
      target_enemy = drand(0, 4);
      target = &hero_slots[target_enemy].ext;
    }
    do_targetted_attack(current_turn->entity, target, skill);
    dispatch_action(ANIMATE_EnemyAttacking);

    if (skill != FIGHT) {
      dispatch_action(MODAL_Open);
      dispatch_action(MODAL_Hold);
      dispatch_action(MODAL_Close);
    }

  }
}

void handle_targeted_support(BATTLE_SKILL skill) BANKED {
  const UBYTE target_ally = rpg_get_target_ally(FALSE);
  do_targetted_support(current_turn->entity, &hero_slots[target_ally].ext, skill);
  dispatch_action(PANEL_UpdateParty);
}

void handle_group_attack(BATTLE_SKILL skill) BANKED {
  do_group_attack(current_turn->entity, current_turn->is_enemy, skill);
  dispatch_action(ANIMATE_PlayerAttacking);
}

void handle_personal_support(BATTLE_SKILL skill) BANKED {
  do_personal_support(&current_hero->ext, skill);
  dispatch_action(ANIMATE_PlayerCasting);
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

void spend_ap_for_skill(BATTLE_SKILL skill_id, hero_data * hero) BANKED {
  skill_data skill;
  load_skill(&skill, skill_id);
  hero->ap = CLAMP(hero->ap - skill.cost, 0, 4);
}

BOOLEAN handle_skill(BATTLE_SKILL skill) BANKED {
  switch (skill) {
  case FIGHT:
  case GOBLIN_PUNCH:
  case LUSTER:
  case THRASH:
  case SNEAK:
  case WEAK:
  case STUN:
  case WRECK:
    handle_targeted_attack(skill);
    break;
  case COVER:
    handle_targeted_support(skill);
    break;
  case BLADE_BLITZ:
  case PIERCE:
    handle_group_attack(skill);
    break;
  case FOCUS:
  case GUARD:
    handle_personal_support(skill);
    break;
  case FIRE:
  case ICE:
  case HARM:
  case HEAL:
  case HOWL:
  case BLANK:
    dispatch_action(PICK_GetPlayerActionChoice);
    return FALSE;
  }

  dispatch_action(ATTACKER_FinishTurn);
  return TRUE;
}

void display_skill(BATTLE_SKILL skill) BANKED{
  skill_data s_data;
  load_skill(&s_data, skill);
  load_battle_message(s_data.name);
}