#include "bkg_tile_info.h"
#include "data_manager.h"
#include "ff_types.h"
#include "states/topdown.h"
#include <asm/types.h>
#include <bankdata.h>
#include <camera.h>
#include <collision.h>
#include <game_time.h>
#include <gb/cgb.h>
#include <gb/gb.h>
#include <gb/hardware.h>
#include <gbs_types.h>
#include <input.h>
#include <interrupts.h>
#include <scroll.h>
#include <types.h>
#include <actor.h>
#pragma bank 255

#include "overworld/overworld_tiles.h"
#include "palette.h"
#include "states/overworld.h"
#include <math.h>

void update_world(UBYTE map_x, UBYTE map_y) BANKED {
    overworld_far_ptr overworld_ptr;
    set_overworld_ptr(&overworld_ptr, map_x, map_y);

    image_bank = overworld_ptr.bank;
    image_ptr = overworld_ptr.map_ptr;

    image_attr_bank = overworld_ptr.bank;
    image_attr_ptr = overworld_ptr.attrs_ptr;

    scroll_repaint();
}

void overworld_init(void) BANKED {
  PLAYER.pos.y = PLAYER.pos.x = 4 << 7;
  SetBankedBkgData(0, overworld_tiles_TILE_COUNT, overworld_tiles_tiles,
                   BANK(overworld_tiles));
  MemcpyBanked(BkgPalette, overworld_tiles_palettes,
               sizeof(palette_entry_t) * overworld_tiles_PALETTE_COUNT,
               BANK(overworld_tiles));

  image_tile_height = 32;
  image_tile_width = 32;
  image_width = image_tile_width * 8;
  scroll_x_max = image_width - ((UINT16)SCREENWIDTH);
  image_height = image_tile_height * 8;
  scroll_y_max = image_height - ((UINT16)SCREENHEIGHT);

  update_world(0, 0);
}

void overworld_update(void) BANKED {
  static UBYTE map_x = 0;
  static UBYTE map_y = 0;

  topdown_update();

  UBYTE next_map_x = map_x;
  UBYTE next_map_y = map_y;

  if ((PLAYER.pos.x >> 7) > 29) {
    next_map_x++;
    PLAYER.pos.x -= 29 << 7;
  } else if ((PLAYER.pos.y >> 7) > 29) {
    next_map_y++;
    PLAYER.pos.y -= 29 << 7;
  } else if ((PLAYER.pos.x >> 7) < 3) {
    next_map_x--;
    PLAYER.pos.x += 28 << 7;
  } else if ((PLAYER.pos.y >> 7) < 3) {
    next_map_y--;
    PLAYER.pos.y += 28 << 7;
  }

  if (map_x != next_map_x || map_y != next_map_y) {
    map_x = next_map_x;
    map_y = next_map_y;

    update_world(map_x, map_y);
  }
}
