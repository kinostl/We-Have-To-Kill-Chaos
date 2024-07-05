#include "entity_data.h"
#include "turn_slots.h"
#include <asm/types.h>
#include <data/game_globals.h>
#include <gb/gb.h>
#include <string.h>
#include <vm.h>
#include <ui.h>
#pragma bank 255


extern UBYTE _itoa_fmt_len;
UBYTE itoa_fmt(INT16 v, UBYTE * d) OLDCALL BANKED PRESERVES_REGS(b, c);

inline UBYTE itoa_format(INT16 v, UBYTE * d, UBYTE dlen) {
    _itoa_fmt_len = dlen;
    UBYTE len = itoa_fmt(v, d);
    return len;
}

void loadHeroData(SCRIPT_CTX *THIS) OLDCALL BANKED {
  THIS;
  struct entity_data *player = &turn_slots[VM_GLOBAL(VAR_ATTACKER_ID)];
  unsigned char * d = ui_text_data;

  // Fast Text Speed
  *d++=0x01;
  *d++=1;

  // Set to Name Location
  *d++=0x03;
  *d++=2;
  *d++=2;
  // Load Name
  for (int i = 0; i < strlen(player->name); i++) {
    *d++ = player->name[i];
  }
  // Set to HP Location
  *d++ = 0x03;
  *d++ = 5;
  *d++ = 3;
  // HP Here
  if(player->hp < 100){
    *d++=' ';
  }
  if(player->hp < 10){
    *d++ = ' ';
  }
  d+=itoa_format(player->hp, d, 0);

  // Set to AP Location
  *d++ = 0x03;
  *d++ = 5;
  *d++ = 4;
  // AP Stars here
  for (int i = 0; i < 7; i++) {
    if (i == 3) {
      *d++ = '\n';
    } else if (i < player->ap) {
      *d++ = '+';
    } else {
      *d++ = '-';
    }
  }
  *d++='\0';
}

// TODO This is where you left off - Trying to make this menu a bit more dynamic by making use of the fact that skills are stored in the entity data now.
// void loadHeroMenu(SCRIPT_CTX *THIS) OLDCALL BANKED {
//   struct entity_data *player = &turn_slots[VM_GLOBAL(VAR_ATTACKER_ID)];
//   unsigned char * d = ui_text_data;
//   d+=load_menu_item(player->skills[0]);
//   d+=load_menu_item(player->skills[1]);
//   d+=load_menu_item(player->skills[2]);
//   d+=load_menu_item(player->skills[3]);
// }