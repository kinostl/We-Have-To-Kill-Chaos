#include <asm/types.h>
#include "vm.h"
#include "vm_ui.h"

void makeBox(SCRIPT_CTX * THIS) OLDCALL BANKED{
    UBYTE x = *(UBYTE *) VM_REF_TO_PTR(FN_ARG0);
    UBYTE y = *(UBYTE *) VM_REF_TO_PTR(FN_ARG1);
    UBYTE w = *(UBYTE *) VM_REF_TO_PTR(FN_ARG2);
    UBYTE h = *(UBYTE *) VM_REF_TO_PTR(FN_ARG3);
    // UBYTE color = *(UBYTE *) VM_REF_TO_PTR(FN_ARG4);
    // UBYTE opts = *(UBYTE *) VM_REF_TO_PTR(FN_ARG5);

    UBYTE color = 1;
    UBYTE options = 0 | 1;

    vm_overlay_clear(THIS, x, y, w, h, color, options);
}