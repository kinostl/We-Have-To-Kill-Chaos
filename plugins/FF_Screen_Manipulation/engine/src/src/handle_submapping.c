#include "bankdata.h"
#pragma bank 255

#include "data_manager.h"
#include "vm.h"
#include <gb/gb.h>
#include <stdint.h>

union tile {
    uint8_t _tile;
    struct {
        unsigned char palette : 3;
        unsigned char bank : 1;
        unsigned char nothing : 1;
        unsigned char flip_h : 1;
        unsigned char flip_v : 1;
        unsigned char draw_over_objects : 1;
    } attr;
};

void copyBkgToBkg(SCRIPT_CTX *THIS) OLDCALL BANKED {

  const int16_t COLOR = *(int16_t *)VM_REF_TO_PTR(FN_ARG6);
  const int16_t DES_X = *(int16_t *)VM_REF_TO_PTR(FN_ARG5);
  const int16_t DES_Y = *(int16_t *)VM_REF_TO_PTR(FN_ARG4);
  const int16_t W1 = *(int16_t *)VM_REF_TO_PTR(FN_ARG3);
  const int16_t H1 = *(int16_t *)VM_REF_TO_PTR(FN_ARG2);
  const int16_t SRC_X = *(int16_t *)VM_REF_TO_PTR(FN_ARG1);
  const int16_t SRC_Y = *(int16_t *)VM_REF_TO_PTR(FN_ARG0);

  const int16_t offset_x = SRC_X - DES_X;
  const int16_t offset_y = SRC_Y - DES_Y;
  const int16_t offset = offset_x + (offset_y * image_tile_width);

  unsigned char my_tiles[32*32];
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
  MemcpyBanked(my_tiles,image_ptr, sizeof(my_tiles), image_bank);
  set_bkg_submap(DES_X, DES_Y, W1, H1, my_tiles + offset, image_tile_width);
}