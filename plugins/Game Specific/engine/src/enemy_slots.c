#pragma bank 255
#include <gb/gb.h>
#include <asm/types.h>
#include <bankdata.h>
#include <data/game_globals.h>
#include <gbs_types.h>
#include "enemy_slots.h"
#include "data/bg_battle_concept_tileset.h"
#include "data/bg_enemies_plains_1.h"
#include "data/bg_enemies_plains_1_tileset.h"
#include "enemy_data.h"
#include "entity_data.h"
#include "handle_flashing.h"
#include "rand.h" // IWYU pragma: keep
#include "vm.h"


BANKREF(ff_enemy_slots)


// All FF1 backgrounds have 2 small & 2 large enemies in them
// Enemies are grouped appropriately for this

/*
I can't find the real encounter values so using the attack slot logic is
probably fine.

    50% Slot 1
    25% Slot 2
    12.5% Slot 3
    12.5% Slot 4

After testing, this is a 1/4 chance of getting a big guy in a fight and they
tend to be dangerous encounters. Not sure if good or bad.
*/

BYTE get_small_enemy_idx(void) OLDCALL BANKED{
  BYTE enemy_roll = rand() % 6;
  switch (enemy_roll){
  default:
    return 0;
  case 4:
  case 5:
    return 1;
  }
}

BYTE get_enemy_idx(void) OLDCALL BANKED{
  BYTE enemy_roll = rand() % 8;
  switch (enemy_roll) {
  case 0:
    return 2;
  case 1:
    return 3;
  default:
    return get_small_enemy_idx();
  }
}

void setupTileBuffer(UBYTE *buffer, UBYTE w, UBYTE h, UBYTE x, UBYTE y,
                     UBYTE offset, background_t import_bkg) OLDCALL BANKED {

  UBYTE buffer_s = w * h;

  UWORD buffer_offset = 0;
  UWORD bank_offset = 0;

  for (UBYTE i = 0; i < h; i++) {
    buffer_offset = i * w;
    bank_offset = (i + y) * import_bkg.width + x;
    UBYTE *import_ptr = import_bkg.tilemap.ptr;
    import_ptr += bank_offset;

    MemcpyBanked(buffer + buffer_offset, import_ptr, sizeof(UBYTE) * w,
                 import_bkg.tilemap.bank);
  }

  for (int i = 0; i < buffer_s; i++) {
    buffer[i] += offset;
  }
}

void initialize_enemy_slot(struct enemy_slot *slot) OLDCALL BANKED {
  struct entity_data blank;
  slot->hp = 0;
  slot->skill_idx = 0;
  slot->info = blank;
  slot->alive = FALSE;
}

