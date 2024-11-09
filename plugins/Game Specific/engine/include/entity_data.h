#ifndef FF_ENTITY_DATA
#define FF_ENTITY_DATA
#include <asm/types.h>

typedef struct {
  // shared data

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
  BYTE family;
  BYTE weakness;
  BYTE resists;
  BYTE skills[4];
  BYTE skill_costs[4];
} entity_data;

#endif