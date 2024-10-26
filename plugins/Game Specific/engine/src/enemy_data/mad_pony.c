#include <asm/types.h>
#include <string.h>
#pragma bank 255
#include <gb/gb.h>
#include "enemy_data.h"
#include "entity_data.h"
#include "enemy_data/mad_pony.h"

void set_to_mad_pony(entity_data *entity) OLDCALL BANKED{
  strcpy(entity->name, "MADPONY");
  entity->max_hp = 64;
  entity->gold = 15;
  entity->exp = 63;
  entity->damage = 10;
  entity->hits = 2;
  entity->hit_chance = 92;
  entity->status = -1;
  entity->crit_chance = 1;
  entity->absorb = 2;
  entity->evade = 11;
  entity->mdef = 20;
  entity->morale = 13;
  entity->magic = 0;
  entity->spatk = 0;
  entity->family = NONE;
  entity->type = MADPONY;
  entity->weakness = -1;
  entity->resists = -1;
  entity->skills[0] = THRASH;
  entity->skills[1] = FIGHT;
  entity->skills[2] = FIGHT;
  entity->skills[3] = FIGHT;
}