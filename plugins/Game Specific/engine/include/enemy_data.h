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

void setup_encounter_table(BYTE encounter_table_id,
                           struct enemy_info encounter_table[4]) OLDCALL BANKED;
#endif