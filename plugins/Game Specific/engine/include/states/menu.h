#ifndef STATE_FS_MENU_H
#define STATE_FS_MENU_H

#include <gbdk/platform.h>

void menu_init(void) BANKED;
void menu_update(void) BANKED;

extern UBYTE menu_selection;

#endif
