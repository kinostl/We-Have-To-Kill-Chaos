#pragma bank 255

// Background: overworld

#include "gbs_types.h"
#include "data/bg_overworld_tileset.h"
#include "data/bg_overworld_cgb_tileset.h"
#include "data/bg_overworld_tilemap.h"
#include "data/bg_overworld_tilemap_attr.h"

BANKREF(bg_overworld)

const struct background_t bg_overworld = {
    .width = 87,
    .height = 106,
    .tileset = TO_FAR_PTR_T(bg_overworld_tileset),
    .cgb_tileset = TO_FAR_PTR_T(bg_overworld_cgb_tileset),
    .tilemap = TO_FAR_PTR_T(bg_overworld_tilemap),
    .cgb_tilemap_attr = TO_FAR_PTR_T(bg_overworld_tilemap_attr)
};
