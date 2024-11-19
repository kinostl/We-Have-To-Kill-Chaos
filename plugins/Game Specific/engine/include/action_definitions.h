#ifndef FF_ACTION_DEFINITIONS
#define FF_ACTION_DEFINITIONS
#include "entity_data.h"
#include "enums.h"
#include <gbs_types.h>
#include <vm.h>

void turn_rollInitiative(void) BANKED;
ATTACK_RESULTS defender_TakeDamage(entity_data *attacker, entity_data *defender) BANKED;

extern actor_t * damage_numbers[3];

#endif