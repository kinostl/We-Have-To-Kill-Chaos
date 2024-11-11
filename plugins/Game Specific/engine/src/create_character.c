#include "extra_data.h"
#include "hero_data.h"
#include "load_font_into_bg.h"
#include "states/string_input.h"
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

UBYTE load_centered_text(char name[7]) BANKED {
  strcpy(ui_text_data, name);

  switch (strlen(ui_text_data)) {
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


void cc_init_set_name(void) OLDCALL BANKED{
  loadFontIntoBkg();
  const UBYTE c = VM_GLOBAL(VAR_CC_CURRENT_C);
  strcpy(ui_text_data, hero_slots[c].name);
  write_bg_font(7, 3, 6, 1);
  VM_GLOBAL(VAR_CC_CURRENT_LETTER) = strlen(hero_slots[c].name);
}

void cc_check_finished(SCRIPT_CTX * THIS) OLDCALL BANKED{
  UWORD * isFinished = (UWORD *)VM_REF_TO_PTR(FN_ARG0);
  *isFinished = 0;
  for(UBYTE i=0;i<4;i++){
    if(strlen(hero_slots[i].name) > 0){
      *isFinished += 1;
    }
  }
}

void cc_init_confirm_party(void) OLDCALL BANKED{
  UBYTE offset;
  loadFontIntoBkg();

  offset = load_centered_text(hero_slots[0].name);
  write_bg_font(3+offset, 5, 6-offset, 1);

  offset = load_centered_text(hero_slots[1].name);
  write_bg_font(11+offset, 5, 6-offset, 1);

  offset = load_centered_text(hero_slots[2].name);
  write_bg_font(3+offset, 10, 6-offset, 1);

  offset = load_centered_text(hero_slots[3].name);
  write_bg_font(11+offset, 10, 6-offset, 1);
}

void cc_add_letter_to_name(void) OLDCALL BANKED {
  const UBYTE c = VM_GLOBAL(VAR_CC_CURRENT_C);
  hero_slots[c].name[VM_GLOBAL(VAR_CC_CURRENT_LETTER)] = string_input_char();
  VM_GLOBAL(VAR_CC_CURRENT_LETTER)++;
  hero_slots[c].name[VM_GLOBAL(VAR_CC_CURRENT_LETTER)] = '\0';

  strcpy(ui_text_data, hero_slots[c].name);
  write_bg_font(7, 3, 6, 1);
}

void cc_backspace(void) OLDCALL BANKED {
  const UBYTE c = VM_GLOBAL(VAR_CC_CURRENT_C);
  VM_GLOBAL(VAR_CC_CURRENT_LETTER)--;

  hero_slots[c].name[VM_GLOBAL(VAR_CC_CURRENT_LETTER)] = '\0';
  strcpy(ui_text_data, hero_slots[c].name);

  write_bg_font(7, 3, 6, 1);
}

void cc_set_job(void) OLDCALL BANKED {
  hero_slots[VM_GLOBAL(VAR_CC_CURRENT_C)].job = VM_GLOBAL(VAR_CC_CLASS_CHOICE);
}

void cc_end_input(void) OLDCALL BANKED {
  string_input_curr_pos.y = 5;
  string_input_curr_pos.x = 8;
}

void cc_display_class(SCRIPT_CTX *THIS) OLDCALL BANKED {
  UWORD * class = (UWORD *)VM_REF_TO_PTR(FN_ARG0);
  *class = hero_slots[*class].job;
}

void cc_display_names(void) OLDCALL BANKED {
  UBYTE offset;
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