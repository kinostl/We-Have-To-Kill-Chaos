#pragma bank 255

// Palette: 1

#include "gbs_types.h"

BANKREF(palette_1)

const struct palette_t palette_1 = {
    .mask = 0xFF,
    .palette = {
        DMG_PALETTE(DMG_WHITE, DMG_LITE_GRAY, DMG_DARK_GRAY, DMG_BLACK)
    },
    .cgb_palette = {
        CGB_PALETTE(RGB(31, 31, 31), RGB(24, 25, 1), RGB(14, 14, 14), RGB(0, 0, 1)),
        CGB_PALETTE(RGB(31, 29, 18), RGB(31, 28, 1), RGB(31, 13, 1), RGB(0, 0, 1)),
        CGB_PALETTE(RGB(31, 31, 31), RGB(31, 28, 1), RGB(24, 25, 1), RGB(0, 0, 1)),
        CGB_PALETTE(RGB(31, 29, 18), RGB(12, 9, 31), RGB(14, 0, 31), RGB(0, 0, 1)),
        CGB_PALETTE(RGB(31, 31, 31), RGB(17, 31, 1), RGB(17, 22, 31), RGB(0, 0, 1)),
        CGB_PALETTE(RGB(31, 31, 31), RGB(14, 14, 14), RGB(0, 0, 27), RGB(0, 0, 1)),
        CGB_PALETTE(RGB(18, 26, 1), RGB(6, 20, 1), RGB(5, 14, 31), RGB(0, 0, 1)),
        CGB_PALETTE(RGB(28, 31, 24), RGB(15, 29, 10), RGB(4, 14, 11), RGB(0, 0, 1))
    }
};
