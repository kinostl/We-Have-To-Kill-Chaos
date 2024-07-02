#ifndef FF_ENTITY_DATA
#define FF_ENTITY_DATA
#include <asm/types.h>

struct entity_data {
    char name[8];
    BYTE type;
    BYTE max_hp;
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

#endif