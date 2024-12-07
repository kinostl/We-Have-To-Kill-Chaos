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

extern const battle_header battle_header_db[];
UBYTE load_battle_header(UBYTE vram_ptr, BATTLE_ID battle_id) BANKED;
void draw_battle_header(UBYTE vram_ptr) BANKED;

BANKREF_EXTERN(FF_BATTLE_HEADERS)

#endif
