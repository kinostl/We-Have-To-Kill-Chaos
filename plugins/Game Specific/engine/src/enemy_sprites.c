#include "handle_flashing.h"
#include <asm/types.h>
#pragma bank 255

#include "enemy_sprites.h"
#include "data/tileset_enemies_imp.h"
#include "data/tileset_enemies_wolf.h"
#include "data/tileset_enemies_mad_pony.h"
#include "enums.h"
#include <gb/gb.h>
#include <gb/cgb.h>

#define RED_PAL                                                                \
  { RGB(0, 0, 0), RGB(0, 0, 0), RGB(0, 0, 0) }

const enemy_sprite enemy_sprite_db[] = {
    [IMP] =
        {
            .sprite = &tileset_enemies_imp,
            .colors = RED_PAL,
            .bank = BANK(tileset_enemies_imp),
        },
    [WOLF] =
        {
            .sprite = &tileset_enemies_wolf,
            .colors = RED_PAL,
            .bank = BANK(tileset_enemies_wolf),
        },
    [MADPONY] =
        {
            .sprite = &tileset_enemies_mad_pony,
            .colors = RED_PAL,
            .bank = BANK(tileset_enemies_mad_pony),
        },
};

UBYTE load_enemy_tiles(UBYTE start_of_enemy_vram, ENEMY_TYPE enemy_type) BANKED {
  enemy_sprite sprite;

  MemcpyBanked(&sprite, &enemy_sprite_db[enemy_type], sizeof(enemy_sprite), BANK(FF_ENEMY_SPRITES));

  const tileset_t * t_set = sprite.sprite;
  UWORD n_tiles = ReadBankedUWORD(&(t_set->n_tiles), sprite.bank);
  UBYTE * data = t_set->tiles;

  SetBankedBkgData(start_of_enemy_vram, n_tiles, data, sprite.bank);
  return n_tiles; // New end of available VRAM
}

void draw_enemy_sm(UBYTE enemy_tiles, UBYTE x, UBYTE y) BANKED {
  UBYTE buf[4*4];
  for(UBYTE i=0;i<4*4;i++)
    buf[i] = enemy_tiles+i;

  set_bkg_tiles(x, y, 4, 4, buf);
  handle_bkg_set_color(1, x, y, 4, 4);
}

void draw_enemy_lg(UBYTE enemy_tiles, UBYTE x, UBYTE y) BANKED {
  UBYTE buf[6*6];
  for(UBYTE i=0;i<6*6;i++)
    buf[i] = enemy_tiles+i;

  set_bkg_tiles(x, y, 6, 6, buf);
  handle_bkg_set_color(1, x, y, 6, 6);
}

BANKREF(FF_ENEMY_SPRITES)