#ifndef FF_ENEMY_DATA
#define FF_ENEMY_DATA
#include <asm/types.h>
#include <gb/gb.h>

BANKREF_EXTERN(ff_enemy_data)

enum enemy_family {
    NONE,
    GIANT
};

enum enemy_name {
    IMP,
    GrIMP,
    WOLF,
    MADPONY
};

struct enemy_info {
    char name[8];
    BYTE hp;
    BYTE gold;
    BYTE exp;
    BYTE damage;
    BYTE hits;
    BYTE hit_chance;
    BYTE status;
    BYTE crit_chance;
    BYTE absorb;
    BYTE evade;
    BYTE mdef;
    BYTE morale;
    BYTE magic;
    BYTE spatk;
    BYTE family;
    BYTE weakness;
    BYTE resists;
};

extern const struct enemy_info enemy_db[128];
#endif