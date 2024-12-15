#ifndef STATE_RPG_COMBAT
#define STATE_RPG_COMBAT
#include <asm/types.h>
#include <data/rpg_combat_animation_states.h>

typedef struct script_state_t {
    UBYTE script_bank;
    UBYTE *script_addr;
} script_state_t;

extern RPG_ANIMATION_STATE rpg_animation_state;
extern script_state_t state_events[RPG_ANIMATION_STATE_LENGTH];
extern BYTE rpg_lock;

UBYTE rpg_run_menu(void) BANKED;
UBYTE rpg_get_target_ally(BOOLEAN targets_dead) BANKED;
UBYTE rpg_get_target_enemy(void) BANKED;

#endif