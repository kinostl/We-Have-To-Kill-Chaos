#include "action_handler.h"
#include "animations.h"
#include "enemy_data.h"
#include "extra_data.h"
#include "ff_text.h"
#include "ff_util.h"
#include "handle_menu.h"
#include "position_data.h"
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
#include <data/rpg_combat_animation_states.h>
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

inline void move_cursor_rtl(ff_position_t pos) {
  PLAYER.pos.x = pos(pos.x + pos.w - 1);
  PLAYER.pos.y = pos(pos.y + (pos.h / 2));
}

inline void move_cursor_ltr(ff_position_t pos) {
  PLAYER.pos.x = pos(pos.x - 1);
  PLAYER.pos.y = pos(pos.y + (pos.h / 2));
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

UBYTE rpg_get_target_ally(BOOLEAN targets_dead) BANKED {
  BYTE current_index = 0;
  while (targets_dead ? FALSE : (hero_slots[current_index].ext.status & DEAD)) {
    current_index++;
  }

  BYTE previous_index = 0;
  BYTE max_index = 4;
  move_cursor_ltr(hero_slots[current_index].ext.pos);
  PLAYER.hidden = FALSE;
  while (TRUE) {
    menu_loop_preamble();
    if (INPUT_UP_PRESSED) {
      if (current_index - 1 > -1) {
        previous_index = current_index;
        current_index--;
        while (targets_dead ? FALSE
                            : (hero_slots[current_index].ext.status & DEAD)) {
          current_index--;
          if (current_index < 0) {
            current_index = previous_index;
            break;
          }
        }
      }
    } else if (INPUT_DOWN_PRESSED) {
      if (current_index + 1 < max_index) {
        previous_index = current_index;
        current_index++;
        while ((hero_slots[current_index].ext.status & DEAD)) {
          current_index++;
          if (current_index > max_index) {
            current_index = previous_index;
            break;
          }
        }
      }
    } else if (INPUT_A_PRESSED) {
      PLAYER.hidden = TRUE;
      return current_index;
    } else {
      move_cursor_ltr(hero_slots[current_index].ext.pos);
      continue;
    }
  }
  return 0;
}

UBYTE rpg_get_target_enemy(void) BANKED {
  BYTE current_index = 0;
  BYTE previous_index = 0;
  BYTE max_index = 5;
  BYTE orig_dir = PLAYER.dir;
  while ((enemy_slots[current_index].ext.status & DEAD)) {
    current_index++;
  }
  move_cursor_rtl(enemy_slots[current_index].ext.pos);
  PLAYER.hidden = FALSE;
  actor_set_dir(&PLAYER, DIR_LEFT, FALSE);

  while (TRUE) {
    menu_loop_preamble();
    if (INPUT_UP_PRESSED) {
      if (current_index - 1 > -1) {
        previous_index = current_index;
        current_index--;
        while ((enemy_slots[current_index].ext.status & DEAD)) {
          current_index--;
          if(current_index<0){
            current_index = previous_index;
            break;
          }
        }
      }
    } else if (INPUT_DOWN_PRESSED) {
      if (current_index + 1 < max_index) {
        previous_index = current_index;
        current_index++;
        while ((enemy_slots[current_index].ext.status & DEAD)) {
          current_index++;
          if(current_index>max_index){
            current_index = previous_index;
            break;
          }
        }
      }
    } else if (INPUT_A_PRESSED) {
      PLAYER.hidden = TRUE;
      actor_set_dir(&PLAYER, orig_dir, FALSE);
      return current_index;
    } else {
      move_cursor_rtl(enemy_slots[current_index].ext.pos);
      continue;
    }
  }
}