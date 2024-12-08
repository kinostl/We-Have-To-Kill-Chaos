#ifndef FF_BATTLE_HEADERS
#define FF_BATTLE_HEADERS

#include "enums.h"
#include <bankdata.h>
#include <gb/gb.h>
#include <gbs_types.h>
#include "data/header_palettes.h"

typedef struct {
    UBYTE bank;
    const void * header;
    HEADER_PALETTES palette;
} battle_header ;

UBYTE load_battle_header(UBYTE vram_ptr, BATTLE_ID battle_id) BANKED;
void draw_battle_header(void) BANKED;

extern UBYTE battle_header_ptr;
extern const battle_header battle_header_db[];

inline void set_battle_header(UBYTE vram_ptr){
    battle_header_ptr = vram_ptr;
    draw_battle_header();
}

BANKREF_EXTERN(FF_BATTLE_HEADERS)

#endif
