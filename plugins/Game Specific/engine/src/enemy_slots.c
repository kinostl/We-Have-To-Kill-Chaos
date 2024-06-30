#include <asm/types.h>
#include "data/max_global_vars.h"
#include "enemy_data.h"
#include "rand.h" // IWYU pragma: keep
#include "vm.h"
#include <bankdata.h>
#include <gb/gb.h>
#include <gbs_types.h>
#include "data/bg_enemies_plains_1_tileset.h"
#include "data/bg_enemies_plains_1.h"
#include "data/bg_battle_concept_tileset.h"

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

After testing, this is a 1/4 chance of getting a big guy in a fight and they tend to be dangerous encounters. Not sure if good or bad.
*/

BYTE get_small_enemy_idx(void) {
  const BYTE enemy_roll = rand() % 6;
  switch (enemy_roll) {
  default:
    return 0;
  case 4:
  case 5:
    return 1;
  }
}

BYTE get_enemy_idx(void) {
  const BYTE enemy_roll = rand() % 8;
  switch (enemy_roll) {
  case 0:
    return 2;
  case 1:
    return 3;
  default:
    return get_small_enemy_idx();
  }
}

void setupTileBuffer(UBYTE * buffer, UBYTE w, UBYTE h, UBYTE x, UBYTE y, UBYTE offset, background_t import_bkg) OLDCALL BANKED{

  const UBYTE buffer_s = w*h;

  UWORD buffer_offset=0;
  UWORD bank_offset=0;

  for (UBYTE i = 0; i < h; i++) {
    buffer_offset = i * w;
    bank_offset = (i+y) * import_bkg.width + x;
    UBYTE * import_ptr = import_bkg.tilemap.ptr;
    import_ptr += bank_offset;

    MemcpyBanked(buffer + buffer_offset, import_ptr,
                 sizeof(UBYTE) * w, import_bkg.tilemap.bank);
  }

  for(int i=0;i<buffer_s;i++){
    buffer[i]+=offset;
  }
}

void setupEnemySlots(SCRIPT_CTX *THIS) OLDCALL BANKED {
  struct enemy_info *enemy_slots = VM_REF_TO_PTR(MAX_GLOBAL_VARS+1);
  struct enemy_info encounter_table[4];

  setup_encounter_table(0, encounter_table);
  // Default to -1
  enemy_slots[0].type = -1;
  enemy_slots[1].type = -1;
  enemy_slots[2].type = -1;
  enemy_slots[3].type = -1;
  enemy_slots[4].type = -1;
  enemy_slots[5].type = -1;

  // Now load up the enemy VRAM
  // Then draw the tiles manually, knowing that they'll be in order correctly.
  // https://github.com/chrismaltby/gb-studio/blob/9a9696decc30b7970e152919a4a4163d967c5ead/appData/src/gb/src/core/ui.c#L4

  UBYTE start_of_enemy_vram;
  UBYTE tileset_size;
  background_t import_bkg;

  MemcpyBanked(&import_bkg, &bg_enemies_plains_1, sizeof(import_bkg), BANK(bg_enemies_plains_1));

  MemcpyBanked(&start_of_enemy_vram, &bg_battle_concept_tileset.n_tiles, sizeof(UBYTE), BANK(bg_battle_concept_tileset));
  MemcpyBanked(&tileset_size, &bg_enemies_plains_1_tileset.n_tiles, sizeof(UBYTE), BANK(bg_enemies_plains_1_tileset));

  SetBankedBkgData(start_of_enemy_vram,tileset_size, bg_enemies_plains_1_tileset.tiles, BANK(bg_enemies_plains_1_tileset));

  UBYTE enemy_buffer[10*4];

  //defines because we're going to be repeating this and I don't feel like looping or figuring out if inlines can do js stuff
  #define place_bg_tiles setupTileBuffer(enemy_buffer, 10, 4, 0, 0, start_of_enemy_vram, import_bkg);\
  set_bkg_tiles(1, 1, 10, 4, enemy_buffer)

  #define place_sm_enemy_1(x,y) setupTileBuffer(enemy_buffer, 5, 4, 0, 4, start_of_enemy_vram, import_bkg);\
  set_bkg_tiles(x, y, 5, 4, enemy_buffer)

  #define place_sm_enemy_2(x,y) setupTileBuffer(enemy_buffer, 5, 4, 5, 4, start_of_enemy_vram, import_bkg);\
  set_bkg_tiles(x, y, 5, 4, enemy_buffer)

  #define place_lg_enemy_1(x,y) setupTileBuffer(enemy_buffer, 6, 6, 0, 8, start_of_enemy_vram, import_bkg);\
  set_bkg_tiles(x, y, 6, 6, enemy_buffer);

  #define place_lg_enemy_2(x,y) setupTileBuffer(enemy_buffer, 6, 6, 6, 8, start_of_enemy_vram, import_bkg);\
  set_bkg_tiles(x, y, 6, 6, enemy_buffer);

  BYTE idx;
  BYTE small_enemies[6] = {-1, -1, -1, -1,-1,-1};
  BYTE sm_i=0;
  BYTE large_enemies[2] = {-1, -1};
  BYTE lg_i=0;
  const BYTE enemy_count = (rand() % 6) + 1;
  for (BYTE i = 0; i < enemy_count; i++) {
    if(lg_i > 0 && sm_i > 0){
      idx = get_small_enemy_idx();
    }else{
      idx = get_enemy_idx();
    }

    enemy_slots[i] = encounter_table[idx];

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

  //idk why but breaks don't like me so doing my gates in this inefficient way
  if(lg_i == 2){
    sm_i = 0;
  }
  if (lg_i == 1 && sm_i > 2) {
    sm_i = 2;
  }

  BYTE next_x=1;
  BYTE next_y=5;
  BYTE enemy_slot_i=0;
  for(BYTE i=0;i<lg_i;i++){
    const BYTE idx = large_enemies[i];
    switch(idx){
      case 2:
      place_lg_enemy_1(next_x, next_y);
      break;
      case 3:
      place_lg_enemy_2(next_x, next_y);
      break;
    }
    enemy_slots[enemy_slot_i] = encounter_table[idx];
    enemy_slot_i++;
    next_x = 1;
    next_y += 6;
  }

  for(BYTE i=0;i<sm_i;i++){
    const BYTE idx = small_enemies[i];
    switch(idx){
      case 0:
      place_sm_enemy_1(next_x, next_y);
      break;
      case 1:
      place_sm_enemy_2(next_x, next_y);
      break;
    }
    enemy_slots[enemy_slot_i] = encounter_table[idx];
    enemy_slot_i++;
    next_x+=5;
    if(next_x>10){
      next_x=1;
      next_y+=4;
    }
  }

  place_bg_tiles;
}


void finishBattle(SCRIPT_CTX *THIS) OLDCALL BANKED {
  // I can probably put EXP Gains and Gil Gains here too.
  THIS;
}