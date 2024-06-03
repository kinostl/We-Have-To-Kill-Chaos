.module script_2

.include "vm.i"
.include "data/game_globals.i"

.area _CODE_255

.SCRIPT_ARG_0_VARIABLE = -3
.SCRIPT_ARG_INDIRECT_1_VARIABLE = -4

___bank_script_2 = 255
.globl ___bank_script_2

_script_2::
        ; Switch Variable
        VM_SWITCH               .SCRIPT_ARG_0_VARIABLE, 1, 0
        .dw 1, 1$

        VM_JUMP                 2$
        ; case 1:
1$:
        ; Variable Set To
        VM_SET_INDIRECT         .SCRIPT_ARG_INDIRECT_1_VARIABLE, VAR_ENEMY_1_HP

        VM_JUMP                 2$
2$:

        VM_RET_FAR_N            2
