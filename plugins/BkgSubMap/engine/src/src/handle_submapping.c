#include "gbs_types.h"
#include <gb/hardware.h>
#pragma bank 255

#include <stdint.h>
#include "system.h"
#include "vm.h"
#include <gb/gb.h>
#include "data_manager.h"
#include "ui.h"

// typedef struct set_submap_params_t {
//     int x;
//     int _pad0;
//     int y;
//     int _pad1;
//     int w;
//     int _pad2;
//     int h;
//     int _pad3;
//     int scene_x;
//     int _pad4;
//     int scene_y;
// } set_submap_params_t;

// void set_xy_bkg_submap(const unsigned char * source, int bank, int width, int x, int y, int w, int h) OLDCALL;

// void vm_background_set_submap_ex(SCRIPT_CTX * THIS, uint16_t params_idx) OLDCALL BANKED {
//     set_submap_params_t * params = VM_REF_TO_PTR(params_idx);
//     UWORD offset = (params->scene_y * image_tile_width) + params->scene_x;
// #ifdef CGB
//     if (_is_CGB) {
//         VBK_REG = 1;
//         set_xy_bkg_submap(image_attr_ptr + offset, image_attr_bank, image_tile_width, params->x, params->y, params->w, params->h);
//         VBK_REG = 0;
//     }
// #endif
//     set_xy_bkg_submap(image_ptr + offset, image_bank, image_tile_width, params->x, params->y, params->w, params->h);
// }

void copyBkgToBkg(SCRIPT_CTX * THIS) OLDCALL BANKED {

    const uint16_t DES_X = *(uint16_t *) VM_REF_TO_PTR(FN_ARG5);
    const uint16_t DES_Y = *(uint16_t *) VM_REF_TO_PTR(FN_ARG4);
    const uint16_t W1 = *(uint16_t *) VM_REF_TO_PTR(FN_ARG3);
    const uint16_t H1 = *(uint16_t *) VM_REF_TO_PTR(FN_ARG2);
    const uint16_t SRC_X = *(uint16_t *) VM_REF_TO_PTR(FN_ARG1);
    const uint16_t SRC_Y = *(uint16_t *) VM_REF_TO_PTR(FN_ARG0);

    // set_bkg_submap(SRC_X, SRC_Y, W1, H1, const uint8_t *map, uint8_t map_w)
    
    uint8_t tile;
    for(int j = 0; j< H1 ; j++) {
        for(int i = 0 ; i < W1; i++) {
            VBK_REG = 1;
            tile = get_bkg_tile_xy(SRC_X + i, SRC_Y + j);
            set_bkg_tile_xy(DES_X + i, DES_Y + j, tile);
         
            VBK_REG = 0;
            tile = get_bkg_tile_xy(SRC_X + i, SRC_Y + j);
            set_bkg_tile_xy(DES_X + i, DES_Y + j, tile);
        }
    }
}

void copyBkgAttrToBkgAttr(SCRIPT_CTX * THIS) OLDCALL BANKED {

    const uint16_t DES_X = *(uint16_t *) VM_REF_TO_PTR(FN_ARG5);
    const uint16_t DES_Y = *(uint16_t *) VM_REF_TO_PTR(FN_ARG4);
    const uint16_t W1 = *(uint16_t *) VM_REF_TO_PTR(FN_ARG3);
    const uint16_t H1 = *(uint16_t *) VM_REF_TO_PTR(FN_ARG2);
    const uint16_t SRC_X = *(uint16_t *) VM_REF_TO_PTR(FN_ARG1);
    const uint16_t SRC_Y = *(uint16_t *) VM_REF_TO_PTR(FN_ARG0);

    
    uint8_t tile;
    VBK_REG = 1;
    tile = get_bkg_tile_xy(SRC_X, SRC_Y);
    for(int j = 0; j< H1 ; j++) {
        for(int i = 0 ; i < W1; i++) {
            set_bkg_tile_xy(DES_X + i, DES_Y + j, tile);
        }
    }
    VBK_REG = 0;
}

void copyWinToBkg(SCRIPT_CTX * THIS) OLDCALL BANKED {

    const uint16_t DES_X = *(uint16_t *) VM_REF_TO_PTR(FN_ARG5);
    const uint16_t DES_Y = *(uint16_t *) VM_REF_TO_PTR(FN_ARG4);
    const uint16_t W1 = *(uint16_t *) VM_REF_TO_PTR(FN_ARG3);
    const uint16_t H1 = *(uint16_t *) VM_REF_TO_PTR(FN_ARG2);
    const uint16_t SRC_X = *(uint16_t *) VM_REF_TO_PTR(FN_ARG1);
    const uint16_t SRC_Y = *(uint16_t *) VM_REF_TO_PTR(FN_ARG0);

    // set_bkg_submap(SRC_X, SRC_Y, W1, H1, const uint8_t *map, uint8_t map_w)
    
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