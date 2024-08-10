#ifndef FF_HANDLE_SUBMAPPING
#define FF_HANDLE_SUBMAPPING

#include <asm/types.h>
union tile {
    UBYTE _tile;
    struct {
        UBYTE palette : 3;
        UBYTE bank : 1;
        UBYTE nothing : 1;
        UBYTE flip_h : 1;
        UBYTE flip_v : 1;
        UBYTE draw_over_objects : 1;
    } attr;
};

void clearAttrsSection(UBYTE x, UBYTE y, UBYTE w, UBYTE h) OLDCALL BANKED;
void clearSection(UBYTE x, UBYTE y, UBYTE w, UBYTE h) OLDCALL BANKED;
void clearTile(union tile * blank_tile) OLDCALL BANKED;
void setAttrsSectionColor(UBYTE x, UBYTE y, UBYTE w, UBYTE h, UBYTE palette_id) OLDCALL BANKED;
#endif