#include "action_handler.h"
#include "entity_data.h"
#include "enums.h"
#include "extra_data.h"
#include "ff_util.h"
#include "hero_data.h"
#include "turn_slots.h"
#include "weapon_data.h"
#include <actor.h>
#include <asm/types.h>
#include <data/game_globals.h>
#include <math.h>
#include <string.h>
#pragma bank 255
#include "action_definitions.h"
#include "skill_definitions.h"

#define BASE_PLAYER_EVADE 48
#define TURN_ORDER_COUNT 10

actor_t * damage_numbers[3];

UBYTE do_initiative_roll(turn_slot_t * turn_slot) BANKED {
  if (turn_slot->entity == NULL)
    return 0;

  entity_data *entity = turn_slot->entity;

  if (entity->status & DEAD)
    return 0;

  UBYTE initiative_roll = drand(1, entity->max_hp);
  initiative_roll += entity->evade;
  if (!turn_slot->is_enemy)
    initiative_roll += BASE_PLAYER_EVADE;
  return initiative_roll;
}

turn_slot_t* sortedInsert(turn_slot_t* createTurnSlot, 
                          turn_slot_t* sorted) BANKED {
    
    // Special case for the head end
    if (sorted == NULL || 
        sorted->initiative_roll < createTurnSlot->initiative_roll) {
        createTurnSlot->next = sorted;
        sorted = createTurnSlot;
    }
    else {
        turn_slot_t* curr = sorted;
        
        // Locate the node before the point of insertion
        while (curr->next != NULL && 
               curr->next->initiative_roll > createTurnSlot->initiative_roll) {
            curr = curr->next;
        }
        createTurnSlot->next = curr->next;
        curr->next = createTurnSlot;
    }
    
    return sorted;
}

turn_slot_t* insertionSort(turn_slot_t* head) BANKED {
    
    // Initialize sorted linked list
    turn_slot_t* sorted = NULL;
    turn_slot_t* curr = head;
    
    // Traverse the given linked list and insert
    // every node to sorted
    while (curr != NULL) {
        
        // Store next for next iteration
        turn_slot_t* next = curr->next;
        
        // Insert current in sorted linked list
        sorted = sortedInsert(curr, sorted);
        
        // Update current
        curr = next;
    }
    
    return sorted;
}

struct turn_slot_t *doubleLink(turn_slot_t *start) BANKED {
  turn_slot_t *prev = start;
  turn_slot_t *head = start->next;

  while (head != NULL) {
    head->prev = prev;
    head = head->next;
    prev = prev->next;
  }

  return start;
}

void turn_rollInitiative(void) BANKED {
  turn_slot_t *tail_slot;
  turn_slot_t *head_slot;
  
  for (UBYTE i = 0; i < 10; i++) {
    turn_slots[i].next = NULL;
    turn_slots[i].prev = NULL;
    turn_slots[i].initiative_roll = NULL;
    turn_slots[i].is_enemy = i > 3;
    turn_slots[i].initiative_roll = 0;
    if (turn_slots[i].entity == NULL)
      continue;

    turn_slots[i].initiative_roll = do_initiative_roll(&turn_slots[i]);

    if (turn_slots[i].initiative_roll < 1)
      continue;

    if(tail_slot == NULL){
      tail_slot = &turn_slots[i];
      head_slot = tail_slot;
      continue;
    }
    
    tail_slot->next = &turn_slots[i];
    tail_slot = &turn_slots[i];

  }

  head_slot = insertionSort(head_slot);
  head_slot = doubleLink(head_slot);

  current_turn = head_slot;
}

void attacker_prepareNextTurn_Hero(void) BANKED {
  hero_data *player = &hero_slots[VM_GLOBAL(VAR_ATTACKER_ID)];
  weapon_data *weapon = &player->weapon;
  player->ap++;
}

void attacker_prepareNextTurn_Enemy(void) BANKED {}

void defender_RollToHit(entity_data *attacker, entity_data *defender) BANKED {
  const UBYTE hit_roll = drand(0, 200);
  const UBYTE base_hit_chance = 168;
  const UWORD hit_chance =
      (base_hit_chance + attacker->hit_chance) - defender->evade;

  damage_queue_tail->skill_type = FIGHT_ATTACK;
  damage_queue_tail->attack_results = ATTACK_MISSED;

  if (hit_roll == 200) {
    damage_queue_tail->attack_results |= CRITICAL_MISS;
    return;
  }

  if (hit_chance < hit_roll)
    return;

  damage_queue_tail->attack_results = ATTACK_HIT;

  if (attacker->crit_chance > hit_roll) {
    damage_queue_tail->attack_results |= CRITICAL_HIT;
  }
}

void defender_RollForDamage( entity_data *defender, UBYTE damage_calc) BANKED {
  if(damage_queue_tail->attack_results & ATTACK_MISSED){
    damage_queue_tail->damage = 0;
    return;
  }

  damage_queue_tail->damage = damage_calc;
  damage_queue_tail->damage = MAX(damage_calc - defender->absorb, 1);

  if (defender->status & DEFENDING) {
    damage_queue_tail->damage =
        MAX(damage_queue_tail->damage - defender->absorb, 1);
  }

  if (damage_queue_tail->attack_results & CRITICAL_HIT) {
    damage_queue_tail->damage += damage_calc;
  }
}

void defender_TakeDamage(entity_data *defender) BANKED {
  defender->hp = MAX(defender->hp - damage_queue_tail->damage, 0);

  if (defender->hp < 1) {
    defender->status |= DEAD;
    damage_queue_tail->attack_results |= TARGET_DEFEATED;
  }

}

void defender_ReceiveAttack(entity_data *attacker, entity_data *defender,
                            UBYTE damage_calc) BANKED {
  defender_RollToHit(attacker, defender);
  defender_RollForDamage(defender, damage_calc);
  defender_TakeDamage(defender);
}

void defender_TakeMagicDamage(entity_data *attacker, entity_data *defender,
                              UBYTE damage_calc, UBYTE spell_acc) BANKED {
  const UBYTE hit_roll = drand(0, 200);
  const UBYTE base_hit_chance = 148;
  const UBYTE hit_chance = base_hit_chance + spell_acc - defender->mdef;

  damage_queue_tail->damage = damage_calc;
  damage_queue_tail->attack_results = MAGIC_HIT;
  damage_queue_tail->skill_type = MAGIC_ATTACK;

  if (hit_roll < hit_chance) {
    damage_queue_tail->damage += damage_calc;
  } else {
    damage_queue_tail->attack_results |= MAGIC_RESISTED;
  }

  defender->hp = MAX(defender->hp - damage_queue_tail->damage, 0);

  if(defender->hp < 1){
    defender->status |= DEAD;
    damage_queue_tail->attack_results |= TARGET_DEFEATED;
  }
}