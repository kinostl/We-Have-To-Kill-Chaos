#include "data/bg_battle_concept_tileset.h"
#include "data/bg_enemies_plains_1.h"
#include "data/bg_enemies_plains_1_tileset.h"
#include "encounter_table.h"
#include "enemy_data.h"
#include "entity_data.h"
#include "handle_flashing.h"
#include "item_slot.h"
#include "rand.h" // IWYU pragma: keep
#include "extra_data.h"
#include "vm.h"
#include <asm/types.h>
#include <bankdata.h>
#include <data/game_globals.h>
#include <gb/gb.h>
#include <gbs_types.h>
#include <math.h>
#include <string.h>

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

void initialize_entity_data(struct entity_data * slot) OLDCALL BANKED {
  slot->hp = 0;
  slot->skill_idx = 0;
  slot->alive = FALSE;
}
void setupPlayerSlots(SCRIPT_CTX *THIS) OLDCALL BANKED {
  THIS;
  //
  turn_slots[0].max_hp = 35;
  turn_slots[0].hp = 35;
  turn_slots[0].hit_chance = 10;
  turn_slots[0].crit_chance = 0;
  turn_slots[0].damage = 10;
  turn_slots[0].alive = TRUE;
  turn_slots[0].ap = 0;
  strcpy(turn_slots[0].name, "ONCLER");
  turn_slots[0].skills[0] = FIGHT;
  turn_slots[0].skill_costs[0] = 1;
  turn_slots[0].x = 13;
  turn_slots[0].y = 2;
  turn_slots[0].w = 3;
  turn_slots[0].h = 3;

  turn_slots[0].skills[1] = SHIELD;
  turn_slots[0].skill_costs[1] = 1;

  turn_slots[0].skills[2] = RUNE_SWORD;
  turn_slots[0].skill_costs[2] = 2;

  turn_slots[0].skills[3] = LUSTER;
  turn_slots[0].skill_costs[3] = 3;

  weapon_slots[0].type=6;
  weapon_slots[0].color=2;
  weapon_slots[0].attack=69;
  weapon_slots[0].classes=69;
  weapon_slots[0].crit_chance=69;
  weapon_slots[0].hit_chance=69;
  weapon_slots[0].id=69;
  weapon_slots[0].price=69;
  item_slots[0].count=42;
  item_slots[0].type=42;
  //
  turn_slots[1].max_hp = 20;
  turn_slots[1].hp = 20;
  turn_slots[1].hit_chance = 10;
  turn_slots[1].crit_chance = 0;
  turn_slots[1].damage = 10;
  turn_slots[1].alive = TRUE;
  turn_slots[1].ap = 0;
  strcpy(turn_slots[1].name, "TWOFER");
  turn_slots[1].skills[0] = FIGHT;
  turn_slots[1].skill_costs[0] = 1;
  turn_slots[1].skills[1] = GOBLIN_PUNCH;
  turn_slots[1].skill_costs[1] = 1;
  turn_slots[1].x = 13;
  turn_slots[1].y = 2;
  turn_slots[1].w = 3;
  turn_slots[1].h = 3;

  weapon_slots[1].type=8;
  weapon_slots[1].color=4;
  weapon_slots[1].attack=69;
  weapon_slots[1].classes=69;
  weapon_slots[1].crit_chance=69;
  weapon_slots[1].hit_chance=69;
  weapon_slots[1].id=69;
  weapon_slots[1].price=69;
  //
  turn_slots[2].max_hp = 25;
  turn_slots[2].hp = 25;
  turn_slots[2].hit_chance = 10;
  turn_slots[2].crit_chance = 0;
  turn_slots[2].damage = 10;
  turn_slots[2].alive = TRUE;
  turn_slots[2].ap = 0;
  strcpy(turn_slots[2].name, "THREEF");
  turn_slots[2].skills[0] = FIRE;
  turn_slots[2].skill_costs[0] = 1;
  turn_slots[2].skills[1] = ICE;
  turn_slots[2].skill_costs[1] = 1;
  turn_slots[2].x = 13;
  turn_slots[2].y = 10;
  turn_slots[2].w = 3;
  turn_slots[2].h = 3;
  weapon_slots[2].type=8;
  weapon_slots[2].color=3;
  weapon_slots[2].attack=69;
  weapon_slots[2].classes=69;
  weapon_slots[2].crit_chance=69;
  weapon_slots[2].hit_chance=69;
  weapon_slots[2].id=69;
  weapon_slots[2].price=69;
  //
  turn_slots[3].max_hp = 10;
  turn_slots[3].hp = 10;
  turn_slots[3].hit_chance = 10;
  turn_slots[3].crit_chance = 0;
  turn_slots[3].damage = 10;
  turn_slots[3].alive = TRUE;
  turn_slots[3].ap = 0;
  strcpy(turn_slots[3].name, "FOURNA");
  turn_slots[3].skills[0] = HARM;
  turn_slots[3].skill_costs[0] = 1;
  turn_slots[3].skills[1] = HEAL;
  turn_slots[3].skill_costs[1] = 1;
  turn_slots[3].x = 13;
  turn_slots[3].y = 14;
  turn_slots[3].w = 3;
  turn_slots[3].h = 3;
  weapon_slots[3].type=3;
  weapon_slots[3].color=1;
  weapon_slots[3].attack=69;
  weapon_slots[3].classes=69;
  weapon_slots[3].crit_chance=69;
  weapon_slots[3].hit_chance=69;
  weapon_slots[3].id=69;
  weapon_slots[3].price=69;
}

