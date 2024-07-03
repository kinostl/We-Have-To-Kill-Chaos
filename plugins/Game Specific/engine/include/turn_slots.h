#ifndef FF_TURN_SLOTS
#define FF_TURN_SLOTS
#include <asm/types.h>
#include "entity_data.h"

enum TURN_TAG {PLAYER, ENEMY} ;

void load_attacker(BYTE slot_idx) OLDCALL BANKED;
void load_defender(BYTE slot_idx) OLDCALL BANKED;

void load_player_atk(struct entity_data *player) OLDCALL BANKED;
void load_player_def(struct entity_data *player) OLDCALL BANKED;
void load_enemy_atk(struct entity_data *enemy) OLDCALL BANKED;
void load_enemy_def(struct entity_data *enemy) OLDCALL BANKED;
extern struct entity_data * turn_slots;
#endif