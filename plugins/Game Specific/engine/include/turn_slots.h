#ifndef FF_TURN_SLOTS
#define FF_TURN_SLOTS
#include <asm/types.h>
#include <gb/gb.h>
BANKREF_EXTERN(ff_turn_slots)

#include "valloc.h" // IWYU pragma: keep

enum TURN_TAG {PLAYER, ENEMY} ;

struct turn_slot {
  enum TURN_TAG tag;
  void * entity;
};

void valloc_turn_slots(void) OLDCALL BANKED;
void load_attacker(BYTE slot_idx) OLDCALL BANKED;
void load_defender(BYTE slot_idx) OLDCALL BANKED;

extern struct turn_slot * turn_slots;
#endif