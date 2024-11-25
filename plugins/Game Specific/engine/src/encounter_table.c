#include "encounter_table.h"
#include "enums.h"
#include "ff_util.h"
#include <bankdata.h>
#include <gb/gb.h>

#pragma bank 255

#define global_pos(x, y) (x + (y * 16))

UBYTE load_slots(ENEMY_TYPE enemy_type, ENEMY_TYPE encounter_table[6],
                 UBYTE start_at, UBYTE min, UBYTE max) BANKED {
  UBYTE encounter_roll = drand(min, max);
  for (BYTE i = 0; i < encounter_roll; i++) {
    encounter_table[i + start_at] = enemy_type;
  }
  return encounter_roll;
}

void load_encounter(ENEMY_TYPE encounter_table[6], UBYTE world_x,
                         UBYTE world_y) BANKED {
  for (UBYTE i = 0; i < 6; i++) {
    encounter_table[i] = EMPTY_ENEMY_SLOT;
  }

  const UBYTE encounter_table_id = global_pos(world_x, world_y);
  UBYTE encounter_roll = drand(0, 255);
  UBYTE start_at = 0;

  if (encounter_roll < 4) {
    encounter_roll = 7;
  } else if (encounter_roll < 16) {
    encounter_roll = 6;
  } else if (encounter_roll < 40) {
    encounter_roll = 5;
  } else if (encounter_roll < 64) {
    encounter_roll = 4;
  } else if (encounter_roll < 112) {
    encounter_roll = 3;
  } else if (encounter_roll < 160) {
    encounter_roll = 2;
  } else if (encounter_roll < 208) {
    encounter_roll = 1;
  } else {
    encounter_roll = 0;
  }

  switch (encounter_table_id) {
  case global_pos(7, 7):
  case global_pos(8, 7):
    // World Map Near Temple of Fiends
    switch (encounter_roll) {
    case 7:
      start_at = load_slots(MADPONY, encounter_table, 0, 1, 2);
      if (start_at < 2) {
        load_slots(GrIMP, encounter_table, start_at, 0, 2);
      }
      return;
    case 6:
      start_at = load_slots(IMP, encounter_table, 0, 2, 4);
      load_slots(GrIMP, encounter_table, start_at, 0, 2);
      return;
    case 5:
      load_slots(MADPONY, encounter_table, 0, 1, 1);
      return;
    case 4:
      load_slots(CREEP, encounter_table, 0, 1, 2);
      return;
    case 3:
      load_slots(IMP, encounter_table, 0, 3, 6);
      return;
    case 2:
      load_slots(BONE, encounter_table, 0, 2, 4);
      return;
    case 1:
      start_at = load_slots(BONE, encounter_table, 0, 1, 2);
      load_slots(SPIDER, encounter_table, start_at, 1, 2);
    case 0:
    default:
      load_slots(GrIMP, encounter_table, 0, 1, 3);
      return;
    }
  case global_pos(8, 8):
  case global_pos(8, 9):
  case global_pos(9, 9):
    // World Map North of Coneria
    switch (encounter_roll) {
    case 7:
      start_at = load_slots(IMP, encounter_table, 0, 2, 4);
      load_slots(GrIMP, encounter_table, start_at, 0, 2);
      return;
    case 6:
      load_slots(MADPONY, encounter_table, 0, 1, 1);
      return;
    case 5:
      load_slots(WOLF, encounter_table, 0, 1, 2);
      return;
    case 4:
      load_slots(GrIMP, encounter_table, 0, 1, 3);
      return;
    default:
      load_slots(IMP, encounter_table, 0, 3, 6);
      return;
    }
  case global_pos(8, 10):
  case global_pos(9, 10):
  default:
    // World Map Coneria Area or Undefined Area
    load_slots(IMP, encounter_table, 0, 3, 6);
    return;
  }
}