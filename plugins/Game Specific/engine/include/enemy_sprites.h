#ifndef FF_ENEMY_SPRITES
#define FF_ENEMY_SPRITES

#include <gb/gb.h>

typedef struct {
    UBYTE bank;
    UWORD colors[3];
} enemy_sprite ;

extern const enemy_sprite enemy_sprite_db[];

#endif
