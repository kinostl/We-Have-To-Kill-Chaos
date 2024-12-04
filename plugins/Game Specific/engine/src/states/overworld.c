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
overworld_quad overworld_tile_quad;

inline WORD get_offset(BYTE x, BYTE y){
  return x+(y*32);
}

void draw_quad(overworld_quad quad, overworld_far_ptr *map) BANKED {
  WORD x, y, offset=0;
  switch (quad) {
  case Q_TOP_LEFT:
    x = 0;
    y = 0;
    break;
  case Q_TOP_RIGHT:
    x = 16;
    y = 0;
    break;
  case Q_BOT_LEFT:
    x = 0;
    y = 16;
    break;
  case Q_BOT_RIGHT:
    x = 16;
    y = 16;
    break;
  default:
    x = 0;
    y = 0;
    break;
  }

  VBK_REG = VBK_ATTRIBUTES;
  SetBankedBkgSubmap(x, y, 16, 16, map->attrs_ptr+offset, 32, map->bank);
  VBK_REG = VBK_TILES;
  SetBankedBkgSubmap(x, y, 16, 16, map->map_ptr+offset, 32, map->bank);
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

  scroll_x_max = 256 - ((UINT16)SCREENWIDTH);
  scroll_y_max = 256 - ((UINT16)SCREENHEIGHT);

  // update_world(0, 0);
}

