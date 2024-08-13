#include "handle_submapping.h"
#include <asm/types.h>
#include <camera.h>
#include <data/game_globals.h>
#include <game_time.h>
#include <gb/gb.h>
#include <gb/hardware.h>
#include <input.h>
#include <projectiles.h>
#include <scroll.h>
#include <shadow.h>
#include <ui.h>
#include <vm.h>
#pragma bank 255

void eventLayerMenu(SCRIPT_CTX *THIS) OLDCALL BANKED {
  THIS;
  union tile _tile;
  clearTile(&_tile);
  _tile.attr.draw_over_objects = TRUE;
  _tile.attr.palette = 7;
  VBK_REG = 1;
  fill_win_rect(2, 0, 18, 2, _tile._tile);
  VBK_REG = 0;
}

void eventMyMenu(SCRIPT_CTX *THIS) OLDCALL BANKED {
  THIS;
  UBYTE idx = *(UBYTE *)VM_REF_TO_PTR(FN_ARG0);
  UBYTE actorId = *(UBYTE *)VM_REF_TO_PTR(FN_ARG1);
  UBYTE menuSize = *(UBYTE *)VM_REF_TO_PTR(FN_ARG2);

  actors[actorId].pos.x = 0;
  actors[actorId].hidden = FALSE;
  actors[actorId].pinned = TRUE;

  UBYTE yOffset = (18 - menuSize - 1);

  VM_GLOBAL(idx) = 1;

  while (TRUE) {
    actors[actorId].pos.y = (yOffset + VM_GLOBAL(idx)) * 128;

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
      VM_GLOBAL(idx)--;
      if (VM_GLOBAL(idx) < 1) {
        VM_GLOBAL(idx) = 1;
      }
      continue;
    } else if (INPUT_DOWN_PRESSED) {
      VM_GLOBAL(idx)++;
      if (VM_GLOBAL(idx) >= menuSize) {
        VM_GLOBAL(idx) = menuSize;
      }
      continue;
    } else if (INPUT_A_PRESSED) {
      break;
    } else if ((INPUT_B_PRESSED)) {
      VM_GLOBAL(idx) = 0;
      break;
    } else {
      continue;
    }
  };
  actors[actorId].hidden = TRUE;
}