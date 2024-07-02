#include <stdint.h>
#include "vm.h"
#include "data/game_globals.h"

#pragma bank 255

#define TURN_ORDER_COUNT 10
void handleSortTurnOrder(SCRIPT_CTX * THIS) OLDCALL BANKED {

    int16_t * initative_rolls = (int16_t *) VM_REF_TO_PTR(VAR_TURN_ORDER_SLOT_1_P1);
    int16_t turn_order[TURN_ORDER_COUNT];
    uint16_t end_of_arr=0;
    int16_t max_val=-1;
    int16_t max_i=0;

    for(uint16_t i = 0; i<TURN_ORDER_COUNT;i++){
        turn_order[i] = -1;
    }

    for(uint16_t i = 0; i<TURN_ORDER_COUNT;i++){
        if(initative_rolls[i] < 0){
            continue;
        }
        max_val = initative_rolls[i];
        max_i=i;

        for (uint16_t j = i; j < TURN_ORDER_COUNT; j++) {
          if (initative_rolls[j] > max_val) {
            max_val = initative_rolls[j];
          }
        }
        if (max_val > -1) {
          turn_order[end_of_arr] = max_i+1;
          end_of_arr++;
        }
    }

    for(uint16_t i = 0; i<TURN_ORDER_COUNT;i++){
        initative_rolls[i] = turn_order[i];
    }
}