void overworld_update(void) BANKED {
  topdown_update();
  // const BYTE x = (camera_x >> 4) - (SCREENWIDTH >> 1);
  // const BYTE y = (camera_y >> 4) - (SCREENHEIGHT >> 1);

  // const BYTE current_col = scroll_x >> 3;
  // const BYTE current_row = scroll_y >> 3;
  // const BYTE new_col = x >> 3;
  // const BYTE new_row = y >> 3;

  static BYTE map_x = 6;
  static BYTE map_y = 9;

  const BYTE new_col = PLAYER.pos.x >> 7;
  const BYTE new_row = PLAYER.pos.y >> 7;
  const overworld_quad prev_quad = overworld_tile_quad;

  // When player steps into new 256-grid ???
  if (new_col > 31) {
    map_x++;
    PLAYER.pos.x = 0 << 7;
  } else if (new_col < 0) {
    map_x--;
    PLAYER.pos.x = 32 << 7;
  } else if (new_row > 31) {
    map_y++;
    PLAYER.pos.y = 0 << 7;
  } else if (new_row < 0) {
    map_y--;
    PLAYER.pos.y = 32 << 7;
  }

  if(map_x > 15){map_x = 0;}
  if(map_x < 0){map_x = 15;}
  if(map_y > 15){map_y = 0;}
  if(map_y < 0){map_y = 15;}

  // // Assume player is always in a 256 sq px grid
  // // Split that into 4 sub-grids

  // // If in the top-left, set left and up
  // // If in the top-right, set right and up

  // // If in the bot-left, set left and down
  // // If in the bot-right, set right and down
    const UBYTE on_left_edge = (PLAYER.pos.x >> 7) < 8;
    const UBYTE on_right_edge = (PLAYER.pos.x >> 7) > 24;

    const UBYTE on_top_edge = (PLAYER.pos.y >> 7) < 8;
    const UBYTE on_bottom_edge = (PLAYER.pos.y >> 7) > 24;

    if (on_left_edge && on_top_edge) {
      // Top Left
      overworld_tile_quad = Q_TOP_LEFT;
    } else if (on_right_edge && on_top_edge) {
      // Top Right
      overworld_tile_quad = Q_TOP_RIGHT;
    } else if (on_left_edge && on_bottom_edge) {
      // Bottom Left
      overworld_tile_quad = Q_BOT_LEFT;
    } else if (on_right_edge && on_bottom_edge){
      // Bottom Right
      overworld_tile_quad = Q_BOT_RIGHT;
    }else if (on_top_edge) {
      overworld_tile_quad = Q_TOP;
    }else if(on_bottom_edge){
      overworld_tile_quad = Q_BOT;
    }
    else if(on_left_edge){
      overworld_tile_quad = Q_LEFT;
    }
    else if(on_right_edge){
      overworld_tile_quad = Q_RIGHT;
    }
    else{
      overworld_tile_quad = Q_CENTER;
    }

  if(prev_quad != overworld_tile_quad){


    // 0 Top Left
    // 1 Top Right
    // 2 Bottom Left
    // 3 Bottom Right
    switch (overworld_tile_quad) {
    case Q_CENTER:
      set_overworld_ptr(&overworld_maps[3], map_x, map_y);
      set_overworld_ptr(&overworld_maps[2], map_x, map_y);
      set_overworld_ptr(&overworld_maps[1], map_x, map_y);
      set_overworld_ptr(&overworld_maps[0], map_x, map_y);
      break;
    case Q_TOP_LEFT:
      set_overworld_ptr(&overworld_maps[3], map_x - 1, map_y - 1);
      set_overworld_ptr(&overworld_maps[2], map_x, map_y - 1);
      set_overworld_ptr(&overworld_maps[1], map_x - 1, map_y);
      set_overworld_ptr(&overworld_maps[0], map_x, map_y);

      break;
    case Q_TOP_RIGHT:
      set_overworld_ptr(&overworld_maps[3], map_x, map_y - 1);
      set_overworld_ptr(&overworld_maps[2], map_x + 1, map_y - 1);
      set_overworld_ptr(&overworld_maps[1], map_x, map_y);
      set_overworld_ptr(&overworld_maps[0], map_x + 1, map_y);

      break;
    case Q_BOT_LEFT:
      set_overworld_ptr(&overworld_maps[3], map_x - 1, map_y);
      set_overworld_ptr(&overworld_maps[2], map_x, map_y);
      set_overworld_ptr(&overworld_maps[1], map_x - 1, map_y + 1);
      set_overworld_ptr(&overworld_maps[0], map_x, map_y + 1);

      break;
    case Q_BOT_RIGHT:
      set_overworld_ptr(&overworld_maps[3], map_x, map_y);
      set_overworld_ptr(&overworld_maps[2], map_x + 1, map_y);
      set_overworld_ptr(&overworld_maps[1], map_x, map_y + 1);
      set_overworld_ptr(&overworld_maps[0], map_x + 1, map_y + 1);
      break;
    case Q_TOP:
      set_overworld_ptr(&overworld_maps[0], map_x, map_y);
      set_overworld_ptr(&overworld_maps[1], map_x, map_y);
      set_overworld_ptr(&overworld_maps[2], map_x, map_y - 1);
      set_overworld_ptr(&overworld_maps[3], map_x, map_y - 1);
      break;
    case Q_RIGHT:
      set_overworld_ptr(&overworld_maps[0], map_x + 1, map_y);
      set_overworld_ptr(&overworld_maps[1], map_x, map_y);
      set_overworld_ptr(&overworld_maps[2], map_x + 1, map_y);
      set_overworld_ptr(&overworld_maps[3], map_x, map_y);
      break;
    case Q_BOT:
      set_overworld_ptr(&overworld_maps[0], map_x, map_y + 1);
      set_overworld_ptr(&overworld_maps[1], map_x, map_y + 1);
      set_overworld_ptr(&overworld_maps[2], map_x, map_y);
      set_overworld_ptr(&overworld_maps[3], map_x, map_y);
      break;
    case Q_LEFT:
      set_overworld_ptr(&overworld_maps[0], map_x, map_y);
      set_overworld_ptr(&overworld_maps[1], map_x - 1, map_y);
      set_overworld_ptr(&overworld_maps[2], map_x, map_y);
      set_overworld_ptr(&overworld_maps[3], map_x - 1, map_y);
      break;
    }
      draw_quad(Q_BOT_RIGHT, &overworld_maps[3]);
      draw_quad(Q_BOT_LEFT, &overworld_maps[2]);
      draw_quad(Q_TOP_RIGHT, &overworld_maps[1]);
      draw_quad(Q_TOP_LEFT, &overworld_maps[0]);
    
  }

}