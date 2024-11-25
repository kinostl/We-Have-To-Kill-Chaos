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
    [IMP] = {.sprite = &tileset_enemies_imp,
             .colors = RED_PAL,
             .bank = BANK(tileset_enemies_imp)},
    [WOLF] = {.sprite = &tileset_enemies_wolf,
             .colors = RED_PAL,
             .bank = BANK(tileset_enemies_wolf)},
    [MADPONY] = {.sprite = &tileset_enemies_mad_pony,
             .colors = RED_PAL,
             .bank = BANK(tileset_enemies_mad_pony)},
};

BANKREF(FF_ENEMY_SPRITES)