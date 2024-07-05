#include "turn_slots.h"
#include "data/game_globals.h"
#include <asm/types.h>
#include <vm.h>
#pragma bank 255

void prepareHeroTurn(SCRIPT_CTX * THIS) OLDCALL BANKED {
    THIS;
    VM_GLOBAL(VAR_ATTACKER_ID) = VM_GLOBAL(VAR_TURN_ORDER_CURRENT_ACTO);

    struct entity_data *player = &turn_slots[VM_GLOBAL(VAR_ATTACKER_ID)];
    player->ap++;
    VM_GLOBAL(VAR_ATTACKER_AP) = player->ap;
    VM_GLOBAL(VAR_ATTACKER_TYPE) = VM_GLOBAL(VAR_ATTACKER_ID) + 1;
}