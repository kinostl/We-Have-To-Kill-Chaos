#ifndef FF_ENTITY_DATA
#define FF_ENTITY_DATA
#include "enums.h"
#include "position_data.h"
#include <asm/types.h>

typedef struct {
  UBYTE idx;
  UBYTE hp;
  UBYTE max_hp;
  UBYTE type;
  UBYTE gold;
  UBYTE exp;
  UBYTE damage;
  UBYTE hits;
  UBYTE hit_chance;
  STATUS_EFFECT status;
  UBYTE crit_chance;
  UBYTE absorb;
  UBYTE evade;
  UBYTE mdef;
  UBYTE morale;
  UBYTE spell_chance;
  UBYTE skill_chance;
  ENEMY_FAMILY family;
  ENEMY_TYPE weakness;
  UBYTE resists;
  BATTLE_SKILL skills[4];
  ff_position_t pos;
} entity_data;

#endif