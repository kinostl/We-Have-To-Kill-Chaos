#ifndef FF_ARMOR_DATA
#define FF_ARMOR_DATA
#include "class_data.h"
#include <asm/types.h>

enum A_TYPE { UNARMORED, ARMOR, ROBE, BRACELET, SHIELD, HELMET, GAUNTLET };

typedef struct {
  BYTE id;
  enum A_TYPE type;
  UBYTE defense;
  UBYTE weight;
  UWORD price;
  UWORD classes; // Flag
} armor_data;

void set_armor(BYTE armor_id, armor_data *armor) OLDCALL BANKED;
#endif