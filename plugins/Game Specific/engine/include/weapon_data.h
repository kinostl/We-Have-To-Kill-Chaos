#ifndef FF_WEAPON_DATA
#define FF_WEAPON_DATA
#include <asm/types.h>
struct weapon_data {
    BYTE id;
    BYTE type;
    BYTE color;
    BYTE attack;
    BYTE hit_chance;
    BYTE crit_chance;
    BYTE price;
    BYTE classes; // Flag
};
#endif