void setupEnemySlots(SCRIPT_CTX *THIS) OLDCALL BANKED {
  THIS;
  struct entity_data encounter_table[4];

  setup_encounter_table(0, encounter_table);
  // Default to null
  initialize_enemy_slot(&enemy_slots[0]);
  initialize_enemy_slot(&enemy_slots[1]);
  initialize_enemy_slot(&enemy_slots[2]);
  initialize_enemy_slot(&enemy_slots[3]);
  initialize_enemy_slot(&enemy_slots[4]);
  initialize_enemy_slot(&enemy_slots[5]);

  // Now load up the enemy VRAM
  // Then draw the tiles manually, knowing that they'll be in order correctly.
  // https://github.com/chrismaltby/gb-studio/blob/9a9696decc30b7970e152919a4a4163d967c5ead/appData/src/gb/src/core/ui.c#L4

  UBYTE start_of_enemy_vram;
  UBYTE tileset_size;
  background_t import_bkg;

  // When you're ready to make this take more than one background
  // Refer to BulkTileSwap plugin in DomainDomain
  // tl;dr
  //  1. event accepts a type:background with key backgroundId (this makes it do
  //  the visuals thing on the ide side)
  //  2. event iterates through backgrounds array from helper finding the
  //  related key
  //  3. event pushes __bank_bg and _bg into stack
  //  4. bank and from are the stack vars now
  MemcpyBanked(&import_bkg, &bg_enemies_plains_1, sizeof(import_bkg),
               BANK(bg_enemies_plains_1));

  MemcpyBanked(&start_of_enemy_vram, &bg_battle_concept_tileset.n_tiles,
               sizeof(UBYTE), BANK(bg_battle_concept_tileset));
  MemcpyBanked(&tileset_size, &bg_enemies_plains_1_tileset.n_tiles,
               sizeof(UBYTE), BANK(bg_enemies_plains_1_tileset));

  SetBankedBkgData(start_of_enemy_vram, tileset_size,
                   bg_enemies_plains_1_tileset.tiles,
                   BANK(bg_enemies_plains_1_tileset));

  UBYTE enemy_buffer[6 * 6];

  // defines because we're going to be repeating this and I don't feel like
  // looping or figuring out if inlines can do js stuff
  // ngl getting this to be a 6*6 buffer instead of a 10*4 is me having a
  // pissing contest with myself

#define place_bg_tiles                                                         \
  setupTileBuffer(enemy_buffer, 5, 4, 0, 0, start_of_enemy_vram, import_bkg);  \
  set_bkg_tiles(1, 1, 5, 4, enemy_buffer);                                     \
  handle_bkg_set_color(1, 1, 1, 5, 4);                                         \
  setupTileBuffer(enemy_buffer, 5, 4, 5, 0, start_of_enemy_vram, import_bkg);  \
  set_bkg_tiles(6, 1, 5, 4, enemy_buffer);                                     \
  handle_bkg_set_color(1, 6, 1, 5, 4)

#define place_sm_enemy_1(x, y, color)                                          \
  setupTileBuffer(enemy_buffer, 5, 4, 0, 4, start_of_enemy_vram, import_bkg);  \
  set_bkg_tiles(x, y, 5, 4, enemy_buffer);                                     \
  handle_bkg_set_color(color, x, y, 5, 4)

#define place_sm_enemy_2(x, y, color)                                          \
  setupTileBuffer(enemy_buffer, 5, 4, 5, 4, start_of_enemy_vram, import_bkg);  \
  set_bkg_tiles(x, y, 5, 4, enemy_buffer);                                     \
  handle_bkg_set_color(color, x, y, 5, 4)
#define place_lg_enemy_1(x, y, color)                                          \
  setupTileBuffer(enemy_buffer, 6, 6, 0, 8, start_of_enemy_vram, import_bkg);  \
  set_bkg_tiles(x, y, 6, 6, enemy_buffer);                                     \
  handle_bkg_set_color(color, x, y, 6, 6)

#define place_lg_enemy_2(x, y, color)                                          \
  setupTileBuffer(enemy_buffer, 6, 6, 6, 8, start_of_enemy_vram, import_bkg);  \
  set_bkg_tiles(x, y, 6, 6, enemy_buffer);                                     \
  handle_bkg_set_color(color, x, y, 6, 6)

  BYTE idx;
  BYTE small_enemies[6] = {-1, -1, -1, -1, -1, -1};
  BYTE sm_i = 0;
  BYTE large_enemies[2] = {-1, -1};
  BYTE lg_i = 0;
  BYTE enemy_count = (rand() % 6) + 1;
  for (BYTE i = 0; i < enemy_count; i++) {
    if (lg_i > 0 && sm_i > 0) {
      idx = get_small_enemy_idx();
    } else {
      idx = get_enemy_idx();
    }

    switch (idx) {
    case 0:
    case 1:
      small_enemies[sm_i] = idx;
      sm_i++;
      break;
    case 2:
    case 3:
      large_enemies[lg_i] = idx;
      lg_i++;
      break;
    }
  }

  // idk why but breaks don't like me so doing my gates in this inefficient way
  if (lg_i == 2) {
    sm_i = 0;
  }
  if (lg_i == 1 && sm_i > 2) {
    sm_i = 2;
  }

  BYTE next_x = 1;
  BYTE next_y = 5;
  BYTE enemy_slot_i = 0;
  struct enemy_slot *current_enemy;
  for (BYTE i = 0; i < lg_i; i++) {
    current_enemy = &enemy_slots[enemy_slot_i];
    BYTE idx = large_enemies[i];
    switch (idx) {
    case 2:
      place_lg_enemy_1(next_x, next_y, 1);
      break;
    case 3:
      place_lg_enemy_2(next_x, next_y, 1);
      break;
    }
    current_enemy->info = encounter_table[idx];
    current_enemy->hp = current_enemy->info.max_hp;
    current_enemy->alive = TRUE;
    current_enemy->x = next_x;
    current_enemy->y = next_y;
    current_enemy->w = 6;
    current_enemy->h = 6;
    enemy_slot_i++;
    next_x = 1;
    next_y += 6;
  }

  for (BYTE i = 0; i < sm_i; i++) {
    current_enemy = &enemy_slots[enemy_slot_i];
    BYTE idx = small_enemies[i];
    switch (idx) {
    case 0:
      place_sm_enemy_1(next_x, next_y, 1);
      break;
    case 1:
      place_sm_enemy_2(next_x, next_y, 1);
      break;
    }
    current_enemy->info = encounter_table[idx];
    current_enemy->hp = current_enemy->info.max_hp;
    current_enemy->alive = TRUE;
    current_enemy->x = next_x;
    current_enemy->y = next_y;
    current_enemy->w = 5;
    current_enemy->h = 4;
    enemy_slot_i++;
    next_x += 5;
    if (next_x > 10) {
      next_x = 1;
      next_y += 4;
    }
  }
  VM_GLOBAL(VAR_SCENE_ENEMIES_ALIVE) = lg_i + sm_i;

  place_bg_tiles;
}

