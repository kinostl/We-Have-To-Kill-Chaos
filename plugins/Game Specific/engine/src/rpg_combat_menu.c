#include "states/rpg_combat.h"

#include "ui.h"
#include "game_time.h"
#include "camera.h"
#include "scroll.h"
#include "input.h"
#include "actor.h"
#include "projectiles.h"
#include "shadow.h"
#pragma bank 255

#define pos(coord) (((coord * 128) >> 7) << 7);

UBYTE rpg_run_menu(void) BANKED {
  UBYTE current_index = 0;
  UBYTE max_index = 5;
  UBYTE rpg_menu_timer = 0;
  UWORD cursor_base_pos = pos(6);

  PLAYER.pos.x = pos(11);
  PLAYER.pos.y = cursor_base_pos;

  while (TRUE) {
    input_update();
    ui_update();

    toggle_shadow_OAM();
    camera_update();
    scroll_update();
    actors_update();
    projectiles_render();
    activate_shadow_OAM();

    game_time++;
    wait_vbl_done();

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
      PLAYER.pos.y = cursor_base_pos + pos(current_index);
      continue;
    }
  };
}