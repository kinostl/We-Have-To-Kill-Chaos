#include "extra_data.h"
#include "hero_data.h"
#include "load_font_into_bg.h"
#include "states/string_input.h"
#include "states/menu.h"
#include "vm.h"
#include <asm/types.h>
#include <data/game_globals.h>
#include <gb/gb.h>
#include <input.h>
#include <string.h>
#include <ui.h>
#pragma bank 255

#define CC_NAME_X 7
#define CC_NAME_Y 3

#define CC_ALPH_X 2
#define CC_ALPH_Y 6


void cc_init_set_name(SCRIPT_CTX * THIS) OLDCALL BANKED{
  loadFontIntoBkg();
  hero_data *hero = &hero_slots[VM_GLOBAL(VAR_CC_CURRENT_C)];
  strcpy(ui_text_data, hero->name);
  write_bg_font(7, 3, 6, 1);
  VM_GLOBAL(VAR_CC_CURRENT_LETTER) = strlen(hero->name);
}

void cc_add_letter_to_name(SCRIPT_CTX *THIS) OLDCALL BANKED {
  hero_data *hero = &hero_slots[VM_GLOBAL(VAR_CC_CURRENT_C)];
  char next_letter = string_input_char();

  hero->name[VM_GLOBAL(VAR_CC_CURRENT_LETTER)] = next_letter;
  VM_GLOBAL(VAR_CC_CURRENT_LETTER)++;

  strcpy(ui_text_data, hero->name);
  write_bg_font(7, 3, 6, 1);
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
  string_input_curr_pos.x = 8;
}

void cc_display_class(SCRIPT_CTX *THIS) OLDCALL BANKED {
  UWORD * class = (UWORD *)VM_REF_TO_PTR(FN_ARG0);
  *class = hero_slots[*class].job;
}

UBYTE load_centered_text(char name[7]) BANKED {
  strcpy(ui_text_data, name);

  switch (strlen(name)) {
  case 6:
  case 5:
  default:
    return 0;
  case 4:
  case 3:
    return 1;
  case 2:
  case 1:
    return 2;
  }
}

void cc_display_names(SCRIPT_CTX *THIS) OLDCALL BANKED {
  UBYTE offset;

  hero_slots[0].job = 4;
  hero_slots[1].job = 3;
  hero_slots[2].job = 2;
  hero_slots[3].job = 1;
  loadFontIntoBkg();

  offset = load_centered_text(hero_slots[0].name);
  write_bg_font(2+offset, 6, 6-offset, 1);

  offset = load_centered_text(hero_slots[1].name);
  write_bg_font(12+offset, 6, 6-offset, 1);

  offset = load_centered_text(hero_slots[2].name);
  write_bg_font(2+offset, 15, 6-offset, 1);

  offset = load_centered_text(hero_slots[3].name);
  write_bg_font(12+offset, 15, 6-offset, 1);
}