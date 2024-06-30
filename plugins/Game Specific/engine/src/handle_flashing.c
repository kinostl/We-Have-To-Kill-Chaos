#include "handle_submapping.h"
#include "handle_flashing.h"
#include "vm.h"
#include <asm/types.h>
#include <gb/gb.h>
#include <stdint.h>

#pragma bank 255

void handle_bkg_flash(WORD color_1, WORD color_2, WORD x, WORD y, WORD w, WORD h) OLDCALL BANKED{
  union tile my_tile;
  my_tile.attr.bank = 0;
  my_tile.attr.nothing = 0;
  my_tile.attr.flip_h = 0;
  my_tile.attr.flip_v = 0;
  my_tile.attr.draw_over_objects = 0;

  VBK_REG = 1;

  for (uint8_t i = 0; i < 2; i++) {
    my_tile.attr.palette = color_2;
    fill_bkg_rect(x, y, w, h, my_tile._tile);
    vsync();
    delay(100);
    my_tile.attr.palette = color_1;
    fill_bkg_rect(x, y, w, h, my_tile._tile);
    vsync();
    delay(100);
  }

  VBK_REG = 0;
}

void makeBkgFlash(SCRIPT_CTX *THIS) OLDCALL BANKED {

  const int16_t COLOR_1 = *(int16_t *)VM_REF_TO_PTR(FN_ARG5);
  const int16_t COLOR_2 = *(int16_t *)VM_REF_TO_PTR(FN_ARG4);
  const int16_t X = *(int16_t *)VM_REF_TO_PTR(FN_ARG3);
  const int16_t Y = *(int16_t *)VM_REF_TO_PTR(FN_ARG2);
  const int16_t W = *(int16_t *)VM_REF_TO_PTR(FN_ARG1);
  const int16_t H = *(int16_t *)VM_REF_TO_PTR(FN_ARG0);

  handle_bkg_flash(COLOR_1, COLOR_2, X, Y, W, H);
}
