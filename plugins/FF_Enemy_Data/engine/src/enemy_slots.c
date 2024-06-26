#pragma bank 255
#include "data/game_globals.h"
#include "data/max_global_vars.h"
#include "enemy_data.h"
#include "vm.h"
#include "math.h"
#include <gb/crash_handler.h>
BANKREF(ff_enemy_slots)

WORD end_of_globals = MAX_GLOBAL_VARS;

void* extra_reserve(SCRIPT_CTX* THIS, WORD size) OLDCALL BANKED
{
    void * end_of = VM_REF_TO_PTR(end_of_globals + 1);
    end_of_globals = end_of_globals + DIV_16(size);
    if(end_of_globals > 512){
        __HandleCrash();
    }
    return end_of;
}

void extra_free(SCRIPT_CTX* THIS, WORD size) OLDCALL BANKED
{
    THIS;
    end_of_globals = end_of_globals - DIV_16(size);
    if(end_of_globals < MAX_GLOBAL_VARS){
        end_of_globals = MAX_GLOBAL_VARS;
    }
}

void handleEnemySlots(SCRIPT_CTX* THIS) OLDCALL BANKED
{
    struct enemy_info* enemy_slots = extra_reserve(THIS, sizeof(struct enemy_info) * 6);
    enemy_slots[0] = enemy_db[IMP];
    enemy_slots[1] = enemy_db[WOLF];
    enemy_slots[2] = enemy_db[MADPONY];
}

void finishBattle(SCRIPT_CTX* THIS) OLDCALL BANKED
{
    extra_free(THIS, sizeof(struct enemy_info) * 6);
}