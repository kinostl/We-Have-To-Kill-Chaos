#ifndef FF_ACTION_DEFINITIONS
#define FF_ACTION_DEFINITIONS
#include "entity_data.h"
#include "enums.h"
#include <gbs_types.h>
#include <vm.h>

void turn_rollInitiative(void) BANKED;
ATTACK_RESULTS defender_TakeDamage(entity_data *attacker, entity_data *defender, UBYTE damage_calc) BANKED;
ATTACK_RESULTS defender_TakeMagicDamage(entity_data *attacker, entity_data *defender, UBYTE damage_calc, UBYTE spell_accuracy) BANKED;

extern actor_t * damage_numbers[3];

#endif