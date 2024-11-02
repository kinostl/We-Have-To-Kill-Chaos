#include <asm/types.h>
#include <data/game_globals.h>
#include <gb/gb.h>
#include "extra_data.h"
#include "hero_data.h"
#include "states/string_input.h"
#include "vm.h"
#pragma bank 255

void cc_add_letter_to_name(SCRIPT_CTX * THIS) OLDCALL BANKED {
    hero_data * hero = &hero_slots[VM_GLOBAL(VAR_CC_CURRENT_C)];
    hero -> name[VM_GLOBAL(VAR_CC_CURRENT_LETTER)] = string_input_char();
}

void cc_set_job(SCRIPT_CTX * THIS) OLDCALL BANKED {
    hero_data * hero = &hero_slots[VM_GLOBAL(VAR_CC_CURRENT_C)];
    hero -> job = VM_GLOBAL(VAR_CC_CLASS_CHOICE);
}