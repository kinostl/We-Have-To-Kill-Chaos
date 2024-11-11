#include "action_handler.h"
#include "entity_data.h"
#include "enums.h"
#include "extra_data.h"
#include "hero_data.h"
#include "weapon_data.h"
#include <asm/types.h>
#include <data/game_globals.h>
#include <math.h>
#pragma bank 255
#include "rand.h" // IWYU pragma: keep
#include "action_definitions.h"

#define BASE_PLAYER_EVADE 48
#define TURN_ORDER_COUNT 10

void turn_rollInitiative(void) BANKED{
    for (int i = 0; i < 10; i++) {
      turn_order[i] = -1;
    }

    for (int i = 0; i < 10; i++) {
      entity_data * entity = turn_slots[i];
      if (!entity->alive)
        continue;
      BYTE *initiative_slot = &turn_order[i];
      *initiative_slot = rand() % entity->max_hp;
      *initiative_slot += entity->evade;
      if (i < 4) {
        *initiative_slot += BASE_PLAYER_EVADE;
      }
    }
}

#define initiative_rolls turn_order
BYTE turn_sortInitiative(void) BANKED{
    BYTE initiative_order[TURN_ORDER_COUNT];
    BYTE end_of_arr=0;
    int16_t max_val=-1;
    int16_t max_i=0;

    for(BYTE i = 0; i<TURN_ORDER_COUNT;i++){
        initiative_order[i] = -1;
    }

    for(BYTE i = 0; i<TURN_ORDER_COUNT;i++){
        if(initiative_rolls[i] < 0){
            continue;
        }
        max_val = initiative_rolls[i];
        max_i=i;

        for (BYTE j = i; j < TURN_ORDER_COUNT; j++) {
          if (initiative_rolls[j] > max_val) {
            max_val = initiative_rolls[j];
          }
        }
        if (max_val > -1) {
          initiative_order[end_of_arr] = max_i;
          end_of_arr++;
        }
    }

    for(BYTE i = 0; i<TURN_ORDER_COUNT;i++){
        turn_order[i] = initiative_order[i];
    }

    return end_of_arr;
}
#undef initiative_rolls

void attacker_prepareNextTurn_Hero(void) BANKED {
    hero_data *player = &hero_slots[VM_GLOBAL(VAR_ATTACKER_ID)];
    weapon_data *weapon = &player->weapon;
    player->ap++;
}

void attacker_prepareNextTurn_Enemy(void) BANKED{}

ATTACK_RESULTS defender_TakeDamage(entity_data *attacker,
                                   entity_data *defender) BANKED {
  const UWORD hit_roll = rand() % 201;
  const UWORD target_number = (168 + attacker->hit_chance) - defender->evade;

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
    defender->alive = FALSE;
    results |= TARGET_DEFEATED;
  }

  return results;
}