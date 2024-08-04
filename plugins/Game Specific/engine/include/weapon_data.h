#ifndef FF_WEAPON_DATA
#define FF_WEAPON_DATA
#include <asm/types.h>
#include "macro.h"

enum W_TYPE {
    UNARMED,
    FISTS,
    DAGGER,
    HAMMER,
    NUNCHUCKS,
    STAFF,
    SWORD_1,
    SWORD_2,
    SWORD_3
};

enum W_COLOR {
    DMG,
    BROWN,
    GREY,
    PURPLE,
    PINK
};

enum W_CLASSES{
    FIGHTER,
    THIEF,
    MONK,
    RED_MAGE,
    WHITE_MAGE,
    BLACK_MAGE,
    BLUE_MAGE
};

#define add_fighter(c) SET_FLAG(c, FIGHTER)
#define add_thief(c) SET_FLAG(c, THIEF)
#define add_monk(c) SET_FLAG(c, MONK)
#define add_red_mage(c) SET_FLAG(c, RED_MAGE)
#define add_white_mage(c) SET_FLAG(c, WHITE_MAGE)
#define add_black_mage(c) SET_FLAG(c, BLACK_MAGE)
#define add_blue_mage(c) SET_FLAG(c, BLUE_MAGE)

struct weapon_data {
    BYTE id;
    enum W_TYPE type;
    enum W_COLOR color;
    BYTE attack;
    BYTE hit_chance;
    BYTE crit_chance;
    UWORD price;
    UWORD classes; // Flag
};

void set_weapon(BYTE weapon_id, struct weapon_data *weapon) OLDCALL BANKED;
#endif