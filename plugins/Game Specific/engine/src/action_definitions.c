#include "action_handler.h"
#include "entity_data.h"
#include "enums.h"
#include "extra_data.h"
#include "ff_util.h"
#include "hero_data.h"
#include "position_data.h"
#include "turn_slots.h"
#include "weapon_data.h"
#include <actor.h>
#include <asm/types.h>
#include <data/game_globals.h>
#include <math.h>
#include <string.h>
#pragma bank 255
#include "action_definitions.h"
#include "position.h"

#define BASE_PLAYER_EVADE 48
#define TURN_ORDER_COUNT 10

actor_t *damage_numbers[3];

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
                          turn_slot_t* sorted) {
    
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

turn_slot_t* insertionSort(turn_slot_t* head) {
    
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

struct turn_slot_t *doubleLink(turn_slot_t *start) {
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

void setupDamageNumbers(UBYTE dmg, ff_position_t *target) {
  // 0 = Ones
  // 1 = Tens
  // 2 = Hundreds

  UBYTE max_i = 3;
  if (dmg < 100){
    actor_set_frame_offset(damage_numbers[2], 10);
    max_i--;
  }

  if (dmg < 10){
    actor_set_frame_offset(damage_numbers[1], 10);
    max_i--;
  }

  for (UBYTE i = 0; i < max_i; i++) {
    UBYTE digit = dmg % 10;
    actor_set_frame_offset(damage_numbers[i], digit);
    damage_numbers[i]->pos.x = pos(((target->x - i) + (target->w / 2)) - 1);
    damage_numbers[i]->pos.y = pos((target->y) + (target->h / 2));
    dmg /= 10;
  }
}

ATTACK_RESULTS defender_TakeDamage(entity_data *attacker,
                                   entity_data *defender) BANKED {
  setupDamageNumbers(0, &defender->pos);

  const UBYTE hit_roll = drand(0, 200);
  if (hit_roll == 200)
    return ATTACK_MISSED | CRITICAL_MISS;

  const UBYTE base_hit_chance = 168;
  const UWORD target_number =
      (base_hit_chance + attacker->hit_chance) - defender->evade;

  if (target_number < hit_roll)
    return ATTACK_MISSED;

  ATTACK_RESULTS results = ATTACK_HIT;
  UBYTE total_damage=0;
  const UBYTE atk_dmg = attacker->damage;
  UBYTE damage_calc = MAX(drand(atk_dmg, atk_dmg * 2), 1);

  if (attacker->crit_chance > hit_roll) {
    defender->hp -= damage_calc;
    results |= CRITICAL_HIT;
    total_damage += damage_calc;
  }

  damage_calc = MAX(damage_calc - defender->absorb, 1);
  total_damage += damage_calc;
  if ((defender->hp - damage_calc) < 1) {
    defender->hp = 0;
    defender->status |= DEAD;
    results |= TARGET_DEFEATED;
  } else {
    defender->hp -= damage_calc;
  }

  setupDamageNumbers(total_damage, &defender->pos);

  return results;
}