#ifndef FF_TURN_SLOTS
#define FF_TURN_SLOTS
#include <asm/types.h>
#include "entity_data.h"
#include "vm.h"

enum TURN_TAG {PLAYER, ENEMY} ;

void load_attacker(SCRIPT_CTX * THIS) OLDCALL BANKED;
void load_defender(SCRIPT_CTX * THIS) OLDCALL BANKED;

void load_player_atk(entity_data * player) OLDCALL BANKED;
void load_player_def(entity_data * player) OLDCALL BANKED;
void load_enemy_atk(entity_data * enemy) OLDCALL BANKED;
void load_enemy_def(entity_data * enemy) OLDCALL BANKED;
void load_name(entity_data * entity) OLDCALL BANKED;
#endif