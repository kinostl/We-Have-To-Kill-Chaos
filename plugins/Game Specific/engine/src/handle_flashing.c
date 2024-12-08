#include <asm/types.h>
#include <gb/gb.h>
#include <stdint.h>
#include "handle_flashing.h"
#include "handle_submapping.h"
#include "vm.h"

#pragma bank 255

void handle_bkg_set_color(WORD color, WORD x, WORD y, WORD w,
                          WORD h) OLDCALL BANKED {
  union tile my_tile;
  my_tile.attr.bank = 0;
  my_tile.attr.nothing = 0;
  my_tile.attr.flip_h = 0;
  my_tile.attr.flip_v = 0;
  my_tile.attr.draw_over_objects = 0;
  my_tile.attr.palette = color;
  VBK_REG = 1;
  fill_bkg_rect(x, y, w, h, my_tile._tile);
  VBK_REG = 0;
}
void handle_bkg_flash(WORD color_1, WORD color_2, WORD x, WORD y, WORD w,
                      WORD h) OLDCALL BANKED {
  union tile my_tile;
  my_tile.attr.bank = 0;
  my_tile.attr.nothing = 0;
  my_tile.attr.flip_h = 0;
  my_tile.attr.flip_v = 0;
  my_tile.attr.draw_over_objects = 0;
  my_tile.attr.palette = color_1;
  VBK_REG = 1;
  for (uint8_t i = 0; i < 2; i++) {
    my_tile.attr.palette = color_2;
    fill_bkg_rect(x, y, w, h, my_tile._tile);
    for(UBYTE i=0;i<6;i++){
    vsync();
    }
    my_tile.attr.palette = color_1;
    fill_bkg_rect(x, y, w, h, my_tile._tile);
    for(UBYTE i=0;i<6;i++){
    vsync();
    }
  }
  VBK_REG = 0;
}

void makeBkgFlash(SCRIPT_CTX *THIS) OLDCALL BANKED {

  int16_t COLOR_1 = *(int16_t *)VM_REF_TO_PTR(FN_ARG5);
  int16_t COLOR_2 = *(int16_t *)VM_REF_TO_PTR(FN_ARG4);
  int16_t X = *(int16_t *)VM_REF_TO_PTR(FN_ARG3);
  int16_t Y = *(int16_t *)VM_REF_TO_PTR(FN_ARG2);
  int16_t W = *(int16_t *)VM_REF_TO_PTR(FN_ARG1);
  int16_t H = *(int16_t *)VM_REF_TO_PTR(FN_ARG0);

  handle_bkg_flash(COLOR_1, COLOR_2, X, Y, W, H);
}

void handle_bkg_set_color_slow(WORD color, WORD x, WORD y, WORD w,
                          WORD h) OLDCALL BANKED {
  union tile my_tile;
  my_tile.attr.bank = 0;
  my_tile.attr.nothing = 0;
  my_tile.attr.flip_h = 0;
  my_tile.attr.flip_v = 0;
  my_tile.attr.draw_over_objects = 0;
  my_tile.attr.palette = color;
  VBK_REG = 1;

  for (UBYTE dy = y; dy < y+h; dy++) {
    for (UBYTE dx = x; dx < x+w; dx++) {
      set_bkg_tile_xy(dx, dy, my_tile._tile);
      vsync();
    }
  }

  VBK_REG = 0;
}