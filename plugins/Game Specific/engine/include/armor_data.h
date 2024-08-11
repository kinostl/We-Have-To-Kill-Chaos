#ifndef FF_ARMOR_DATA
#define FF_ARMOR_DATA
#include "class_data.h"
#include <asm/types.h>

enum A_TYPE { UNARMORED, ARMOR, ROBE, BRACELET, SHIELD, HELMET, GAUNTLET };

struct armor_data {
  BYTE id;
  enum A_TYPE type;
  BYTE defense;
  BYTE weight;
  UWORD price;
  UWORD classes; // Flag
};

void set_armor(BYTE armor_id, struct armor_data *armor) OLDCALL BANKED;
#endif