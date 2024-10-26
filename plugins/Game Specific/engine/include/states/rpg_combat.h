#ifndef STATE_RPG_COMBAT
#define STATE_RPG_COMBAT
#include <asm/types.h>

typedef enum {
  RPG_SELECT_MENU_ITEM_MODE,
  RPG_SELECT_ENEMY_MODE,
  RPG_SELECT_ALLY_MODE,
  RPG_ENEMY_MODE,
  RPG_LOOP_MODE,
} RPG_MENU_MODE;

extern RPG_MENU_MODE rpg_menu_mode;

#endif