#ifndef FF_ENTITY_DATA
#define FF_ENTITY_DATA
#include "enums.h"
#include "skill_data.h"
#include <asm/types.h>

typedef struct {
  BYTE hp;
  BOOLEAN alive;
  BYTE max_hp;
  BYTE type;
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
  ENEMY_FAMILY family;
  ENEMY_TYPE weakness;
  BYTE resists;
  const skill_data * skills[4];
} entity_data;

#endif