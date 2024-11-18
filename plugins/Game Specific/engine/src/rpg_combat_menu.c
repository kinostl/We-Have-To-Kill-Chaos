#include "states/rpg_combat.h"

#include "ui.h"
#include "game_time.h"
#include "camera.h"
#include "scroll.h"
#include "input.h"
#include "actor.h"
#include "projectiles.h"
#include "shadow.h"
#include "position.h"
#include <gb/gb.h>
#include <math.h>
#pragma bank 255


inline void menu_loop_preamble(){
    input_update();
    ui_update();

    toggle_shadow_OAM();
    camera_update();
    scroll_update();
    actors_update();
    projectiles_render();
    activate_shadow_OAM();

    game_time++;
    vsync();
}

UBYTE rpg_run_menu(void) BANKED {
  UBYTE current_index = 0;
  UBYTE max_index = 8;

  PLAYER.hidden = FALSE;
  PLAYER.pos.x = pos(11);
  PLAYER.pos.y = pos(6);

  while (TRUE) {
    menu_loop_preamble();

    if (INPUT_UP_PRESSED) {
      if (current_index - 1 > -1) {
        current_index--;
      }
    } else if (INPUT_DOWN_PRESSED) {
      if (current_index + 1 < max_index) {
        current_index++;
      }
    } else if (INPUT_A_PRESSED) {
      PLAYER.hidden = TRUE;
      return current_index;
    } else {
      switch (current_index) {
      case 0:
        PLAYER.pos.y = pos(6);
        break;
      case 1:
        PLAYER.pos.y = pos(8);
        break;
      case 2:
        PLAYER.pos.y = pos(10);
        break;
      case 3:
        PLAYER.pos.y = pos(12);
        break;
      case 4:
        PLAYER.pos.y = pos(14);
        break;
      case 5:
        PLAYER.pos.y = pos(15);
        break;
      case 6:
        PLAYER.pos.y = pos(16);
        break;
      case 7:
        PLAYER.pos.y = pos(17);
        break;
      }
      continue;
    }
  };
}

UBYTE rpg_get_target_ally (void) BANKED {

}

UBYTE rpg_get_target_enemy(void) BANKED {
  UBYTE current_index = 0;
  UBYTE max_index = 6;

  PLAYER.pos.x = pos(1);
  PLAYER.pos.y = pos(6);

  while (TRUE) {
    menu_loop_preamble();
    if (INPUT_UP_PRESSED) {
      if (current_index - 1 > -1) {
        current_index--;
      }
    } else if (INPUT_DOWN_PRESSED) {
      if (current_index + 1 < max_index) {
        current_index++;
      }
    } else if (INPUT_A_PRESSED) {
      return current_index;
    } else {
      switch (current_index) {
      case 0:
        PLAYER.pos.x = pos(1);
        PLAYER.pos.y = pos(6);
        break;
      case 1:
        PLAYER.pos.x = pos(1);
        PLAYER.pos.y = pos(10);
        break;
      case 2:
        PLAYER.pos.x = pos(1);
        PLAYER.pos.y = pos(14);
        break;
      case 3:
        PLAYER.pos.x = pos(5);
        PLAYER.pos.y = pos(6);
        break;
      case 4:
        PLAYER.pos.x = pos(5);
        PLAYER.pos.y = pos(10);
        break;
      case 5:
        PLAYER.pos.x = pos(5);
        PLAYER.pos.y = pos(14);
        break;
      }
      continue;
    }
  }
}