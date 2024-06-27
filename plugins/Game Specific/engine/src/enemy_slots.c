#pragma bank 255
#include "data/max_global_vars.h"
#include "enemy_data.h"
#include "math.h"
#include "rand.h" // IWYU pragma: keep
#include "vm.h"
#include <gb/crash_handler.h>

WORD end_of_globals = MAX_GLOBAL_VARS;

void *extra_reserve(SCRIPT_CTX *THIS, WORD size) OLDCALL BANKED {
  void *end_of = VM_REF_TO_PTR(end_of_globals + 1);
  end_of_globals = end_of_globals + DIV_16(size);

  if (end_of_globals > 512) {
    __HandleCrash();
  }

  return end_of;
}

void extra_free(SCRIPT_CTX *THIS, WORD size) OLDCALL BANKED {
  THIS;
  end_of_globals = end_of_globals - DIV_16(size);

  if (end_of_globals < MAX_GLOBAL_VARS) {
    end_of_globals = MAX_GLOBAL_VARS;
  }
}

// All FF1 backgrounds have 2 small & 2 large enemies in them
// Enemies are grouped appropriately for this

/*
I can't find the real encounter values so using the attack slot logic is
probably fine.

    50% Slot 1
    25% Slot 2
    12.5% Slot 3
    12.5% Slot 4
*/

static WORD get_small_enemy_idx(void) {
  const BYTE enemy_roll = rand() % 6;
  switch (enemy_roll) {
  case 0:
  case 1:
  case 2:
  case 3:
    return 0;
  case 4:
  case 5:
    return 1;
  default:
    return 0;
  }
}

static WORD get_large_enemy_idx(void) {
  const BYTE enemy_roll = rand() % 2;
  switch (enemy_roll) {
  case 0:
    return 2;
  case 1:
    return 3;
  default:
    return 2;
  }
}

void setupEnemySlots(SCRIPT_CTX *THIS) OLDCALL BANKED {
  struct enemy_info *enemy_slots =
      extra_reserve(THIS, sizeof(struct enemy_info) * 6);

  struct enemy_info encounter_table[4];
  setup_encounter_table(0, encounter_table);
  // Default to -1
  enemy_slots[0].type = -1;
  enemy_slots[1].type = -1;
  enemy_slots[2].type = -1;
  enemy_slots[3].type = -1;
  enemy_slots[4].type = -1;
  enemy_slots[5].type = -1;

  BYTE large_enemy_count = rand() % 2;
  BYTE small_enemy_count;

  switch (large_enemy_count) {
  case 0:
    small_enemy_count = rand() % 2;
    break;
  case 1:
    small_enemy_count = rand() % 6;
    break;
  default:
    small_enemy_count = 0;
    break;
  }

  WORD idx;
  for(BYTE i=0;i<large_enemy_count;i++){
    idx = get_large_enemy_idx();
    enemy_slots[i] = encounter_table[idx];
  }

  for(BYTE i=0;i<small_enemy_count;i++){
    idx = get_small_enemy_idx();
    enemy_slots[i] = encounter_table[idx];
  }

}

void finishBattle(SCRIPT_CTX *THIS) OLDCALL BANKED {
  extra_free(THIS, sizeof(struct enemy_info) * 6);
}