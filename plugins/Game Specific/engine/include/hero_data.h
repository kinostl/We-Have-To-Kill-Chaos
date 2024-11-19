#ifndef FF_HERO_DATA
#define FF_HERO_DATA
#include "armor_data.h"
#include "entity_data.h"
#include "weapon_data.h"
#include "class_data.h"
#include "position_data.h"
#include <asm/types.h>
#include <gbs_types.h>

typedef struct {
  char name[7];
  BYTE ap;

  JOB_ID job;

  entity_data ext;

  weapon_data weapon;

  armor_data body_armor;
  armor_data helmet;
  armor_data grieves;
  armor_data gloves;

  actor_t * actor;
  ff_position_t pos;

  BYTE strength;
  BYTE agility;
  BYTE intel;
  BYTE vitality;
  BYTE luck;

} hero_data;

extern const hero_data hero_db[];

BANKREF_EXTERN(FF_HERO_DATA)

inline void load_hero(hero_data *hero, JOB hero_id) {
  MemcpyBanked(hero, &hero_db[hero_id], sizeof(hero_data),
               BANK(FF_HERO_DATA));
}

#endif