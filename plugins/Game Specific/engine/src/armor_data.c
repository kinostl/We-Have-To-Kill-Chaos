#include "armor_data.h"
#include "class_data.h"
#include "enums.h"
#include <string.h>
#pragma bank 255

const armor_data armor_db[] = {
    [NUDE] =
        {
            .id = NUDE,
            .type = UNARMORED,
            .defense = 0,
            .weight = 0,
            .price = 0,
            .classes = ALL_JOBS,
        },
    [CLOTH] =
        {
            .id = CLOTH,
            .type = ARMOR,
            .defense = 1,
            .weight = 2,
            .price = 10,
            .classes = ALL_JOBS,
        },
    [WOOD_ARMOR] =
        {
            .id = WOOD_ARMOR,
            .type = ARMOR,
            .defense = 4,
            .weight = 8,
            .price = 50,
            .classes = ALL_MELEE | RED_MAGE,
        },
    [CHAIN_ARMOR] =
        {
            .id = CHAIN_ARMOR,
            .type = ARMOR,
            .defense = 15,
            .weight = 15,
            .price = 80,
            .classes = FIGHTER | RED_MAGE,
        },
    [CAP] =
        {
            .id = CAP,
            .type = HELMET,
            .defense = 1,
            .weight = 1,
            .price = 80,
            .classes = ALL_JOBS,
        },
};

void load_armor(armor_data *armor, ARMOR_TYPE armor_type) BANKED {
  memcpy(armor, &armor_db[armor_type], sizeof(armor_data));
}