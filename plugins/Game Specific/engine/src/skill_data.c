#include "enums.h"
#include <bankdata.h>
#pragma bank 255
#include "skill_data.h"
#include <gb/gb.h>

#define db_row(id, name, cost) [id] = {id, name, cost}

const skill_data skill_db[] = {
    db_row(FIGHT, "Fight", 1),
    db_row(GUARD, "Guard", -1),
    db_row(COVER, "Cover", 1),
    db_row(LUSTER, "Luster", 2),
    db_row(BLADE_BLITZ, "Bladia", 3),
    db_row(GOBLIN_PUNCH, "Impunch", 0),
    db_row(HOWL, "Howl", 0),
    db_row(THRASH, "Thrash", 0),
    db_row(FIRE, "Fire", 3), //Fire 2 costs 2, Fire 3 Costs 1. Same for other magics.
    db_row(ICE, "Ice", 0),
    db_row(HARM, "Harm", 0),
    db_row(HEAL, "Heal", 0),
    db_row(BLANK, "", 0),
    db_row(STUN, "Stun", 0),
    db_row(WEAK, "Weak", 0),
    db_row(SNEAK, "Sneak", 0),
    db_row(FOCUS, "Focus", -2),
    db_row(WRECK, "Wreck", 0),
    db_row(PIERCE, "Pierce", 0),
    db_row(LOAD, "Load", 0),
};

#undef db_row

BANKREF(FF_SKILLS)