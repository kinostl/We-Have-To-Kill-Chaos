#ifndef STATE_FS_MENU_H
#define STATE_FS_MENU_H

#include <asm/types.h>
#include <gbdk/platform.h>

void menu_init(void) BANKED;
void menu_update(void) BANKED;

extern UBYTE menu_selection;
extern UBYTE max_menu_selection;
extern UWORD cursor_base_pos;

#endif
