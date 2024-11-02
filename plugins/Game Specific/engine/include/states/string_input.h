#ifndef STATE_STRING_INPUT
#define STATE_STRING_INPUT
#include <asm/types.h>
#include <data/rpg_combat_animation_states.h>
#include <math.h>

extern const char string_input_alphabet[6][8];

extern point16_t string_input_curr_pos;

inline char string_input_char(void){
    return string_input_alphabet[string_input_curr_pos.y][string_input_curr_pos.x];
}

#endif