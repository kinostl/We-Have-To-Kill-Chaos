#pragma bank 255

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

void makeBkgFlash(SCRIPT_CTX *THIS) OLDCALL BANKED {

  const int16_t COLOR_1 = *(int16_t *)VM_REF_TO_PTR(FN_ARG5);
  const int16_t COLOR_2 = *(int16_t *)VM_REF_TO_PTR(FN_ARG4);
  const int16_t DES_X = *(int16_t *)VM_REF_TO_PTR(FN_ARG3);
  const int16_t DES_Y = *(int16_t *)VM_REF_TO_PTR(FN_ARG2);
  const int16_t W1 = *(int16_t *)VM_REF_TO_PTR(FN_ARG1);
  const int16_t H1 = *(int16_t *)VM_REF_TO_PTR(FN_ARG0);

  union tile my_tile;
  my_tile.attr.bank = 0;
  my_tile.attr.nothing = 0;
  my_tile.attr.flip_h = 0;
  my_tile.attr.flip_v = 0;
  my_tile.attr.draw_over_objects = 0;

  VBK_REG = 1;

  for (uint8_t i = 0; i < 2; i++) {
    my_tile.attr.palette = COLOR_2;
    fill_bkg_rect(DES_X, DES_Y, W1, H1, my_tile._tile);
    vsync();
    delay(100);
    my_tile.attr.palette = COLOR_1;
    fill_bkg_rect(DES_X, DES_Y, W1, H1, my_tile._tile);
    vsync();
    delay(100);
  }

  VBK_REG = 0;
}