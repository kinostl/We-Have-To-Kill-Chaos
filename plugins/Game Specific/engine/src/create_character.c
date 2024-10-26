#include <asm/types.h>
#include <data/game_globals.h>
#include <gb/gb.h>
#include "extra_data.h"
#include "hero_data.h"
#include "vm.h"
#pragma bank 255

void cc_add_letter_to_name(SCRIPT_CTX * THIS) OLDCALL BANKED {
    const char alpha[6][8]={
        {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H'},
        {'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P'},
        {'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X'},
        {'Y', 'Z', ' ', '0', '1', '2', '3', '4'},
        {'?', '\'', ',', '5', '6', '7', '8', '9'},
        {'.', '-', '.', '!', '.', '.', '.', '\0'},
    };

    hero_data * hero = &hero_slots[VM_GLOBAL(VAR_CC_CURRENT_C)];
    hero -> name[VM_GLOBAL(VAR_CC_CURRENT_LETTER)] = alpha[VM_GLOBAL(VAR_TEMP_Y)][VM_GLOBAL(VAR_TEMP_X)];
}

void cc_set_job(SCRIPT_CTX * THIS) OLDCALL BANKED {
    hero_data * hero = &hero_slots[VM_GLOBAL(VAR_CC_CURRENT_C)];
    hero -> job = VM_GLOBAL(VAR_CC_CLASS_CHOICE);
}