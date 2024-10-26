#include "extra_data.h"
#include "data/game_globals.h"
#include "weapon_data.h"
#include <asm/types.h>
#include <vm.h>
#pragma bank 255

void prepareHeroTurn(SCRIPT_CTX * THIS) OLDCALL BANKED {
    THIS;
    VM_GLOBAL(VAR_ATTACKER_ID) = VM_GLOBAL(VAR_TURN_ORDER_CURRENT_ACTO);

    entity_data *player = &turn_slots[VM_GLOBAL(VAR_ATTACKER_ID)];
    weapon_data *weapon = &weapon_slots[VM_GLOBAL(VAR_ATTACKER_ID)];
    player->ap++;
    VM_GLOBAL(VAR_ATTACKER_AP) = player->ap;
    VM_GLOBAL(VAR_ATTACKER_TYPE) = VM_GLOBAL(VAR_ATTACKER_ID) + 1;

    VM_GLOBAL(VAR_1WEAPON_TYPE) = weapon->type;
    VM_GLOBAL(VAR_1WEAPON_COLORS) = weapon->color;
}