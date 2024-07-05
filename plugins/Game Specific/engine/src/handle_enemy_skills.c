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
  struct entity_data * attacker = &turn_slots[VM_GLOBAL(VAR_ATTACKER_ID)];
  struct entity_data * defender = &turn_slots[VM_GLOBAL(VAR_DEFENDER_ID)];
  WORD *attacker_damage = VM_REF_TO_PTR(VAR_ATTACKER_DAMAGE);

  WORD distance = DISTANCE(attacker->max_hp, defender->max_hp);
  WORD modifier = 8 - CLAMP(distance, 0, 7);

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