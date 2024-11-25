#ifndef FF_ENEMY_SPRITES
#define FF_ENEMY_SPRITES

#include "enums.h"
#include <bankdata.h>
#include <gb/gb.h>
#include <gbs_types.h>

typedef enum {
    SMALL_ENEMY,
    LARGE_ENEMY
} ENEMY_SIZE;

typedef struct {
    UBYTE bank;
    const void * sprite;
    UWORD colors[3];
} enemy_sprite ;

extern const enemy_sprite enemy_sprite_db[];
UBYTE load_enemy_tiles(UBYTE start_of_enemy_vram, ENEMY_TYPE enemy_type) BANKED;
void draw_enemy_sm(UBYTE enemy_tiles, UBYTE x, UBYTE y) BANKED;
void draw_enemy_lg(UBYTE enemy_tiles, UBYTE x, UBYTE y) BANKED;

BANKREF_EXTERN(FF_ENEMY_SPRITES)

#endif
