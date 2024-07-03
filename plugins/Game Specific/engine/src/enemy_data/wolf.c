#include <asm/types.h>
#include <string.h>
#include "enemy_data.h"
#include "enemy_data/wolf.h"
#include "entity_data.h"
#include <gb/gb.h>

#pragma bank 255

void set_to_wolf(struct entity_data *entity) OLDCALL BANKED{
  strcpy(entity->name, "WOLF");
  entity->max_hp = 20;
  entity->gold = 6;
  entity->exp = 24;
  entity->damage = 8;
  entity->hits = 1;
  entity->hit_chance = 86;
  entity->status = -1;
  entity->crit_chance = 1;
  entity->absorb = 0;
  entity->evade = 18;
  entity->mdef = 14;
  entity->morale = 13;
  entity->magic = 0;
  entity->spatk = 0;
  entity->family = NONE;
  entity->type = WOLF;
  entity->weakness = -1;
  entity->resists = -1;
}