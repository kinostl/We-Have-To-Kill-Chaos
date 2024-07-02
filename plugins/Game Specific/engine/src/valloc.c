#include <vm.h>
#include "valloc.h"
#include "data/max_global_vars.h"

#pragma bank 255

void * valloc_ptr = &VM_GLOBAL(MAX_GLOBAL_VARS + 1);
void * valloc(WORD size) OLDCALL BANKED{
    void * ret_ptr = &valloc_ptr;
    valloc_ptr+=size;
    return ret_ptr;
}

// Returns next greater multiple of 8
// int RoundUp(int& x)
// {
//     return ((x + 7) & (-8));
// }
