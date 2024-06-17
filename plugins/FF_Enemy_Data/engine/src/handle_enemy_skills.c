#pragma bank 255

#include "data/game_globals.h"
#include "math.h"
#include "vm.h"
#include <asm/types.h>
#include <stdint.h>

#define GET_GLOBAL_VAL(X) *(int16_t *)VM_REF_TO_PTR(X)
#define GET_GLOBAL_PTR(X) (int16_t *)VM_REF_TO_PTR(X)

enum { GOBLIN_PUNCH, HOWL };

// only 129 enemies in FF1
//
// Maybe I should have this be a Family based thing.
// Bosses get up to 12
// Max seems to be 12
// Most enemies look like they have 4
enum { IMP, GRIMP, WOLF, GRWOLF };
const int8_t enemy_skills[4][5] = {[IMP] = {GOBLIN_PUNCH},
                                   [GRIMP] = {GOBLIN_PUNCH},
                                   [WOLF] = {HOWL},
                                   [GRWOLF] = {HOWL}};

/*
Effect: An attack thats more powerful if you're close in level to the target

Normal Attack
* 0.75
* 8
* Small Max HP / Big Max HP

Short name: GobPun
*/
static void goblinPunch(SCRIPT_CTX *THIS) {
  int16_t *attacker_damage = GET_GLOBAL_PTR(VAR_ATTACKER_DAMAGE);

  const int16_t attacker_max_hp = GET_GLOBAL_VAL(VAR_ATTACKER_MAX_HP);
  const int16_t defender_max_hp = GET_GLOBAL_VAL(VAR_DEFENDER_MAX_HP);

  *attacker_damage -= DIV_4(*attacker_damage);

  const int16_t distance = DISTANCE(attacker_max_hp, defender_max_hp);
  const int16_t modifier = 8 - CLAMP(distance, 0, 7);

  *attacker_damage *= modifier;
}

static void howl(SCRIPT_CTX *THIS) { THIS; }

void handleChooseEnemySkill(SCRIPT_CTX *THIS) OLDCALL BANKED {
  const int16_t attacker_type = GET_GLOBAL_VAL(VAR_ATTACKER_TYPE);
  const int16_t skill_idx = GET_GLOBAL_VAL(VAR_ATTACKER_SKILL_IDX);
  int16_t *skill_id = GET_GLOBAL_PTR(VAR_ATTACKER_SKILL);

  *skill_id = enemy_skills[attacker_type][skill_idx] + 1;
}

void handleEnemySkills(SCRIPT_CTX *THIS) OLDCALL BANKED {
  const int16_t skill_id = GET_GLOBAL_VAL(VAR_ATTACKER_SKILL);
  switch (skill_id - 1) {
  case GOBLIN_PUNCH:
    goblinPunch(THIS);
    break;
  case HOWL:
    howl(THIS);
    break;
  }
}