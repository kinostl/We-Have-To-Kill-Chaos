#ifndef FF_ENTITY_DATA
#define FF_ENTITY_DATA
#include "enums.h"
#include <asm/types.h>

typedef struct {
  BYTE idx;
  BYTE hp;
  BYTE max_hp;
  BYTE type;
  BYTE gold;
  BYTE exp;
  BYTE damage;
  BYTE hits;
  BYTE hit_chance;
  STATUS_EFFECT status;
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
  BATTLE_SKILL skills[4];
} entity_data;

#endif