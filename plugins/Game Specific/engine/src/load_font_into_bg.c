#include <asm/types.h>
#include <string.h>
#pragma bank 255
#include "load_font_into_bg.h"
#include "data/font_gbs_mono.h"
#include "data_manager.h"
#include "vm.h"
#include <bankdata.h>
#include <gbs_types.h>

UBYTE start_of_bkg_vram;
font_desc_t bg_font;
UBYTE bg_font_bank;

void loadFontIntoBkg(SCRIPT_CTX *THIS) OLDCALL BANKED {
  THIS;
  bg_font_bank = BANK(font_gbs_mono);
  scene_t c_scene;
  MemcpyBanked(&c_scene, current_scene.ptr, sizeof(scene_t),
               current_scene.bank);

  background_t c_bkg;
  MemcpyBanked(&c_bkg, c_scene.background.ptr, sizeof(background_t),
               c_scene.background.bank);

  tileset_t c_tiles;
  MemcpyBanked(&c_tiles, c_bkg.tileset.ptr, sizeof(tileset_t),
               c_bkg.tileset.bank);

  start_of_bkg_vram = c_tiles.n_tiles;
  MemcpyBanked(&bg_font, font_gbs_mono, sizeof(font_desc_t), bg_font_bank);
  SetBankedBkgData(start_of_bkg_vram,16*14, bg_font.bitmaps, bg_font_bank);
}