void checkEnemyAlive(SCRIPT_CTX *THIS) OLDCALL BANKED {
  THIS;
  VM_GLOBAL(VAR_ATTACKER_ALIVE) =
      enemy_slots[VM_GLOBAL(VAR_ATTACKER_ID) - 5].alive;
}

void handleEnemyTakeDamage(SCRIPT_CTX *THIS) OLDCALL BANKED {
  THIS;
  struct enemy_slot *current_enemy;
  current_enemy = &enemy_slots[VM_GLOBAL(VAR_DEFENDER_ID) - 5];
  VM_GLOBAL(VAR_EXPLOSION_X) = current_enemy->x;
  VM_GLOBAL(VAR_EXPLOSION_Y) = current_enemy->y;
  VM_GLOBAL(VAR_EXPLOSION_W) = current_enemy->w;
  VM_GLOBAL(VAR_EXPLOSION_H) = current_enemy->h;

  UWORD * hit_roll = &VM_GLOBAL(VAR_TEMP_HIT_ROLL_0);
  UWORD * damage_calc = &VM_GLOBAL(VAR_TEMP_DAMAGE_CALCULATION);

  if(VM_GLOBAL(VAR_META_DEBUG) > 1){
    *hit_roll = 0;
  }else{
    // I think this probably needs to be changed to reflect the Attacker's stats.
    *hit_roll = rand() % VM_GLOBAL(VAR_CONST_GLOBAL_HIT_ROLL);
  }

  VM_GLOBAL(VAR_ATTACKER_MISSED) = (VM_GLOBAL(VAR_ATTACKER_HIT_CHANCE) - current_enemy-> info.evade) > *hit_roll;

  if(VM_GLOBAL(VAR_ATTACKER_MISSED)) return;

  UWORD *atk_dmg = &VM_GLOBAL(VAR_ATTACKER_DAMAGE);
  *damage_calc = (rand() % *atk_dmg) + (*atk_dmg + 1);
  if(VM_GLOBAL(VAR_ATTACKER_CRIT_CHANCE) > *hit_roll){
   // TODO Finish this after finishing player_slots.h 
  }
}

void enemyFlashBKG(SCRIPT_CTX *THIS) OLDCALL BANKED {
  THIS;
  struct enemy_slot *enemy =
      &enemy_slots[VM_GLOBAL(VAR_TURN_ORDER_CURRENT_ACTO) - 5];
  WORD color_1 = 1;
  WORD color_2 = 6;
  WORD x = enemy->x;
  WORD y = enemy->y;
  WORD w = enemy->w;
  WORD h = enemy->h;
  handle_bkg_flash(color_1, color_2, x, y, w, h);
}

void enemyRollInitiative(SCRIPT_CTX *THIS) OLDCALL BANKED {
  THIS;
  struct enemy_slot *current_enemy;
  UWORD *initiative_slot;
  for (int i = 0; i < 6; i++) {
    initiative_slot = &VM_GLOBAL(VAR_TURN_ORDER_SLOT_5_E1) + i;
    current_enemy = &enemy_slots[i];
    if (!current_enemy->alive)
      continue;
    *initiative_slot = rand() % current_enemy->info.max_hp;
    *initiative_slot += current_enemy->info.evade;
  }
}

void finishBattle(SCRIPT_CTX *THIS) OLDCALL BANKED {
  // I can probably put EXP Gains and Gil Gains here too.
  THIS;
}