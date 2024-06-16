#include "bankdata.h"
#pragma bank 255

#include "collision.h"
#include "data_manager.h"
#include "vm.h"
#include <asm/types.h>
#include <gb/hardware.h>
#include <stdint.h>

#include <gb/gb.h>

void copyBkgToBkg(SCRIPT_CTX *THIS) OLDCALL BANKED {

  const int16_t DES_X = *(int16_t *)VM_REF_TO_PTR(FN_ARG5);
  const int16_t DES_Y = *(int16_t *)VM_REF_TO_PTR(FN_ARG4);
  const int16_t W1 = *(int16_t *)VM_REF_TO_PTR(FN_ARG3);
  const int16_t H1 = *(int16_t *)VM_REF_TO_PTR(FN_ARG2);
  const int16_t SRC_X = *(int16_t *)VM_REF_TO_PTR(FN_ARG1);
  const int16_t SRC_Y = *(int16_t *)VM_REF_TO_PTR(FN_ARG0);

  const int16_t offset_x = SRC_X - DES_X;
  const int16_t offset_y = SRC_Y - DES_Y;

  const unsigned char my_tiles[32*32];
  MemcpyBanked(&my_tiles,image_ptr + offset_x + (offset_y * image_tile_width), sizeof(my_tiles), image_bank);
  set_bkg_submap(DES_X, DES_Y, W1, H1, my_tiles, image_tile_width);

  MemcpyBanked(&my_tiles,image_attr_ptr + offset_x + (offset_y * image_tile_width), sizeof(my_tiles), image_attr_bank);
  VBK_REG = 1;
  set_bkg_submap(DES_X, DES_Y, W1, H1, my_tiles, image_tile_width);
  VBK_REG = 0;
}