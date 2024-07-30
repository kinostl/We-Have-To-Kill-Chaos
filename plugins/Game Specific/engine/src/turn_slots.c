#include <entity_data.h>
#include <gb/gb.h>
#include <asm/types.h>
#include <data/game_globals.h>
#include <gb/crash_handler.h>
#include <string.h>
#include "turn_slots.h"
#include "vm.h"

#pragma bank 255

struct entity_data *turn_slots = (struct entity_data *)&VM_GLOBAL(MAX_GLOBAL_VARS + 1);

void load_attacker(SCRIPT_CTX * THIS) OLDCALL BANKED {
  THIS;
  BYTE slot_idx = VM_GLOBAL(VAR_ATTACKER_ID);
  struct entity_data *slot = &turn_slots[slot_idx];
  switch (slot_idx) {
  case 0:
  case 1:
  case 2:
  case 3:
    load_player_atk(slot);
    break;
  case 4:
  case 5:
  case 6:
  case 7:
  case 8:
  case 9:
    load_enemy_atk(slot);
    break;
  default:
    __HandleCrash();
    break;
  }
}

void load_defender(SCRIPT_CTX * THIS) OLDCALL BANKED {
  THIS;
  BYTE slot_idx = VM_GLOBAL(VAR_DEFENDER_ID);
  struct entity_data *slot = &turn_slots[slot_idx];
  switch (slot_idx) {
  case 0:
  case 1:
  case 2:
  case 3:
    load_player_def(slot);
    break;
  case 4:
  case 5:
  case 6:
  case 7:
  case 8:
  case 9:
    load_enemy_def(slot);
    break;
  default:
    __HandleCrash();
    break;
  }
}

void load_name(struct entity_data * entity) OLDCALL BANKED{
  UWORD *name = &VM_GLOBAL(VAR_1_C);
  UWORD name_l = strlen(entity->name);
  for (int i = 0; i < name_l; i++) {
    name[i] = entity->name[i];
  }
  for (int i = name_l; i < 8; i++) {
    name[i] = 127;
  }
}

void load_player_atk(struct entity_data *player) OLDCALL BANKED {
  VM_GLOBAL(VAR_ATTACKER_DAMAGE) = player->damage;
  VM_GLOBAL(VAR_ATTACKER_AP) = player->ap;
  VM_GLOBAL(VAR_ATTACKER_HP) = player->hp;
  VM_GLOBAL(VAR_ATTACKER_CRIT_CHANCE) = player->crit_chance;
  VM_GLOBAL(VAR_ATTACKER_CRIT_DAMAGE) = player->damage;
  VM_GLOBAL(VAR_ATTACKER_HIT_CHANCE) = player->hit_chance;
  VM_GLOBAL(VAR_ATTACKER_ID) = player->slot_id;
  VM_GLOBAL(VAR_ATTACKER_MISSED) = FALSE;
  VM_GLOBAL(VAR_ATTACKER_SKILL) = 0;
  VM_GLOBAL(VAR_ATTACKER_SKILL_IDX) = 0;
  VM_GLOBAL(VAR_ATTACKER_TYPE) = player->type;
}

void load_player_def(struct entity_data *player) OLDCALL BANKED {
  VM_GLOBAL(VAR_DEFENDER_ENDING_HP) = player->hp;
  VM_GLOBAL(VAR_DEFENDER_ID) = player->slot_id;
  VM_GLOBAL(VAR_DEFENDER_STARTING_HP) = player->hp;
}

void load_enemy_atk(struct entity_data *enemy) OLDCALL BANKED {
  VM_GLOBAL(VAR_ATTACKER_DAMAGE) = enemy->damage;
  VM_GLOBAL(VAR_ATTACKER_AP) = 0;
  VM_GLOBAL(VAR_ATTACKER_CRIT_CHANCE) = enemy->crit_chance;
  VM_GLOBAL(VAR_ATTACKER_CRIT_DAMAGE) = enemy->damage;
  VM_GLOBAL(VAR_ATTACKER_HIT_CHANCE) = enemy->hit_chance;
  VM_GLOBAL(VAR_ATTACKER_ID) = enemy->slot_id;
  VM_GLOBAL(VAR_ATTACKER_MISSED) = FALSE;
  VM_GLOBAL(VAR_ATTACKER_SKILL) = 0;
  VM_GLOBAL(VAR_ATTACKER_SKILL_IDX) = enemy->skill_idx;
  VM_GLOBAL(VAR_ATTACKER_TYPE) = enemy->type;
}

void load_enemy_def(struct entity_data *enemy) OLDCALL BANKED {
  VM_GLOBAL(VAR_DEFENDER_ENDING_HP) = enemy->hp;
  VM_GLOBAL(VAR_DEFENDER_ID) = 0;
  VM_GLOBAL(VAR_DEFENDER_STARTING_HP) = enemy->hp;
}