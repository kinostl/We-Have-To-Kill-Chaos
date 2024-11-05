#include "extra_data.h"
#include "hero_data.h"
#include "states/string_input.h"
#include "vm.h"
#include <asm/types.h>
#include <data/game_globals.h>
#include <gb/gb.h>
#include <input.h>
#include <string.h>
#pragma bank 255

#define CC_NAME_X 7
#define CC_NAME_Y 3

#define CC_ALPH_X 2
#define CC_ALPH_Y 6

void cc_clear_name(SCRIPT_CTX *THIS) OLDCALL BANKED {
  hero_data *hero = &hero_slots[VM_GLOBAL(VAR_CC_CURRENT_C)];
  strcpy(hero->name, "");
}

void cc_add_letter_to_name(SCRIPT_CTX *THIS) OLDCALL BANKED {
  hero_data *hero = &hero_slots[VM_GLOBAL(VAR_CC_CURRENT_C)];
  hero->name[VM_GLOBAL(VAR_CC_CURRENT_LETTER)] = string_input_char();

  uint8_t letterTile =
      get_bkg_tile_xy(CC_ALPH_X + (string_input_curr_pos.x * 2),
                      CC_ALPH_Y + (string_input_curr_pos.y * 2));

  set_bkg_tile_xy(CC_NAME_X + VM_GLOBAL(VAR_CC_CURRENT_LETTER), CC_NAME_Y,
                  letterTile);
  VM_GLOBAL(VAR_CC_CURRENT_LETTER)++;
}

void cc_backspace(SCRIPT_CTX * THIS) OLDCALL BANKED {
  hero_data *hero = &hero_slots[VM_GLOBAL(VAR_CC_CURRENT_C)];
  VM_GLOBAL(VAR_CC_CURRENT_LETTER)--;

  hero->name[VM_GLOBAL(VAR_CC_CURRENT_LETTER)] = '\0';
  set_bkg_tile_xy(CC_NAME_X + VM_GLOBAL(VAR_CC_CURRENT_LETTER), CC_NAME_Y, 0);

}

void cc_set_job(SCRIPT_CTX *THIS) OLDCALL BANKED {
  hero_data *hero = &hero_slots[VM_GLOBAL(VAR_CC_CURRENT_C)];
  hero->job = VM_GLOBAL(VAR_CC_CLASS_CHOICE);
}

void cc_end_input(SCRIPT_CTX *THIS) OLDCALL BANKED {
  string_input_curr_pos.y = 5;
  string_input_curr_pos.x = 7;
}

void cc_display_class(SCRIPT_CTX *THIS) OLDCALL BANKED {
  UWORD * class = (UWORD *)VM_REF_TO_PTR(FN_ARG0);
  *class = hero_slots[*class].job;
}

void cc_display_names(SCRIPT_CTX *THIS) OLDCALL BANKED {
}