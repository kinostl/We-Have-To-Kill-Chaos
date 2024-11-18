#ifndef FF_ENEMY_DATA
#define FF_ENEMY_DATA

#include "entity_data.h"
#include "enums.h"
#include <bankdata.h>
#include <gb/gb.h>
#include "position_data.h"

typedef struct {
  BYTE skill_idx;
  char name[8];

  entity_data ext;
  ff_position_t pos;

} enemy_data;

extern const enemy_data enemy_db[];

BANKREF_EXTERN(FF_ENEMY_DATA)

inline void load_enemy(enemy_data *enemy, ENEMY_TYPE enemy_id) {
  MemcpyBanked(enemy, &enemy_db[enemy_id], sizeof(enemy_data),
               BANK(FF_ENEMY_DATA));
}

#endif