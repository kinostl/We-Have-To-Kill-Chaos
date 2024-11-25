#ifndef FF_ENEMY_SPRITES
#define FF_ENEMY_SPRITES

#include <bankdata.h>
#include <gb/gb.h>
#include <gbs_types.h>

typedef struct {
    UBYTE bank;
    const void * sprite;
    UWORD colors[3];
} enemy_sprite ;

extern const enemy_sprite enemy_sprite_db[];

BANKREF_EXTERN(FF_ENEMY_SPRITES)

#endif
