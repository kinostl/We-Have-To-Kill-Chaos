#pragma bank 255

// Background: battle_concept

#include "gbs_types.h"
#include "data/bg_battle_concept_tileset.h"
#include "data/bg_battle_concept_tilemap.h"
#include "data/bg_battle_concept_tilemap_attr.h"

BANKREF(bg_battle_concept)

const struct background_t bg_battle_concept = {
    .width = 32,
    .height = 32,
    .tileset = TO_FAR_PTR_T(bg_battle_concept_tileset),
    .cgb_tileset = { NULL, NULL },
    .tilemap = TO_FAR_PTR_T(bg_battle_concept_tilemap),
    .cgb_tilemap_attr = TO_FAR_PTR_T(bg_battle_concept_tilemap_attr)
};
