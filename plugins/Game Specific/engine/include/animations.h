#ifndef FF_ANIMS
#define FF_ANIMS
#include "position_data.h"
#include "states/rpg_combat.h"
#include <data/game_globals.h>
#include <data/rpg_combat_animation_states.h>
#include <vm.h>

inline void setup_explosions(ff_position_t *position) {
  VM_GLOBAL(VAR_EXPLOSION_X) = position->x;
  VM_GLOBAL(VAR_EXPLOSION_Y) = position->y + 1;
  VM_GLOBAL(VAR_EXPLOSION_W) = position->w - 1;
  VM_GLOBAL(VAR_EXPLOSION_H) = position->h - 1;
}

inline void animate(RPG_ANIMATION_STATE rpg_animation_state) {
  if (state_events[rpg_animation_state].script_addr != 0) {
    script_execute(state_events[rpg_animation_state].script_bank,
                   state_events[rpg_animation_state].script_addr, 0, 0);
  }
}
#endif