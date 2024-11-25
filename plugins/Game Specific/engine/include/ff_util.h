#ifndef FF_UTIL
#define FF_UTIL

#include <asm/types.h>
#include "rand.h" // IWYU pragma: export

inline UBYTE drand(UBYTE min, UBYTE max){
  return min + rand() / (RAND_MAX / (max - min + 1) + 1);
}

#endif