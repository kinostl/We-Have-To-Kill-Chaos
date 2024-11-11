#ifndef FF_ARMOR_DATA
#define FF_ARMOR_DATA
#include "class_data.h"
#include "enums.h"
#include <asm/types.h>

typedef struct {
  ARMOR_TYPE id;
  ARMOR_FAMILY type;
  UBYTE defense;
  UBYTE weight;
  UWORD price;
  JOB classes; // Flag
} armor_data;

extern const armor_data armor_db[];

void load_armor(armor_data *armor, ARMOR_TYPE armor_type) BANKED;
#endif