#include "bkg_tile_info.h"
#include "data_manager.h"
#include "ff_types.h"
#include "states/topdown.h"
#include <asm/types.h>
#include <bankdata.h>
#include <camera.h>
#include <collision.h>
#include <gb/cgb.h>
#include <gb/gb.h>
#include <gb/hardware.h>
#include <gbs_types.h>
#include <input.h>
#include <interrupts.h>
#include <scroll.h>
#include <types.h>
#pragma bank 255

#include "overworld/overworld_tiles.h"
#include "palette.h"
#include "states/overworld.h"

void overworld_init(void) BANKED {
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

}

void overworld_update(void) BANKED {
  topdown_update();
  if (INPUT_A_OR_B_PRESSED) {
    overworld_far_ptr overworld_ptr;
    set_overworld_ptr(&overworld_ptr, 0, 0);

    image_bank = overworld_ptr.bank;
    image_ptr = overworld_ptr.map_ptr;

    image_attr_bank = overworld_ptr.bank;
    image_attr_ptr = overworld_ptr.attrs_ptr;

    scroll_repaint();
  }
}
