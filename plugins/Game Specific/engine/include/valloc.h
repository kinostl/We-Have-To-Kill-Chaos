#ifndef FF_EVENT_VALLOC
#define FF_EVENT_VALLOC

#include <asm/types.h>
#include <gb/gb.h>
BANKREF_EXTERN(ff_event_valloc)

extern void * valloc_ptr;
void * valloc(WORD size) OLDCALL BANKED;

#endif