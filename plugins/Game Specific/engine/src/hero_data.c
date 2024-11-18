#include "hero_data.h"
#include "enums.h"
#include <bankdata.h>
#include <gb/gb.h>

#pragma bank 255
BANKREF(FF_HERO_DATA)

const hero_data hero_db[] = {
    [FIGHTER] = {
                 .strength = 20,
                 .agility  = 5,
                 .intel    = 1,
                 .vitality = 10,
                 .luck     = 5,
                 .job      = FIGHTER,
                 .ext      = {
                 .max_hp     = 35,
                 .hit_chance = 10,
                 .mdef       = 15,
                 .skills     = {
                FIGHT,
                SHIELD_SKILL,
                RUNE_SWORD_SKILL,
                LUSTER,
            },
        },
                 },
    [THIEF] = {
                 .strength = 5,
                 .agility  = 10,
                 .intel    = 5,
                 .vitality = 5,
                 .luck     = 15,
                 .ext      = {
                 .max_hp     = 30,
                 .hit_chance = 5,
                 .mdef       = 15,
                 .skills     = {
                FIGHT,
                STEAL,
                WEAK,
                SNEAK,
            },
        },
                 },
    [MONK] = {
                 .strength = 5,
                 .agility  = 5,
                 .intel    = 5,
                 .vitality = 20,
                 .luck     = 5,
                 .ext      = {
                 .max_hp     = 33,
                 .hit_chance = 5,
                 .mdef       = 10,
                 .skills     = {
                FIGHT,
                FOCUS,
                WRECK,
                PIERCE,
            },
        },
                 },
    [RED_MAGE] = {
                 .strength = 10,
                 .agility  = 10,
                 .intel    = 10,
                 .vitality = 5,
                 .luck     = 5,
                 .ext      = {
                 .max_hp     = 30,
                 .hit_chance = 7,
                 .mdef       = 20,
                 .skills     = {
                FIGHT,
                LOAD,
                BLANK,
                BLANK,
            },
        },
                 },
    [WHITE_MAGE] = {
                 .strength = 5,
                 .agility  = 5,
                 .intel    = 15,
                 .vitality = 10,
                 .luck     = 5,
                 .ext      = {
                 .max_hp     = 28,
                 .hit_chance = 5,
                 .mdef       = 20,
                 .skills     = {
                FIGHT,
                BLANK,
                BLANK,
                BLANK,
            },
        },
                 },
    [BLACK_MAGE] = {
                 .strength = 1,
                 .agility  = 10,
                 .intel    = 20,
                 .vitality = 1,
                 .luck     = 10,
                 .ext      = {
                 .max_hp     = 25,
                 .hit_chance = 5,
                 .mdef       = 20,
                 .skills     = {
                FIGHT,
                BLANK,
                BLANK,
                BLANK,
            },
        },
                 },
    [BLUE_MAGE] = {
                 .strength = 5,
                 .agility  = 10,
                 .intel    = 5,
                 .vitality = 10,
                 .luck     = 10,
                 .ext      = {
                 .max_hp     = 30,
                 .hit_chance = 7,
                 .mdef       = 20,
                 .skills     = {
                FIGHT,
                BLANK,
                BLANK,
                BLANK,
            },
        },
                 },
};