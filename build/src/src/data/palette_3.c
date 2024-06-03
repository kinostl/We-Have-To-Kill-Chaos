#pragma bank 255

// Palette: 3

#include "gbs_types.h"

BANKREF(palette_3)

const struct palette_t palette_3 = {
    .mask = 0xFF,
    .palette = {
        DMG_PALETTE(DMG_WHITE, DMG_WHITE, DMG_LITE_GRAY, DMG_BLACK),
        DMG_PALETTE(DMG_WHITE, DMG_WHITE, DMG_DARK_GRAY, DMG_BLACK)
    },
    .cgb_palette = {
        CGB_PALETTE(RGB(31, 31, 31), RGB(31, 31, 31), RGB(31, 29, 18), RGB(31, 13, 1)),
        CGB_PALETTE(RGB(3, 18, 31), RGB(3, 18, 31), RGB(31, 31, 1), RGB(24, 25, 1)),
        CGB_PALETTE(RGB(31, 31, 31), RGB(31, 31, 31), RGB(31, 29, 18), RGB(31, 13, 1)),
        CGB_PALETTE(RGB(31, 31, 31), RGB(31, 31, 31), RGB(31, 29, 18), RGB(31, 13, 1)),
        CGB_PALETTE(RGB(31, 31, 31), RGB(31, 31, 31), RGB(31, 29, 18), RGB(31, 13, 1)),
        CGB_PALETTE(RGB(31, 31, 31), RGB(31, 31, 31), RGB(31, 29, 18), RGB(31, 13, 1)),
        CGB_PALETTE(RGB(31, 31, 31), RGB(31, 31, 31), RGB(31, 29, 18), RGB(31, 13, 1)),
        CGB_PALETTE(RGB(29, 29, 29), RGB(29, 29, 29), RGB(14, 14, 14), RGB(0, 0, 1))
    }
};
