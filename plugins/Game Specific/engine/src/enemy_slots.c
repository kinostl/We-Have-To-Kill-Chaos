#include "battle_headers.h"
#include "data/bg_battle_concept_tileset.h"
#include "data_manager.h"
#include "encounter_table.h"
#include "enemy_data.h"
#include "enemy_sprites.h"
#include "entity_data.h"
#include "enums.h"
#include "handle_flashing.h"
#include "extra_data.h"
#include "vm.h"
#include <asm/types.h>
#include <bankdata.h>
#include <data/game_globals.h>
#include <gb/gb.h>
#include <gbs_types.h>
#include <string.h>
#include <types.h>

#pragma bank 255

void initialize_entity_data(enemy_data *slot) OLDCALL BANKED {
  memcpy(&slot->ext, NULL, sizeof(entity_data));
  strcpy(slot->name, "");
  slot->skill_idx = 0;
}

void setupEnemySlots(void) BANKED {
  ENEMY_TYPE encounter_table[6];

  // Default to null
  for (int i = 0; i < 6; i++) {
    initialize_entity_data(&enemy_slots[i]);
  }

  clean_enemy_tiles();

  UBYTE tail_of_enemy_vram;

  MemcpyBanked(&tail_of_enemy_vram, &bg_battle_concept_tileset.n_tiles,
               sizeof(UBYTE), BANK(bg_battle_concept_tileset));

  load_encounter(encounter_table, 9, 10);

  const UBYTE n_tiles = load_battle_header(tail_of_enemy_vram, FIELD);
  set_battle_header(tail_of_enemy_vram);

  tail_of_enemy_vram+=n_tiles;

  ENEMY_TYPE prev_enemy = EMPTY_ENEMY_SLOT;
  UBYTE x = 1;
  UBYTE y = 5;
  enemy_view enemy_view;
  for (int i = 0; i < 6; i++) {
    enemy_data *current_enemy = &enemy_slots[i];
    load_enemy(current_enemy, encounter_table[i]);
    if (encounter_table[i] == EMPTY_ENEMY_SLOT)
      break;

    if (prev_enemy != encounter_table[i]) {
      enemy_view.vram_ptr = tail_of_enemy_vram;
      load_enemy_tiles(&enemy_view, encounter_table[i]);
      prev_enemy = encounter_table[i];
      tail_of_enemy_vram += enemy_view.n_tiles;
    }
    current_enemy->ext.hp = current_enemy->ext.max_hp;
    current_enemy->ext.status = NULL;
    current_enemy->ext.idx = i;
    current_enemy->ext.pos.x = x;
    current_enemy->ext.pos.y = y;

    if (enemy_view.n_tiles < (6 * 6)) {
      draw_enemy_sm(&enemy_view, x, y);

      y+=4;
      if(y > 16){
        y = 5;
        x +=5;
      }

      current_enemy->ext.pos.w = 4;
      current_enemy->ext.pos.h = 4;
    } else {
      draw_enemy_lg(&enemy_view, x, y);

      y+=6;

      current_enemy->ext.pos.w = 6;
      current_enemy->ext.pos.h = 6;
    }
  }
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
void handleSetEnemyTarget(SCRIPT_CTX *THIS) OLDCALL BANKED {}