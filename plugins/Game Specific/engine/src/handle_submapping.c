#pragma bank 255

#include "handle_submapping.h"
#include "bankdata.h"
#include "data_manager.h"
#include "vm.h"
#include <gb/gb.h>

void copyBkgToBkg(SCRIPT_CTX *THIS) OLDCALL BANKED {

  const WORD COLOR = *(WORD *)VM_REF_TO_PTR(FN_ARG6);
  const WORD DES_X = *(WORD *)VM_REF_TO_PTR(FN_ARG5);
  const WORD DES_Y = *(WORD *)VM_REF_TO_PTR(FN_ARG4);
  const WORD W1 = *(WORD *)VM_REF_TO_PTR(FN_ARG3);
  const WORD H1 = *(WORD *)VM_REF_TO_PTR(FN_ARG2);
  const WORD SRC_X = *(WORD *)VM_REF_TO_PTR(FN_ARG1);
  const WORD SRC_Y = *(WORD *)VM_REF_TO_PTR(FN_ARG0);

  const WORD offset_x = SRC_X - DES_X;
  const WORD offset_y = SRC_Y - DES_Y;
  const WORD offset = offset_x + (offset_y * image_tile_width);

  UBYTE my_tiles[32 * 32];
  union tile my_tile;
  my_tile.attr.palette = COLOR;
  my_tile.attr.bank = 0;
  my_tile.attr.nothing = 0;
  my_tile.attr.flip_h = 0;
  my_tile.attr.flip_v = 0;
  my_tile.attr.draw_over_objects = 0;

  VBK_REG = 1;
  fill_bkg_rect(DES_X, DES_Y, W1, H1, my_tile._tile);

  VBK_REG = 0;
  MemcpyBanked(my_tiles, image_ptr, sizeof(my_tiles), image_bank);
  set_bkg_submap(DES_X, DES_Y, W1, H1, my_tiles + offset, image_tile_width);
}