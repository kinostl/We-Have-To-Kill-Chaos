#include "data/bg_battle_concept_tileset.h"
#include "data_manager.h"
#include "encounter_table.h"
#include "enemy_data.h"
#include "enemy_sprites.h"
#include "entity_data.h"
#include "enums.h"
#include "handle_flashing.h"
#include "rand.h" // IWYU pragma: keep
#include "extra_data.h"
#include "vm.h"
#include <asm/types.h>
#include <bankdata.h>
#include <data/game_globals.h>
#include <gb/gb.h>
#include <gbs_types.h>
#include <string.h>
#include <types.h>
#include "data/tileset_enemies_imp.h"

#pragma bank 255

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
void handleSetEnemyTarget(SCRIPT_CTX *THIS) OLDCALL BANKED {
  THIS;
  BYTE enemy_roll = rand() % 8;
  UWORD *target = &VM_GLOBAL(VAR_DEFENDER_ID);
  switch (enemy_roll) {
  default:
    *target = 0;
    break;
  case 4:
  case 5:
    *target = 1;
    break;
  case 6:
    *target = 2;
    break;
  case 7:
    *target = 3;
    break;
  }
}

BYTE get_small_enemy_idx(void) OLDCALL BANKED {
  BYTE enemy_roll = rand() % 6;
  switch (enemy_roll) {
  default:
    return 0;
  case 4:
  case 5:
    return 1;
  }
}

