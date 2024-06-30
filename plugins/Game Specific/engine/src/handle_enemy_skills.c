#include "data/game_globals.h"
#include "enemy_data.h"
#include "enemy_slots.h"
#include "math.h"
#include "rand.h"
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
static void goblinPunch(SCRIPT_CTX *THIS) {
  BYTE attacker_id = VM_GLOBAL(VAR_ATTACKER_ID);
  if (attacker_id >= 5) { // Enemy Slots start at 5;
    VM_GLOBAL(VAR_ATTACKER_MAX_HP) = enemy_slots[attacker_id - 5].info.max_hp;
  }

  BYTE defender_id = VM_GLOBAL(VAR_ATTACKER_ID);
  if (defender_id >= 5) { // Enemy Slots start at 5;
    VM_GLOBAL(VAR_DEFENDER_MAX_HP) = enemy_slots[defender_id - 5].info.max_hp;
  }

  const WORD attacker_max_hp = VM_GLOBAL(VAR_ATTACKER_MAX_HP);
  const WORD defender_max_hp = VM_GLOBAL(VAR_DEFENDER_MAX_HP);
  const WORD distance = DISTANCE(attacker_max_hp, defender_max_hp);
  const WORD modifier = 8 - CLAMP(distance, 0, 7);

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

  const BYTE slot_id = VM_GLOBAL(VAR_ATTACKER_ID) - 5;
  const WORD skill_idx = VM_GLOBAL(VAR_ATTACKER_SKILL_IDX);
  struct enemy_slot *enemy_slot = &enemy_slots[slot_id];
  enemy_slot->skill_idx++;
  if (enemy_slot->skill_idx > 4) {
    enemy_slot->skill_idx = 1;
  }

  switch (skill_idx) {
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
  const BYTE slot_id = VM_GLOBAL(VAR_TURN_ORDER_CURRENT_ACTO) - 5;
  const WORD attacker_type = enemy_slots[slot_id].info.type;
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