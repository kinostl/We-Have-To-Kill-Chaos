#pragma bank 255
#include <gb/gb.h>
#include "turn_slots.h"
#include "enemy_slots.h"
#include "player_slots.h"
#include "vm.h"
#include <asm/types.h>
#include <data/game_globals.h>
#include <gb/crash_handler.h>
#include <string.h>

BANKREF(ff_turn_slots)

struct turn_slot *turn_slots;
struct player_slot *player_slots;
struct enemy_slot *enemy_slots;

void valloc_turn_slots(void) OLDCALL BANKED {
  turn_slots = valloc(sizeof(struct turn_slot) * 10);
  player_slots = valloc(sizeof(struct player_slot) * 4);
  enemy_slots = valloc(sizeof(struct enemy_slot) * 6);
  struct turn_slot new_slots[10] = {
    {PLAYER, &player_slots[0]},
    {PLAYER, &player_slots[1]},
    {PLAYER, &player_slots[2]},
    {PLAYER, &player_slots[3]},
    {ENEMY, &enemy_slots[0]},
    {ENEMY, &enemy_slots[1]},
    {ENEMY, &enemy_slots[2]},
    {ENEMY, &enemy_slots[3]},
    {ENEMY, &enemy_slots[4]},
    {ENEMY, &enemy_slots[5]}
  };

  memcpy(turn_slots, new_slots, sizeof(new_slots));
}

void load_attacker(BYTE slot_idx) OLDCALL BANKED {
  struct turn_slot *slot = &turn_slots[slot_idx];
  switch (slot->tag) {
  case PLAYER:
    load_player_atk(slot->entity);
    break;
  case ENEMY:
    load_enemy_atk(slot->entity);
    break;
  default:
    __HandleCrash();
    break;
  }
}

void load_defender(BYTE slot_idx) OLDCALL BANKED {
  struct turn_slot *slot = &turn_slots[slot_idx];
  switch (slot->tag) {
  case PLAYER:
    load_player_def(slot->entity);
    break;
  case ENEMY:
    load_enemy_def(slot->entity);
    break;
  default:
    __HandleCrash();
    break;
  }
}

void load_player_atk(struct player_slot *player) OLDCALL BANKED {
  VM_GLOBAL(VAR_ATTACKER_DAMAGE) = player->info.damage;
  VM_GLOBAL(VAR_ATTACKER_AP) = player->ap;
  VM_GLOBAL(VAR_ATTACKER_CRIT_CHANCE) = player->info.crit_chance;
  VM_GLOBAL(VAR_ATTACKER_CRIT_DAMAGE) = player->info.damage;
  VM_GLOBAL(VAR_ATTACKER_HIT_CHANCE) = player->info.hit_chance;
  VM_GLOBAL(VAR_ATTACKER_ID) = player->slot_id;
  VM_GLOBAL(VAR_ATTACKER_MAX_HP) = player->info.max_hp;
  VM_GLOBAL(VAR_ATTACKER_MISSED) = FALSE;
  VM_GLOBAL(VAR_ATTACKER_SKILL) = 0;
  VM_GLOBAL(VAR_ATTACKER_SKILL_IDX) = 0;
  VM_GLOBAL(VAR_ATTACKER_TYPE) = player->info.type;
}
void load_player_def(struct player_slot *player) OLDCALL BANKED {
  VM_GLOBAL(VAR_DEFENDER_ENDING_HP) = player->hp;
  VM_GLOBAL(VAR_DEFENDER_ID) = player->slot_id;
  VM_GLOBAL(VAR_DEFENDER_MAX_HP) = player->info.max_hp;
  VM_GLOBAL(VAR_DEFENDER_STARTING_HP) = player->hp;
}

void load_enemy_atk(struct enemy_slot *enemy) OLDCALL BANKED {
  VM_GLOBAL(VAR_ATTACKER_DAMAGE) = enemy->info.damage;
  VM_GLOBAL(VAR_ATTACKER_AP) = 0;
  VM_GLOBAL(VAR_ATTACKER_CRIT_CHANCE) = enemy->info.crit_chance;
  VM_GLOBAL(VAR_ATTACKER_CRIT_DAMAGE) = enemy->info.damage;
  VM_GLOBAL(VAR_ATTACKER_HIT_CHANCE) = enemy->info.hit_chance;
  VM_GLOBAL(VAR_ATTACKER_ID) = enemy->slot_id;
  VM_GLOBAL(VAR_ATTACKER_MAX_HP) = enemy->info.max_hp;
  VM_GLOBAL(VAR_ATTACKER_MISSED) = FALSE;
  VM_GLOBAL(VAR_ATTACKER_SKILL) = 0;
  VM_GLOBAL(VAR_ATTACKER_SKILL_IDX) = enemy->skill_idx;
  VM_GLOBAL(VAR_ATTACKER_TYPE) = enemy->info.type;
}

void load_enemy_def(struct enemy_slot *enemy) OLDCALL BANKED {
  VM_GLOBAL(VAR_DEFENDER_ENDING_HP) = enemy->hp;
  VM_GLOBAL(VAR_DEFENDER_ID) = enemy->slot_id;
  VM_GLOBAL(VAR_DEFENDER_MAX_HP) = enemy->info.max_hp;
  VM_GLOBAL(VAR_DEFENDER_STARTING_HP) = enemy->hp;
}