#pragma bank 255

#include <gb/hardware.h>
#include <stdint.h>
#include "vm.h"
#include <gb/gb.h>


void copyWinToBkg(SCRIPT_CTX * THIS) OLDCALL BANKED {

    const uint16_t DES_X = *(uint16_t *) VM_REF_TO_PTR(FN_ARG5);
    const uint16_t DES_Y = *(uint16_t *) VM_REF_TO_PTR(FN_ARG4);
    const uint16_t W1 = *(uint16_t *) VM_REF_TO_PTR(FN_ARG3);
    const uint16_t H1 = *(uint16_t *) VM_REF_TO_PTR(FN_ARG2);
    const uint16_t SRC_X = *(uint16_t *) VM_REF_TO_PTR(FN_ARG1);
    const uint16_t SRC_Y = *(uint16_t *) VM_REF_TO_PTR(FN_ARG0);

    uint8_t tile;
    for(int j = 0; j< H1 ; j++) {
        for(int i = 0 ; i < W1; i++) {
            VBK_REG = 1;
            tile = get_win_tile_xy(SRC_X + i, SRC_Y + j);
            set_bkg_tile_xy(DES_X + i, DES_Y + j, tile);
         
            VBK_REG = 0;
            tile = get_win_tile_xy(SRC_X + i, SRC_Y + j);
            set_bkg_tile_xy(DES_X + i, DES_Y + j, tile);
        }
    }
}