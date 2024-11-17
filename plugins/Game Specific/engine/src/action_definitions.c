#include "action_handler.h"
#include "entity_data.h"
#include "enums.h"
#include "extra_data.h"
#include "hero_data.h"
#include "turn_slots.h"
#include "weapon_data.h"
#include <asm/types.h>
#include <data/game_globals.h>
#include <math.h>
#include <string.h>
#pragma bank 255
#include "rand.h" // IWYU pragma: keep
#include "action_definitions.h"
// #include "ff_debug.h"

#define BASE_PLAYER_EVADE 48
#define TURN_ORDER_COUNT 10

UBYTE do_initiative_roll(turn_slot_t turn_slot) BANKED {
  entity_data *entity = turn_slot.entity;
  // if (entity->status & DEAD)
  //   return 0;

  entity->max_hp = 20;
  entity->evade = 5;
  UBYTE initiative_roll = rand() % entity->max_hp;
  initiative_roll += entity->evade;
  if (!turn_slot.is_enemy)
    initiative_roll += BASE_PLAYER_EVADE;
  return initiative_roll + 1;
}

void turn_rollInitiative(void) BANKED {
  for (UBYTE i = 0; i < 10; i++) {
    turn_slots[i].next = NULL;
    turn_slots[i].prev = NULL;
    turn_slots[i].initiative_roll = NULL;
    turn_slots[i].is_enemy = i > 3;
    // turn_slots[i].initiative_roll = do_initiative_roll(turn_slots[i]);
  }
  turn_slots[0].next = &turn_slots[1];
  turn_slots[1].prev = &turn_slots[0];
  turn_slots[1].next = &turn_slots[2];
  turn_slots[2].prev = &turn_slots[1];
  turn_slots[2].next = &turn_slots[3];
  turn_slots[3].prev = &turn_slots[2];
  turn_slots[3].next = &turn_slots[4];
  turn_slots[4].prev = &turn_slots[3];

  current_turn=&turn_slots[0];
}

void attacker_prepareNextTurn_Hero(void) BANKED {
    hero_data *player = &hero_slots[VM_GLOBAL(VAR_ATTACKER_ID)];
    weapon_data *weapon = &player->weapon;
    player->ap++;
}

void attacker_prepareNextTurn_Enemy(void) BANKED{}

ATTACK_RESULTS defender_TakeDamage(entity_data *attacker,
                                   entity_data *defender) BANKED {
  const UBYTE base_hit_chance = 168;
  const UWORD hit_roll = rand() % 201;
  const UWORD target_number = (base_hit_chance + attacker->hit_chance) - defender->evade;

  if (hit_roll == 200)
    return ATTACK_MISSED | CRITICAL_MISS;
  if (target_number < hit_roll)
    return ATTACK_MISSED;

  ATTACK_RESULTS results = ATTACK_HIT;
  const UWORD atk_dmg = attacker->damage;
  UWORD damage_calc = (rand() % atk_dmg) + (atk_dmg + 1);

  if (attacker->crit_chance > hit_roll) {
    defender->hp -= damage_calc;
    results |= CRITICAL_HIT;
  }

  damage_calc = MAX(damage_calc - defender->absorb, 1);
  defender->hp -= damage_calc;

  if (defender->hp <= 0) {
    defender->status |= DEAD;
    results |= TARGET_DEFEATED;
  }

  return results;
}