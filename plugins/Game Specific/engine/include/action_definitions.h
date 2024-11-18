#ifndef FF_ACTION_DEFINITIONS
#define FF_ACTION_DEFINITIONS
#include <vm.h>
void turn_rollInitiative(void) BANKED;
ATTACK_RESULTS defender_TakeDamage(entity_data *attacker, entity_data *defender) BANKED;
#endif