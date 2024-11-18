#ifndef FF_POSITION_DATA
#define FF_POSITION_DATA

#include <asm/types.h>

typedef struct {
    BYTE x;
    BYTE y;
    BYTE w;
    BYTE h;
} ff_position_t;

#endif