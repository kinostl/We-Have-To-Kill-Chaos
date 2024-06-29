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
#endif