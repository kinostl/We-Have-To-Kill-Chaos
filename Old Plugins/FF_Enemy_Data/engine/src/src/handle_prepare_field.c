#pragma bank 255

#include "data/game_globals.h"
#include "vm.h"
#include "handle_prepare_field.h"
#include "enemy_data.h"

const enemy_info enemy_db[1] = {
  {"IMP", 8}
};

void handleSetEnemyData(SCRIPT_CTX *THIS) OLDCALL BANKED {
  THIS;
  //uint16_t *enemy_hp;
  uint16_t enemyslot = GET_GLOBAL_VAL(FN_ARG1);
  uint16_t enemy_type = GET_GLOBAL_VAL(FN_ARG0);

  switch (enemyslot) {
  case 1:
    //enemy_hp = GET_GLOBAL_REF(VAR_ENEMY_1_HP);
    break;
  // case 2:
  //   enemy_hp = (uint16_t *)VM_REF_TO_PTR(VAR_ENEMY_2_HP);
  //   break;
  // case 3:
  //   enemy_hp = (uint16_t *)VM_REF_TO_PTR(VAR_ENEMY_3_HP);
  //   break;
  // case 4:
  //   enemy_hp = (uint16_t *)VM_REF_TO_PTR(VAR_ENEMY_4_HP);
  //   break;
  // case 5:
  //   enemy_hp = (uint16_t *)VM_REF_TO_PTR(VAR_ENEMY_5_HP);
  //   break;
  // case 6:
  //   enemy_hp = (uint16_t *)VM_REF_TO_PTR(VAR_ENEMY_6_HP);
  //   break;
  default:
    return;
  }

  //*enemy_hp = enemy_db[0].hp;
}