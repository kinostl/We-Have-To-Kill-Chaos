#ifndef FF_INV_SLOTS
#define FF_INV_SLOTS
#include <asm/types.h>

enum I_TYPE{
    POTION_I,
    WEAPON_I,
    ARMOR_I
};

struct item_slot{
    BYTE id;
    enum I_TYPE type; //Armor, Weapon, Potion, etc
    BYTE count;
};

#endif