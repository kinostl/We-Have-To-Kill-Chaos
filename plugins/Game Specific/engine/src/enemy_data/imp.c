#include <string.h>
#include <gb/gb.h>
#include "enemy_data.h"
#include "entity_data.h"
#include "enemy_data/imp.h"

#pragma bank 255

void set_to_imp(struct entity_data *entity) OLDCALL BANKED{
  strcpy(entity->name, "IMP");
  entity->max_hp = 8;
  entity->gold = 6;
  entity->exp = 6;
  entity->damage = 4;
  entity->hits = 1;
  entity->hit_chance = 85;
  entity->status = -1;
  entity->crit_chance = 1;
  entity->absorb = 4;
  entity->evade = 3;
  entity->mdef = 8;
  entity->morale = 13;
  entity->magic = 0;
  entity->spatk = 0;
  entity->family = GIANT;
  entity->type = IMP;
  entity->weakness = -1;
  entity->resists = -1;
  entity->skills[0] = GOBLIN_PUNCH;
  entity->skills[1] = FIGHT;
  entity->skills[2] = FIGHT;
  entity->skills[3] = FIGHT;
}