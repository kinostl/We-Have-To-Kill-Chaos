#include "enums.h"
#include <bankdata.h>
#include <string.h>
#pragma bank 255
#include "skill_data.h"
#include <gb/gb.h>

#define db_row(id, name, cost) [id] = {id, name, cost}

const skill_data skill_db[] = {
    db_row(FIGHT, "Fight", 1),
    db_row(SHIELD_SKILL, "Shield", 1),
    db_row(RUNE_SWORD_SKILL, "Runic", 2),
    db_row(LUSTER, "Luster", 3),
    db_row(GOBLIN_PUNCH, "GobPun", 0),
    db_row(HOWL, "Howl", 0),
    db_row(THRASH, "Thrash", 0),
    db_row(FIRE, "Fire", 0),
    db_row(ICE, "Ice", 0),
    db_row(HARM, "Harm", 0),
    db_row(HEAL, "Heal", 0),
    db_row(BLANK, "", 0),
    db_row(STEAL, "Steal", 0),
    db_row(WEAK, "Weak", 0),
    db_row(SNEAK, "Sneak", 0),
    db_row(FOCUS, "Focus", 0),
    db_row(WRECK, "Wreck", 0),
    db_row(PIERCE, "Pierce", 0),
    db_row(LOAD, "Load", 0),
};

#undef db_row

BANKREF(FF_SKILLS)