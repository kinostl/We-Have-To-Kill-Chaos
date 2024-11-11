#ifndef FF_HERO_DATA
#define FF_HERO_DATA
#include "armor_data.h"
#include "entity_data.h"
#include "weapon_data.h"
#include <asm/types.h>
#include <gbs_types.h>

typedef struct {
  char name[7];
  BYTE ap;

  BYTE job;

  entity_data ext;

  weapon_data weapon;

  armor_data body_armor;
  armor_data helmet;
  armor_data grieves;
  armor_data gloves;

  BYTE idx;

  actor_t * actor;
} hero_data;

#endif