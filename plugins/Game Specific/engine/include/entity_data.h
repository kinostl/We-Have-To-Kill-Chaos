#ifndef FF_ENTITY_DATA
#define FF_ENTITY_DATA
#include <asm/types.h>

typedef struct {
  // shared data
  BYTE slot_id;
  BYTE hp;
  BOOLEAN alive;
  // enemy only data
  BYTE skill_idx;
  BYTE x;
  BYTE y;
  BYTE w;
  BYTE h;
  // player only data
  BYTE ap;
  // static data
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
  BYTE skills[4];
  BYTE skill_costs[4];
  char name[8];
} entity_data;

#endif