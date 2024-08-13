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

void eventMyMenu(SCRIPT_CTX *THIS) OLDCALL BANKED {
  THIS;
  UBYTE cursorW = *(UBYTE *)VM_REF_TO_PTR(FN_ARG3);
  union tile _tile;
  clearTile(&_tile);
  _tile.attr.draw_over_objects = FALSE;
  _tile.attr.palette = 7;
  VBK_REG = 1;
  fill_win_rect(0, 0, cursorW + 1, 10, _tile._tile);
  VBK_REG = 0;

  UBYTE idx = *(UBYTE *)VM_REF_TO_PTR(FN_ARG0);
  UBYTE actorId = *(UBYTE *)VM_REF_TO_PTR(FN_ARG1);
  UBYTE menuSize = *(UBYTE *)VM_REF_TO_PTR(FN_ARG2);
  UBYTE cancelOnB = *(UBYTE *)VM_REF_TO_PTR(FN_ARG4);
  UBYTE cancelOnLast = *(UBYTE *)VM_REF_TO_PTR(FN_ARG5);
  UWORD start_x = actors[actorId].pos.x;
  UWORD start_y = actors[actorId].pos.y;
  _Bool start_hidden = actors[actorId].hidden;
  _Bool start_pinned = actors[actorId].pinned;

  actors[actorId].pos.x = 128;
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
      if (VM_GLOBAL(idx) > menuSize) {
        VM_GLOBAL(idx) = menuSize;
      }
      continue;
    } else if (INPUT_A_PRESSED) {
      if (cancelOnLast > 0 && VM_GLOBAL(idx) == menuSize) {
        VM_GLOBAL(idx) = 0;
      }
      break;
    } else if ((INPUT_B_PRESSED)) {
      if (cancelOnB > 0) {
        VM_GLOBAL(idx) = 0;
        break;
      }
      continue;
    } else {
      continue;
    }
  };

  actors[actorId].hidden = start_hidden;
  actors[actorId].pinned = start_pinned;
  actors[actorId].pos.x = start_x;
  actors[actorId].pos.y = start_y;
}