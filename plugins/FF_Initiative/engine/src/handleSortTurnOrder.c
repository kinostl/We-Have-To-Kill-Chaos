#include <stdint.h>
#pragma bank 255

#include "vm.h"
#include "data/game_globals.h"

void handleSortTurnOrder(SCRIPT_CTX * THIS) OLDCALL BANKED {

    int16_t * initative_rolls = (uint16_t *) VM_REF_TO_PTR(VAR_TURN_ORDER_SLOT_1_P1);
    int16_t turn_order[10];
    uint16_t end_of_arr=0;
    int16_t max_val=-1;
    int16_t max_i=0;
    for(uint16_t i = 0; i<10;i++){
        turn_order[i] = -1;
    }

    for(uint16_t i = 0; i<10;i++){
        if(initative_rolls[i] < 0){
            continue;
        }
        max_val = initative_rolls[i];
        max_i=i;

        for (uint16_t j = i; j < 10; j++) {
          if (initative_rolls[j] > max_val) {
            max_val = initative_rolls[j];
          }
        }
        if (max_val > -1) {
          turn_order[end_of_arr] = max_i+1;
          end_of_arr++;
        }
    }

    for(uint16_t i = 0; i<10;i++){
        initative_rolls[i] = turn_order[i];
    }
}