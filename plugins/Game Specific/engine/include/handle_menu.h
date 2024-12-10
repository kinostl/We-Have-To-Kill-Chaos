#ifndef FF_MENU_HANDLER
#define FF_MENU_HANDLER
#include "hero_data.h"
#include <asm/types.h>

void loadHeroMenu(hero_data * player) BANKED;
void loadPartyMenu(void) BANKED;
void loadPartyMenuOffset(BYTE col) BANKED;
#endif