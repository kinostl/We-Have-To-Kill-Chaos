#include "entity_data.h"
#include "extra_data.h"
#include <data/game_globals.h>
#pragma bank 255
#include "rand.h" // IWYU pragma: keep
#include "action_definitions.h"

#define BASE_PLAYER_EVADE 48
#define TURN_ORDER_COUNT 10

void turn_rollInitiative(void) BANKED{
    for (int i = 0; i < 10; i++) {
      turn_order[i] = -1;
    }

    for (int i = 0; i < 10; i++) {
      entity_data * entity = &turn_slots[i];
      if (!entity->alive)
        continue;
      BYTE *initiative_slot = &turn_order[i];
      *initiative_slot = rand() % entity->max_hp;
      *initiative_slot += entity->evade;
      if (i < 4) {
        *initiative_slot += BASE_PLAYER_EVADE;
      }
    }
}

#define initiative_rolls turn_order
BYTE turn_sortInitiative(void) BANKED{
    BYTE initiative_order[TURN_ORDER_COUNT];
    BYTE end_of_arr=0;
    int16_t max_val=-1;
    int16_t max_i=0;

    for(BYTE i = 0; i<TURN_ORDER_COUNT;i++){
        initiative_order[i] = -1;
    }

    for(BYTE i = 0; i<TURN_ORDER_COUNT;i++){
        if(initiative_rolls[i] < 0){
            continue;
        }
        max_val = initiative_rolls[i];
        max_i=i;

        for (BYTE j = i; j < TURN_ORDER_COUNT; j++) {
          if (initiative_rolls[j] > max_val) {
            max_val = initiative_rolls[j];
          }
        }
        if (max_val > -1) {
          initiative_order[end_of_arr] = max_i;
          end_of_arr++;
        }
    }

    for(BYTE i = 0; i<TURN_ORDER_COUNT;i++){
        turn_order[i] = initiative_order[i];
    }

    return end_of_arr;
}
#undef initiative_rolls

void attacker_prepareNextTurn_Hero() BANKED {
    VM_GLOBAL(VAR_ATTACKER_ID) = VM_GLOBAL(VAR_TURN_ORDER_CURRENT_ACTO);

    entity_data *player = &turn_slots[VM_GLOBAL(VAR_ATTACKER_ID)];
    weapon_data *weapon = &weapon_slots[VM_GLOBAL(VAR_ATTACKER_ID)];
    player->ap++;
    VM_GLOBAL(VAR_ATTACKER_AP) = player->ap;
    VM_GLOBAL(VAR_ATTACKER_TYPE) = VM_GLOBAL(VAR_ATTACKER_ID) + 1;

    VM_GLOBAL(VAR_1WEAPON_TYPE) = weapon->type;
    VM_GLOBAL(VAR_1WEAPON_COLORS) = weapon->color;
}

void attacker_prepareNextTurn_Enemy() BANKED{}