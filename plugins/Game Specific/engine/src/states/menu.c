#include <asm/types.h>
#include <data/game_globals.h>
#include <gb/gb.h>
#include <vm.h>
#pragma bank 255

#include "states/menu.h"

#include "actor.h"
#include "camera.h"
#include "input.h"
#include "math.h"
#include "load_font_into_bg.h"

UBYTE menu_selection;

UWORD cursor_base_pos;
UBYTE c_timer;

void menu_init(void) BANKED {
    menu_selection=1;
    c_timer = 7;
    cursor_base_pos = PLAYER.pos.y;

    PLAYER.pos.x = ((PLAYER.pos.x >> 7) << 7);
    PLAYER.pos.y = ((PLAYER.pos.y >> 7) << 7);

    loadFontIntoBkg();
}

void menu_update(void) BANKED {
 // Updates are counted in Frames, 6 Frames is 0.1 Seconds
  if (c_timer < 6) {
    c_timer++;
    return;
  }

  if (INPUT_RECENT_UP) {
    menu_selection--;
    if (menu_selection < 1) {
      menu_selection = 1;
    }
    c_timer = 0;
  } else if (INPUT_RECENT_DOWN) {
    menu_selection++;
    if (menu_selection > 18) {
      menu_selection = 18;
    }
    c_timer = 0;
  }

  PLAYER.pos.y = ((cursor_base_pos + ((menu_selection - 1) * 128)) >> 7) << 7;
}