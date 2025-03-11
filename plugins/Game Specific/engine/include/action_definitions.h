#ifndef FF_ACTION_DEFINITIONS
#define FF_ACTION_DEFINITIONS
#include "entity_data.h"
#include "enums.h"
#include <actor.h>
#include <gbs_types.h>
#include <vm.h>
#include "position.h"

void turn_rollInitiative(void) BANKED;
void defender_ReceiveAttack(entity_data *attacker, entity_data *defender, UBYTE damage_calc) BANKED;
void defender_ReceiveMagicAttack(entity_data *attacker, entity_data *defender, UBYTE damage_calc, UBYTE spell_accuracy) BANKED;

void defender_RollToHit(entity_data *attacker, entity_data *defender) BANKED;
void defender_RollForDamage( entity_data *defender, UBYTE damage_calc) BANKED;
void defender_TakeDamage(entity_data *defender) BANKED;

extern actor_t * damage_numbers[3];

inline void setup_damage_numbers(UBYTE dmg, ff_position_t *target) {
  // 0 = Ones
  // 1 = Tens
  // 2 = Hundreds
  if(dmg < 1){
    actor_set_frame_offset(damage_numbers[0], 11);
    actor_set_frame_offset(damage_numbers[1], 10);
    actor_set_frame_offset(damage_numbers[2], 10);
    damage_numbers[0]->pos.x = pos(((target->x) + (target->w / 2)) - 1);
    damage_numbers[0]->pos.y = pos((target->y) + (target->h / 2));
    return;
  }

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

#endif