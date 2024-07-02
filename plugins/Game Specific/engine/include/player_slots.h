#ifndef FF_PLAYER_SLOTS
#define FF_PLAYER_SLOTS

#include "vm.h" // IWYU pragma: keep
#include <asm/types.h>
BANKREF_EXTERN(ff_player_slots)

#include "entity_data.h"

struct player_slot {
  BYTE slot_id;
  BYTE hp;
  BYTE ap;
  BOOLEAN alive;
  // TODO str dex etc
  struct entity_data info; //substats
};

void initialize_player_slot(struct player_slot * slot) OLDCALL BANKED;

void load_player_atk(struct player_slot * player) OLDCALL BANKED;
void load_player_def(struct player_slot * player) OLDCALL BANKED;
extern struct player_slot * player_slots;
#endif