void setupEnemySlots(SCRIPT_CTX *THIS) OLDCALL BANKED {
  THIS;
  BYTE encounter_table[4];

  set_encounter_table(encounter_table, 0);
  // Default to null
  for (int i = 4; i < 10; i++) {
    initialize_entity_data(&turn_slots[i]);
  }

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
  BYTE entity_data_i = 4;
  BYTE enemies_alive = 0;
  struct entity_data * current_enemy;
  for (BYTE i = 0; i < lg_i; i++) {
    current_enemy = &turn_slots[entity_data_i];
    BYTE idx = large_enemies[i];

    switch (idx) {
    case 2:
      place_lg_enemy_1(next_x, next_y, 1);
      break;
    case 3:
      place_lg_enemy_2(next_x, next_y, 1);
      break;
    }

    set_enemy_data(current_enemy, encounter_table[idx]);
    current_enemy->hp = current_enemy->max_hp;
    current_enemy->alive = TRUE;
    current_enemy->x = next_x;
    current_enemy->y = next_y;
    current_enemy->w = 6;
    current_enemy->h = 6;

    entity_data_i++;
    enemies_alive++;

    next_x = 1;
    next_y += 6;
  }

  for (BYTE i = 0; i < sm_i; i++) {
    current_enemy = &turn_slots[entity_data_i];
    BYTE idx = small_enemies[i];

    switch (idx) {
    case 0:
      place_sm_enemy_1(next_x, next_y, 1);
      break;
    case 1:
      place_sm_enemy_2(next_x, next_y, 1);
      break;
    }

    set_enemy_data(current_enemy, encounter_table[idx]);
    current_enemy->hp = current_enemy->max_hp;
    current_enemy->alive = TRUE;
    current_enemy->x = next_x;
    current_enemy->y = next_y;
    current_enemy->w = 5;
    current_enemy->h = 4;


    entity_data_i++;
    enemies_alive++;
    next_x += 5;
    if (next_x > 10) {
      next_x = 1;
      next_y += 4;
    }
  }
  VM_GLOBAL(VAR_SCENE_ENEMIES_ALIVE) = enemies_alive;

  place_bg_tiles;
}

void checkEnemyAlive(SCRIPT_CTX *THIS) OLDCALL BANKED {
  THIS;
  VM_GLOBAL(VAR_ATTACKER_ALIVE) =
      turn_slots[VM_GLOBAL(VAR_ATTACKER_ID)].alive;
}

void handleEnemyTakeDamage(SCRIPT_CTX *THIS) OLDCALL BANKED {
  THIS;
  struct entity_data *defender;
  defender = &turn_slots[VM_GLOBAL(VAR_DEFENDER_ID)];
  struct entity_data *attacker;
  attacker = &turn_slots[VM_GLOBAL(VAR_ATTACKER_ID)];

  UWORD * name = &VM_GLOBAL(VAR_1_C);
  UWORD name_l = strlen(defender->name);
  for(int i=0;i<name_l;i++){
    name[i] = defender->name[i];
  }
  for(int i=name_l;i<8;i++){
    name[i]=127;
  }

  VM_GLOBAL(VAR_EXPLOSION_X) = defender->x;
  VM_GLOBAL(VAR_EXPLOSION_Y) = defender->y;
  VM_GLOBAL(VAR_EXPLOSION_W) = defender->w;
  VM_GLOBAL(VAR_EXPLOSION_H) = defender->h;

  VM_GLOBAL(VAR_DEFENDER_STARTING_HP) = defender->hp;

  UWORD hit_roll;
  UWORD damage_calc;

  if (VM_GLOBAL(VAR_META_DEBUG) > 1) {
    hit_roll = 0;
  } else {
    hit_roll = rand() % 201;
  }

  UWORD target_number = (168 + attacker->hit_chance) - defender->evade;

  VM_GLOBAL(VAR_ATTACKER_MISSED) = target_number < hit_roll;
  if(hit_roll == 0){
    VM_GLOBAL(VAR_ATTACKER_MISSED) = FALSE;
  }
  if(hit_roll == 200){
    VM_GLOBAL(VAR_ATTACKER_MISSED) = TRUE;
  }

  if (VM_GLOBAL(VAR_ATTACKER_MISSED))
    return;

  const UWORD atk_dmg = attacker->damage;
  damage_calc = (rand() % atk_dmg) + (atk_dmg + 1);
  if (attacker->crit_chance > hit_roll) {
    defender->hp -= damage_calc;
    VM_GLOBAL(VAR_ATTACKER_CRIT_DAMAGE) = damage_calc;
  }
  damage_calc = MAX(damage_calc - defender->absorb, 1);
  defender->hp -= damage_calc;
  VM_GLOBAL(VAR_DEFENDER_ENDING_HP) = defender->hp;

  if(defender->hp <= 0){
    defender->alive = FALSE;
    if (VM_GLOBAL(VAR_DEFENDER_ID) >= 4) {
      VM_GLOBAL(VAR_SCENE_ENEMIES_ALIVE)--;
    }
  }
}

void enemyFlashBKG(SCRIPT_CTX *THIS) OLDCALL BANKED {
  THIS;
  struct entity_data *enemy =
      &turn_slots[VM_GLOBAL(VAR_ATTACKER_ID)];
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
  struct entity_data *entity;
  UWORD *initiative_slot;
  for (int i = 0; i < 10; i++) {
    entity = &turn_slots[i];
    if (!entity->alive)
      continue;
    initiative_slot = &VM_GLOBAL(VAR_TURN_ORDER_SLOT_1_P1) + i;
    *initiative_slot = rand() % entity->max_hp;
    *initiative_slot += entity->evade;
    if (i < 4) {
      *initiative_slot += VM_GLOBAL(VAR_CONST_BASE_PLAYER_EVADE);
    }
  }
}

void finishBattle(SCRIPT_CTX *THIS) OLDCALL BANKED {
  // I can probably put EXP Gains and Gil Gains here too.
  THIS;
}