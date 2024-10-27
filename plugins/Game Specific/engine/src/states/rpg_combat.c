#include "action_handler.h"
#include <asm/sm83/types.h>
#include <asm/types.h>
#include <data/game_globals.h>
#include <game_time.h>
#include <gb/gb.h>
#include <vm.h>
#pragma bank 255

#include "actor.h"
#include "input.h"
#include "load_font_into_bg.h"
#include "math.h"
#include "states/rpg_combat.h"

UWORD rpg_cursor_base_pos;
UWORD rpg_menu_selection;
UWORD rpg_max_menu_selection;

UBYTE rpg_c_timer;
RPG_MENU_MODE rpg_menu_mode;

void rpg_select_menu_item(void) BANKED;
void rpg_select_enemy(void) BANKED;
void rpg_select_ally(void) BANKED;
void rpg_enemy_turn(void) BANKED;

void rpg_combat_init(void) BANKED {
  rpg_menu_selection = 1;
  rpg_max_menu_selection = 18;
  rpg_cursor_base_pos = PLAYER.pos.y;
  VM_GLOBAL(VAR_1_C) = rpg_cursor_base_pos;

  PLAYER.pos.x = ((PLAYER.pos.x >> 7) << 7);
  PLAYER.pos.y = ((PLAYER.pos.y >> 7) << 7);

  loadFontIntoBkg();
  // handle_action(TURN_BuildInitiative);
  // init_actions();
  dispatch_action(PANEL_OpenPanel);
  rpg_menu_mode = RPG_HAS_UPDATE;
}

void rpg_combat_update(void) BANKED {

  if (rpg_menu_mode == RPG_HAS_UPDATE) {
    take_action();
    return;
  }

  // Skip waiting for frames if its handling logic
  if (rpg_menu_mode == RPG_ENEMY_MODE) {
    return rpg_enemy_turn();
  }

  // Skip continuing logic if its not the right frame
  if (rpg_c_timer < 6) {
    rpg_c_timer++;
    return;
  }

  switch (rpg_menu_mode) {
  case RPG_SELECT_MENU_ITEM_MODE:
    rpg_select_menu_item();
    break;
  case RPG_SELECT_ENEMY_MODE:
    rpg_select_enemy();
    break;
  case RPG_SELECT_ALLY_MODE:
    rpg_select_ally();
    break;
  default:
    break;
  }

  if (INPUT_RECENT_UP || INPUT_RECENT_DOWN) {
    rpg_c_timer = 0;
  }
}

void rpg_select_menu_item(void) BANKED {
  if (INPUT_RECENT_UP) {
    rpg_menu_selection--;
    if (rpg_menu_selection < 1) {
      rpg_menu_selection = 1;
    }
  } else if (INPUT_RECENT_DOWN) {
    rpg_menu_selection++;
    if (rpg_menu_selection > rpg_max_menu_selection) {
      rpg_menu_selection = rpg_max_menu_selection;
    }
  }

  PLAYER.pos.y = ((rpg_cursor_base_pos + ((rpg_menu_selection - 1) * 128)) >> 7)
                 << 7;
  VM_GLOBAL(VAR_2_C) = rpg_cursor_base_pos;
}

void rpg_select_enemy(void) BANKED{}
void rpg_select_ally(void) BANKED{}
void rpg_enemy_turn(void) BANKED{}