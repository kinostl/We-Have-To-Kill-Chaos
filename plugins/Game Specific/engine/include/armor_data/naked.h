#ifndef FF_ARMOR_NAKED
#define FF_ARMOR_NAKED

#include "armor_data.h"
#include <asm/types.h>
void naked(armor_data *armor) OLDCALL BANKED;
#endif