#include <asm/types.h>
#include <collision.h>
#include <gb/gb.h>
#include "handle_submapping.h"
#include "bankdata.h"
#include "data_manager.h"
#include "vm.h"

#pragma bank 255

void copyBkgToBkg(SCRIPT_CTX *THIS) OLDCALL BANKED {

  WORD COLOR = *(WORD *)VM_REF_TO_PTR(FN_ARG6);
  WORD DES_X = *(WORD *)VM_REF_TO_PTR(FN_ARG5);
  WORD DES_Y = *(WORD *)VM_REF_TO_PTR(FN_ARG4);
  WORD W1 = *(WORD *)VM_REF_TO_PTR(FN_ARG3);
  WORD H1 = *(WORD *)VM_REF_TO_PTR(FN_ARG2);
  WORD SRC_X = *(WORD *)VM_REF_TO_PTR(FN_ARG1);
  WORD SRC_Y = *(WORD *)VM_REF_TO_PTR(FN_ARG0);

  WORD offset_x = SRC_X - DES_X;
  WORD offset_y = SRC_Y - DES_Y;
  WORD offset = offset_x + (offset_y * image_tile_width);

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

void clearSection(UBYTE x, UBYTE y, UBYTE w, UBYTE h) OLDCALL BANKED {
  union tile blank_tile;
  blank_tile.attr.palette = 0;
  blank_tile.attr.bank = 0;
  blank_tile.attr.nothing = 0;
  blank_tile.attr.flip_h = 0;
  blank_tile.attr.flip_v = 0;
  blank_tile.attr.draw_over_objects = 0;

  fill_bkg_rect(x, y, w, h, blank_tile._tile);
}

void clearAttrsSection(UBYTE x, UBYTE y, UBYTE w, UBYTE h) OLDCALL BANKED {
  VBK_REG = 1;
  clearSection(x, y, w, h);
  VBK_REG = 0;
}

void clearTile(union tile * blank_tile) OLDCALL BANKED {
  blank_tile->attr.palette = 0;
  blank_tile->attr.bank = 0;
  blank_tile->attr.nothing = 0;
  blank_tile->attr.flip_h = 0;
  blank_tile->attr.flip_v = 0;
  blank_tile->attr.draw_over_objects = 0;
}

void setAttrsSectionColor(UBYTE x, UBYTE y, UBYTE w, UBYTE h, UBYTE palette_id) OLDCALL BANKED {
  VBK_REG = 1;
  union tile _tile;
  _tile.attr.palette = palette_id;
  _tile.attr.bank = 0;
  _tile.attr.nothing = 0;
  _tile.attr.flip_h = 0;
  _tile.attr.flip_v = 0;
  _tile.attr.draw_over_objects = 0;

  fill_bkg_rect(x, y, w, h, _tile._tile);
  VBK_REG = 0;
}