#ifndef FF_TYPES
#define FF_TYPES

#include <asm/types.h>
#include <gbs_types.h>

typedef struct {
    UBYTE bank;
    const unsigned char * map_ptr;
    const unsigned char * attrs_ptr;
} overworld_far_ptr;
#endif