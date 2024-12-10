#ifndef FF_TEXT
#define FF_TEXT

#include <gb/gb.h>

extern BOOLEAN show_message;
void load_battle_message(unsigned char * message) OLDCALL BANKED;
void show_battle_message(void) OLDCALL BANKED;
void close_battle_message(void) OLDCALL BANKED;
#endif