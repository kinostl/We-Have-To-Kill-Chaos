#include "data/game_globals.h"
#include "entity_data.h"
#include "enemy_data.h"
#include "math.h"
#include "rand.h" // IWYU pragma: keep
#include "turn_slots.h"
#include "vm.h"
#include <asm/types.h>

#pragma bank 255

/*
Effect: An attack thats more powerful if you're close in level to the target

Normal Attack
* 0.75
* 8
* Small Max HP / Big Max HP

Short name: GobPun
*/
void goblinPunch(SCRIPT_CTX *THIS) OLDCALL BANKED{
  BYTE attacker_id = VM_GLOBAL(VAR_ATTACKER_ID);
  if (attacker_id >= 5) { // Enemy Slots start at 5;
    VM_GLOBAL(VAR_ATTACKER_MAX_HP) = turn_slots[attacker_id].max_hp;
  }

  BYTE defender_id = VM_GLOBAL(VAR_DEFENDER_ID);
  if (defender_id >= 5) { // Enemy Slots start at 5;
    VM_GLOBAL(VAR_DEFENDER_MAX_HP) = turn_slots[defender_id].max_hp;
  }

  WORD attacker_max_hp = VM_GLOBAL(VAR_ATTACKER_MAX_HP);
  WORD defender_max_hp = VM_GLOBAL(VAR_DEFENDER_MAX_HP);
  WORD distance = DISTANCE(attacker_max_hp, defender_max_hp);
  WORD modifier = 8 - CLAMP(distance, 0, 7);

  WORD *attacker_damage = VM_REF_TO_PTR(VAR_ATTACKER_DAMAGE);
  *attacker_damage -= DIV_4(*attacker_damage);
  *attacker_damage *= modifier;
}

void chooseEnemySkill(SCRIPT_CTX * THIS) OLDCALL BANKED {
  THIS;
  UWORD *skill_id = &VM_GLOBAL(VAR_ATTACKER_SKILL);
  if (rand() % 2 > 0) {
    *skill_id = FIGHT;
    return;
  }

  BYTE slot_id = VM_GLOBAL(VAR_ATTACKER_ID);
  struct entity_data *entity_data = &turn_slots[slot_id];

  entity_data->skill_idx++;
  if (entity_data->skill_idx > 4) {
    entity_data->skill_idx = 1;
  }

  *skill_id = entity_data->skills[entity_data->skill_idx];
}