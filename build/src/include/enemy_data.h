#ifndef _FF_ENEMY_DATA_H_INCLUDE
#define _FF_ENEMY_DATA_H_INCLUDE

#include <stdint.h>

const typedef struct enemy_info {
  unsigned char name[5];
  uint16_t hp;
} enemy_info;

extern const enemy_info enemy_db[1];

#endif
