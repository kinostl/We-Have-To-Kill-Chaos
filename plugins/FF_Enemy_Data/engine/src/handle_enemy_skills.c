/**
Goblin Punch
Usable by:
- Great Imps (Often)
- Imps (Rarely)


I like GobPun
 */

#pragma bank 255

#include <asm/types.h>
#include <stdint.h>
#include "data/game_globals.h"
#include "handle_enemy_skills.h"
#include "math.h"

/*
Effect: An attack thats more powerful if you're close in level to the target

Normal Attack
* 0.75
* 8
* Small Max HP / Big Max HP

Short name: GobPun
*/
void goblinPunch(SCRIPT_CTX *THIS) OLDCALL BANKED {
  int16_t * attacker_damage = GET_GLOBAL_PTR(VAR_ATTACKER_DAMAGE);

  const int16_t attacker_max_hp = GET_GLOBAL_VAL(VAR_ATTACKER_MAX_HP);
  const int16_t defender_max_hp = GET_GLOBAL_VAL(VAR_DEFENDER_MAX_HP);

  *attacker_damage -= DIV_4(*attacker_damage);

  const int16_t distance = DISTANCE(attacker_max_hp, defender_max_hp);
  const int16_t modifier = 8 - CLAMP(distance, 0, 7);

  *attacker_damage *= modifier;
}

void howl(SCRIPT_CTX *THIS) OLDCALL BANKED {
  THIS;
}

void handleChooseEnemySkill(SCRIPT_CTX *THIS) OLDCALL BANKED {
  const int16_t attacker_type = GET_GLOBAL_VAL(VAR_ATTACKER_TYPE);
  const int16_t skill_idx = GET_GLOBAL_VAL(VAR_ATTACKER_SKILL_IDX);
  int16_t *skill_id = GET_GLOBAL_PTR(VAR_ATTACKER_SKILL);

  *skill_id = enemy_skills[attacker_type][skill_idx];
}

void handleEnemySkills(SCRIPT_CTX *THIS) OLDCALL BANKED {
  const int16_t skill_id = GET_GLOBAL_VAL(VAR_ATTACKER_SKILL);
  switch (skill_id) {
  case GOBLIN_PUNCH:
    goblinPunch(THIS);
    break;
  case HOWL:
    howl(THIS);
    break;
  }
}