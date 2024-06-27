#pragma bank 255
#include "data/game_globals.h"
#include "data/max_global_vars.h"
#include "enemy_data.h"
#include "math.h"
#include "rand.h"
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

void setupEnemySlots(SCRIPT_CTX *THIS) OLDCALL BANKED {
  struct enemy_info *enemy_slots =
      extra_reserve(THIS, sizeof(struct enemy_info) * 6);

  // Default to -1
  enemy_slots[0].type = -1;
  enemy_slots[1].type = -1;
  enemy_slots[2].type = -1;
  enemy_slots[3].type = -1;
  enemy_slots[4].type = -1;
  enemy_slots[5].type = -1;

  switch (rand() % 8) {
  case 0:
  case 1:
  case 2:
  case 3:
    // enemy type 1 (small)
    break;
  case 4:
  case 5:
    // enemy type 2 (small)
    break;
  case 6:
    // enemy type 3 (large)
    break;
  case 7:
    // enemy type 4 (large)
    break;
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
}

void handleEnemySlots(SCRIPT_CTX *THIS) OLDCALL BANKED {
  // I think I calculate things in the plugin that has the enemy list
  // Then push the enemy IDs into the stack
  // And then unload them here
  int idx = 0;
  int i;

  for (i = 0; i < VM_GLOBAL(VAR_S1_LARGE_ENEMIES); i++) {
    enemy_slots[idx] = enemy_db[MADPONY];
    idx++;
  }

  for (i = 0; i < VM_GLOBAL(VAR_S1_SMALL_ENEMIES); i++) {
    enemy_slots[idx] = enemy_db[IMP];
    idx++;
  }
}

void finishBattle(SCRIPT_CTX *THIS) OLDCALL BANKED {
  extra_free(THIS, sizeof(struct enemy_info) * 6);
}