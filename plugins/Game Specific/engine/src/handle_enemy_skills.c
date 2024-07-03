#include "data/game_globals.h"
#include "entity_data.h"
#include "enemy_data.h"
#include "math.h"
#include "rand.h" // IWYU pragma: keep
#include "turn_slots.h"
#include "vm.h"
#include <asm/types.h>

#pragma bank 255

enum { FIGHT, GOBLIN_PUNCH, HOWL, THRASH };

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

void set_skill_id(UWORD a, UWORD b, UWORD c, UWORD d) OLDCALL BANKED {
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

  switch (entity_data->skill_idx) {
  case 1:
    *skill_id = a;
    break;
  case 2:
    *skill_id = b;
    break;
  case 3:
    *skill_id = c;
    break;
  case 4:
    *skill_id = d;
    break;
  default:
    *skill_id = FIGHT;
    break;
  }
}

void chooseEnemySkill(SCRIPT_CTX *THIS) OLDCALL BANKED {
  THIS;
  BYTE slot_id = VM_GLOBAL(VAR_TURN_ORDER_CURRENT_ACTO);
  WORD attacker_type = turn_slots[slot_id].type;
  VM_GLOBAL(VAR_ATTACKER_ID) = VM_GLOBAL(VAR_TURN_ORDER_CURRENT_ACTO);
  VM_GLOBAL(VAR_DEFENDER_ID) = 1;


  switch (attacker_type) {
  case IMP:
    set_skill_id(GOBLIN_PUNCH, FIGHT, FIGHT, FIGHT);
    break;
  case GrIMP:
    set_skill_id(GOBLIN_PUNCH, FIGHT, GOBLIN_PUNCH, FIGHT);
    break;
  case WOLF:
    set_skill_id(HOWL, FIGHT, FIGHT, FIGHT);
    break;
  case MADPONY:
    set_skill_id(THRASH, FIGHT, FIGHT, FIGHT);
    break;
  default:
    set_skill_id(FIGHT, FIGHT, FIGHT, FIGHT);
    break;
  }
}