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

UWORD rpg_cursor_base_pos;
UWORD rpg_menu_selection;
UWORD rpg_max_menu_selection;

#define RPG_SELECT_MENU_ITEM_MODE 0
#define RPG_SELECT_ENEMY_MODE 1
#define RPG_SELECT_ALLY_MODE 2
#define RPG_ENEMY_MODE 3

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
}

void rpg_combat_update(void) BANKED {
  const UINT16 m_type = VM_GLOBAL(VAR_3_C);

  // Skip waiting for frames if its handling logic
  if (m_type == RPG_ENEMY_MODE) {
    return rpg_enemy_turn();
  }

  // Skip continuing logic if its not the right frame
  if (!IS_FRAME_8) {
    return;
  }

  switch (m_type) {
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