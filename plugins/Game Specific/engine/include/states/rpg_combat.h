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

UBYTE rpg_run_menu(void) BANKED;

#endif