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

overworld_far_ptr overworld_maps[4];
UBYTE overworld_tile_quad;

void update_world(UBYTE map_x, UBYTE map_y) BANKED {
  // Assume player is always in a 256 sq px grid
  // Split that into 4 sub-grids
  // Split *those* into 4 sub-grids?
  // So, proper grid should be 16 64 sq px spaces

  // If in the top-left, set left and up
  // If in the top-right, set right and up

  // If in the bot-left, set left and down
  // If in the bot-right, set right and down

  // When player steps into new 256-grid ???

  set_overworld_ptr(&overworld_maps[3], map_x, map_y);

  // image_bank = overworld_ptr.bank;
  // image_ptr = overworld_ptr.map_ptr;

  // image_attr_bank = overworld_ptr.bank;
  // image_attr_ptr = overworld_ptr.attrs_ptr;
  // scroll_repaint();

  // Use 0 for Up and Down
  // Use 1 for Left and Right
  // Use 2 for Inter

  /*
      const UBYTE left = (PLAYER.pos.x >> 7) < 16;
      const UBYTE top = (PLAYER.pos.y >> 7) < 16;

      if(top && left){
        // Top Left
        overworld_tile_quad = 0;
        set_overworld_ptr(&overworld_maps[0], map_x, map_y - 1);
        set_overworld_ptr(&overworld_maps[1], map_x - 1, map_y);
        set_overworld_ptr(&overworld_maps[2], map_x - 1, map_y - 1);
      }else if(top){
        // Top Right
        overworld_tile_quad = 1;
        set_overworld_ptr(&overworld_maps[0], map_x, map_y - 1);
        set_overworld_ptr(&overworld_maps[1], map_x + 1, map_y);
        set_overworld_ptr(&overworld_maps[2], map_x + 1, map_y - 1);
      }else if(left){
        // Bottom Left
        overworld_tile_quad = 2;
        set_overworld_ptr(&overworld_maps[0], map_x, map_y + 1);
        set_overworld_ptr(&overworld_maps[1], map_x - 1, map_y);
        set_overworld_ptr(&overworld_maps[2], map_x - 1, map_y + 1);
      }else{
        // Bottom Right
        overworld_tile_quad = 3;
        set_overworld_ptr(&overworld_maps[0], map_x, map_y + 1);
        set_overworld_ptr(&overworld_maps[1], map_x + 1, map_y);
        set_overworld_ptr(&overworld_maps[2], map_x + 1, map_y + 1);
      }
  */
}

void overworld_init(void) BANKED {
  PLAYER.pos.y = PLAYER.pos.x = 4 << 7;
  SetBankedBkgData(0, overworld_tiles_TILE_COUNT, overworld_tiles_tiles,
                   BANK(overworld_tiles));
  MemcpyBanked(BkgPalette, overworld_tiles_palettes,
               sizeof(palette_entry_t) * overworld_tiles_PALETTE_COUNT,
               BANK(overworld_tiles));

  // image_tile_height = 32;
  // image_tile_width = 32;
  // image_width = image_tile_width * 8;
  // image_height = image_tile_height * 8;

  // scroll_x_max = 256 - ((UINT16)SCREENWIDTH);
  // scroll_y_max = 256 - ((UINT16)SCREENHEIGHT);

  // update_world(0, 0);
}

void overworld_update(void) BANKED {
  static UBYTE map_x = 0;
  static UBYTE map_y = 0;

  topdown_update();

  UBYTE next_map_x = map_x;
  UBYTE next_map_y = map_y;

  if ((PLAYER.pos.x >> 7) > 32) {
    next_map_x++;
    PLAYER.pos.x -= (32 << 7);
  } else if ((PLAYER.pos.x >> 7) < 0) {
    next_map_x--;
    PLAYER.pos.x += (32 << 7);
  } else if ((PLAYER.pos.y >> 7) > 32) {
    next_map_y++;
    PLAYER.pos.y -= (32 << 7);
  } else if ((PLAYER.pos.y >> 7) < 0) {
    next_map_y--;
    PLAYER.pos.y += (32 << 7);
  }

  if (map_x != next_map_x || map_y != next_map_y) {
    map_x = next_map_x;
    map_y = next_map_y;

    update_world(map_x, map_y);
  }

}
