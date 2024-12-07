#include "handle_flashing.h"
#include <asm/types.h>
#include <data/enemy_palettes.h>
#include <gbs_types.h>
#include <string.h>
#pragma bank 255

#include "enemy_sprites.h"
#include "data/tileset_enemies_imp.h"
#include "data/tileset_enemies_wolf.h"
#include "data/tileset_enemies_mad_pony.h"
#include "enums.h"
#include <gb/gb.h>
#include <gb/cgb.h>
#include "palette.h"

const ENEMY_PALETTES empty_colors[4] = {NO_ENEMY_PALETTE, NO_ENEMY_PALETTE, NO_ENEMY_PALETTE, NO_ENEMY_PALETTE};
ENEMY_PALETTES assigned_colors[4] = {NO_ENEMY_PALETTE, NO_ENEMY_PALETTE, NO_ENEMY_PALETTE, NO_ENEMY_PALETTE};

//hex values for colors because thats what is easiest to copy from GIMP

const enemy_sprite enemy_sprite_db[] = {
    [IMP] =
        {
            .sprite = &tileset_enemies_imp,
            .palette = ENEMY_RED,
            .bank = BANK(tileset_enemies_imp),
        },
    [WOLF] =
        {
            .sprite = &tileset_enemies_wolf,
            .palette = ENEMY_RED,
            .bank = BANK(tileset_enemies_wolf),
        },
    [MADPONY] =
        {
            .sprite = &tileset_enemies_mad_pony,
            .palette = ENEMY_BROWN,
            .bank = BANK(tileset_enemies_mad_pony),
        },
    [GrIMP] =
        {
            .sprite = &tileset_enemies_imp,
            .palette = ENEMY_PURPLE,
            .bank = BANK(tileset_enemies_imp),
        },
};

inline UBYTE get_palette_id(ENEMY_PALETTES color){
    UBYTE i=0;
    const UBYTE offset=1; //0 is for Header
    while(i<4){
      if (assigned_colors[i] == color)
        return i+offset;
      if (assigned_colors[i] == NO_ENEMY_PALETTE){
        assigned_colors[i] = color;
        load_enemy_palette(&BkgPalette[i+offset], color);
        return i+offset;
      }
      i++;
    }
}

void clean_enemy_tiles() BANKED{
  memcpy(assigned_colors, empty_colors, sizeof(assigned_colors));
}

void load_enemy_tiles(enemy_view *enemy_view, ENEMY_TYPE enemy_type) BANKED {
  enemy_sprite sprite;

  MemcpyBanked(&sprite, &enemy_sprite_db[enemy_type], sizeof(enemy_sprite), BANK(FF_ENEMY_SPRITES));

  const tileset_t * t_set = sprite.sprite;
  const UWORD n_tiles = ReadBankedUWORD(&(t_set->n_tiles), sprite.bank);
  const UBYTE * data = t_set->tiles;

  SetBankedBkgData(enemy_view->vram_ptr, n_tiles, data, sprite.bank);

  enemy_view->palette_id = get_palette_id(sprite.palette);
  enemy_view->n_tiles = n_tiles;
}


void draw_enemy_sm(enemy_view *enemy_view, UBYTE x, UBYTE y) BANKED {
  UBYTE buf[4*4];
  for(UBYTE i=0;i<4*4;i++)
    buf[i] = enemy_view->vram_ptr+i;

  set_bkg_tiles(x, y, 4, 4, buf);
  handle_bkg_set_color(enemy_view->palette_id, x, y, 4, 4);
}

void draw_enemy_lg(enemy_view *enemy_view, UBYTE x, UBYTE y) BANKED {
  UBYTE buf[6*6];
  for(UBYTE i=0;i<6*6;i++)
    buf[i] = enemy_view->vram_ptr+i;

  set_bkg_tiles(x, y, 6, 6, buf);
  handle_bkg_set_color(enemy_view->palette_id, x, y, 6, 6);
}

BANKREF(FF_ENEMY_SPRITES)