#ifndef FF_ENEMY_SPRITES
#define FF_ENEMY_SPRITES

#include "enums.h"
#include <bankdata.h>
#include <data/enemy_palettes.h>
#include <gb/gb.h>
#include <gbs_types.h>

typedef struct {
    UBYTE bank;
    const tileset_t * sprite;
    ENEMY_PALETTES palette;
} enemy_sprite ;

typedef struct {
    UBYTE vram_ptr;
    UBYTE n_tiles;
    UBYTE palette_id;
} enemy_view;

extern const palette_entry_t enemy_palette_db[];
extern const enemy_sprite enemy_sprite_db[];
void load_enemy_tiles(enemy_view *vram_ptr, ENEMY_TYPE enemy_type) BANKED;
void draw_enemy_sm(enemy_view *enemy_view, UBYTE x, UBYTE y) BANKED;
void draw_enemy_lg(enemy_view *enemy_view, UBYTE x, UBYTE y) BANKED;

BANKREF_EXTERN(FF_ENEMY_SPRITES)

#endif