BYTE get_enemy_idx(void) OLDCALL BANKED {
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

UBYTE load_enemy_tiles(UBYTE start_of_enemy_vram, ENEMY_TYPE enemy_type) BANKED {
  enemy_sprite sprite;

  MemcpyBanked(&sprite, &enemy_sprite_db[enemy_type], sizeof(enemy_sprite), BANK(FF_ENEMY_SPRITES));

  const tileset_t * t_set = sprite.sprite;
  UWORD n_tiles = ReadBankedUWORD(&(t_set->n_tiles), sprite.bank);
  UBYTE * data = t_set->tiles;

  SetBankedBkgData(start_of_enemy_vram, n_tiles, data, sprite.bank);
  return start_of_enemy_vram + n_tiles; // New end of available VRAM
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

void initialize_entity_data(enemy_data *slot) OLDCALL BANKED {
  memcpy(&slot->ext, NULL, sizeof(entity_data));
  strcpy(slot->name, "");
  slot->skill_idx = 0;
}

void setupEnemySlots(void) BANKED {
  ENEMY_TYPE encounter_table[4];

  set_encounter_table(encounter_table, 0);
  // Default to null
  for (int i = 0; i < 6; i++) {
    initialize_entity_data(&enemy_slots[i]);
  }

  // Now load up the enemy VRAM
  // Then draw the tiles manually, knowing that they'll be in order correctly.
  // https://github.com/chrismaltby/gb-studio/blob/9a9696decc30b7970e152919a4a4163d967c5ead/appData/src/gb/src/core/ui.c#L4

  UBYTE start_of_enemy_vram, tail_of_enemy_vram;
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
  // MemcpyBanked(&import_bkg, &bg_enemies_plains_1, sizeof(import_bkg),
  //              BANK(bg_enemies_plains_1));

  MemcpyBanked(&start_of_enemy_vram, &bg_battle_concept_tileset.n_tiles,
               sizeof(UBYTE), BANK(bg_battle_concept_tileset));

  tail_of_enemy_vram = start_of_enemy_vram;
  tail_of_enemy_vram = load_enemy_tiles(tail_of_enemy_vram, IMP);
  tail_of_enemy_vram = load_enemy_tiles(tail_of_enemy_vram, WOLF);
  tail_of_enemy_vram = load_enemy_tiles(tail_of_enemy_vram, MADPONY);
  // tail_of_enemy_vram = load_enemy_tiles(tail_of_enemy_vram, WOLF);
  // tail_of_enemy_vram = load_enemy_tiles(tail_of_enemy_vram, MADPONY);

  // MemcpyBanked(&tileset_size, &bg_enemies_plains_1_tileset.n_tiles,
  //              sizeof(UBYTE), BANK(bg_enemies_plains_1_tileset));

  // SetBankedBkgData(start_of_enemy_vram, tileset_size,
  //                  bg_enemies_plains_1_tileset.tiles,
  //                  BANK(bg_enemies_plains_1_tileset));

//   UBYTE enemy_buffer[6 * 6];

//   // defines because we're going to be repeating this and I don't feel like
//   // looping or figuring out if inlines can do js stuff
//   // ngl getting this to be a 6*6 buffer instead of a 10*4 is me having a
//   // pissing contest with myself

// #define place_bg_tiles                                                         \
//   setupTileBuffer(enemy_buffer, 5, 4, 0, 0, start_of_enemy_vram, import_bkg);  \
//   set_bkg_tiles(1, 1, 5, 4, enemy_buffer);                                     \
//   handle_bkg_set_color(0, 1, 1, 5, 4);                                         \
//   setupTileBuffer(enemy_buffer, 5, 4, 5, 0, start_of_enemy_vram, import_bkg);  \
//   set_bkg_tiles(6, 1, 5, 4, enemy_buffer);                                     \
//   handle_bkg_set_color(0, 6, 1, 5, 4)

// #define place_sm_enemy_1(x, y, color)                                          \
//   setupTileBuffer(enemy_buffer, 5, 4, 0, 4, start_of_enemy_vram, import_bkg);  \
//   set_bkg_tiles(x, y, 5, 4, enemy_buffer);                                     \
//   handle_bkg_set_color(color, x, y, 5, 4)

// #define place_sm_enemy_2(x, y, color)                                          \
//   setupTileBuffer(enemy_buffer, 5, 4, 5, 4, start_of_enemy_vram, import_bkg);  \
//   set_bkg_tiles(x, y, 5, 4, enemy_buffer);                                     \
//   handle_bkg_set_color(color, x, y, 5, 4)
// #define place_lg_enemy_1(x, y, color)                                          \
//   setupTileBuffer(enemy_buffer, 6, 6, 0, 8, start_of_enemy_vram, import_bkg);  \
//   set_bkg_tiles(x, y, 6, 6, enemy_buffer);                                     \
//   handle_bkg_set_color(color, x, y, 6, 6)

// #define place_lg_enemy_2(x, y, color)                                          \
//   setupTileBuffer(enemy_buffer, 6, 6, 6, 8, start_of_enemy_vram, import_bkg);  \
//   set_bkg_tiles(x, y, 6, 6, enemy_buffer);                                     \
//   handle_bkg_set_color(color, x, y, 6, 6)

//   BYTE idx;
//   BYTE small_enemies[6] = {-1, -1, -1, -1, -1, -1};
//   BYTE sm_i = 0;
//   BYTE large_enemies[2] = {-1, -1};
//   BYTE lg_i = 0;
//   BYTE enemy_count = (rand() % 6) + 1;
//   for (BYTE i = 0; i < enemy_count; i++) {
//     if (lg_i > 0 && sm_i > 0) {
//       idx = get_small_enemy_idx();
//     } else {
//       idx = get_enemy_idx();
//     }

//     switch (idx) {
//     case 0:
//     case 1:
//       small_enemies[sm_i] = idx;
//       sm_i++;
//       break;
//     case 2:
//     case 3:
//       large_enemies[lg_i] = idx;
//       lg_i++;
//       break;
//     }
//   }

//   // idk why but breaks don't like me so doing my gates in this inefficient way
//   if (lg_i == 2) {
//     sm_i = 0;
//   }
//   if (lg_i == 1 && sm_i > 2) {
//     sm_i = 2;
//   }

//   BYTE next_x = 1;
//   BYTE next_y = 5;
//   BYTE entity_data_i = 0;
//   BYTE enemies_alive = 0;
//   enemy_data * current_enemy;
//   for (BYTE i = 0; i < lg_i; i++) {
//     current_enemy = &enemy_slots[entity_data_i];
//     BYTE idx = large_enemies[i];

//     switch (idx) {
//     case 2:
//       place_lg_enemy_1(next_x, next_y, 1);
//       break;
//     case 3:
//       place_lg_enemy_2(next_x, next_y, 1);
//       break;
//     }

//     load_enemy(current_enemy, encounter_table[idx]);
//     current_enemy->ext.hp = current_enemy->ext.max_hp;
//     current_enemy->ext.status = NULL;
//     current_enemy->ext.pos.x = next_x;
//     current_enemy->ext.pos.y = next_y;
//     current_enemy->ext.pos.w = 6;
//     current_enemy->ext.pos.h = 6;
//     current_enemy->ext.idx = entity_data_i;

//     entity_data_i++;
//     enemies_alive++;

//     next_x = 1;
//     next_y += 6;
//   }

//   for (BYTE i = 0; i < sm_i; i++) {
//     current_enemy = &enemy_slots[entity_data_i];
//     BYTE idx = small_enemies[i];

//     switch (idx) {
//     case 0:
//       place_sm_enemy_1(next_x, next_y, 1);
//       break;
//     case 1:
//       place_sm_enemy_2(next_x, next_y, 1);
//       break;
//     }

//     load_enemy(current_enemy, encounter_table[idx]);
//     current_enemy->ext.hp = current_enemy->ext.max_hp;
//     current_enemy->ext.status = NULL;
//     current_enemy->ext.pos.x = next_x;
//     current_enemy->ext.pos.y = next_y;
//     current_enemy->ext.pos.w = 5;
//     current_enemy->ext.pos.h = 4;
//     current_enemy->ext.idx = entity_data_i;


//     entity_data_i++;
//     enemies_alive++;
//     next_x += 5;
//     if (next_x > 10) {
//       next_x = 1;
//       next_y += 4;
//     }
//   }

//   place_bg_tiles;

}

void enemyFlashBKG(SCRIPT_CTX *THIS) OLDCALL BANKED {
  THIS;
  WORD color_1 = 1;
  WORD color_2 = 6;
  WORD x = current_enemy->ext.pos.x;
  WORD y = current_enemy->ext.pos.y;
  WORD w = current_enemy->ext.pos.w;
  WORD h = current_enemy->ext.pos.h;
  handle_bkg_flash(color_1, color_2, x, y, w, h);
}

void handleEnemyDefeated(SCRIPT_CTX * THIS) OLDCALL BANKED {
  WORD x = current_enemy->ext.pos.x;
  WORD y = current_enemy->ext.pos.y;
  WORD w = current_enemy->ext.pos.w;
  WORD h = current_enemy->ext.pos.h;

  handle_bkg_set_color_slow(5, x, y, w, h);
}

void finishBattle(SCRIPT_CTX *THIS) OLDCALL BANKED {
  // I can probably put EXP Gains and Gil Gains here too.
  THIS;
}

void checkEnemyAlive(void) BANKED {}
void setupHeroData(void) BANKED {}
void handleEnemyTakeDamage(void) BANKED {}
void setupPlayerSlots(void) BANKED {}