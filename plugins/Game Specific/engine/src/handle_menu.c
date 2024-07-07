#include "enemy_data.h"
#include "entity_data.h"
#include "turn_slots.h"
#include <asm/types.h>
#include <data/game_globals.h>
#include <gb/gb.h>
#include <string.h>
#include <ui.h>
#include <vm.h>
#pragma bank 255

extern UBYTE _itoa_fmt_len;
UBYTE itoa_fmt(INT16 v, UBYTE *d) OLDCALL BANKED PRESERVES_REGS(b, c);

inline UBYTE itoa_format(INT16 v, UBYTE *d, UBYTE dlen) {
  _itoa_fmt_len = dlen;
  UBYTE len = itoa_fmt(v, d);
  return len;
}

BYTE create_hero_data(struct entity_data *player, unsigned char *d, BYTE row) OLDCALL BANKED {
  unsigned char *f = d;

  // Fast Text Speed
  *d++ = 0x01;
  *d++ = 1;

  // Set to Name Location
  *d++ = 0x03;
  *d++ = 2;
  *d++ = 2+(row*4);
  // Load Name
  for (int i = 0; i < strlen(player->name); i++) {
    *d++ = player->name[i];
  }

  // Status Effect Area


  // Set to HP Location
  *d++ = 0x03;
  *d++ = 5;
  *d++ = 4+(row*4);
  // HP Here
  if (player->hp < 100) {
    *d++ = ' ';
  }
  if (player->hp < 10) {
    *d++ = ' ';
  }
  d += itoa_format(player->hp, d, 0);

  // Set to AP Location
  *d++ = 0x03;
  *d++ = 5;
  *d++ = 5+(row*4);
  // AP Stars here
  for (int i = 0; i < 3; i++) {
    if (i < player->ap) {
      *d++ = '+';
    } else {
      *d++ = '-';
    }
  }

  *d++ = '\0';
  return d - f;
}

void loadPartyMenu(SCRIPT_CTX *THIS) OLDCALL BANKED {
  THIS;
  unsigned char *d = ui_text_data;
  for (int i = 0; i < 4; i++) {
    d += create_hero_data(&turn_slots[i], d, i);
    *d-- = '\n';
  }
}

void load_skill_name(BYTE skill_id, char *d) OLDCALL BANKED {
  switch (skill_id) {
  case FIGHT:
    strcpy(d, "Fight");
    break;
  case SHIELD:
    strcpy(d, "Shield");
    break;
  case OVERSOUL:
    strcpy(d, "OvrSol");
    break;
  case GOBLIN_PUNCH:
    strcpy(d, "GobPun");
    break;
  case HOWL:
    strcpy(d, "Howl");
    break;
  case THRASH:
    strcpy(d, "Thrash");
    break;
  case FIRE:
    strcpy(d, "Fire");
    break;
  case ICE:
    strcpy(d, "Ice");
    break;
  case HARM:
    strcpy(d, "Harm");
    break;
  case HEAL:
    strcpy(d, "Heal");
    break;
  default:
  case BLANK:
    strcpy(d, "");
    break;
  }
}

BYTE load_stars(BYTE star_length, unsigned char *d)OLDCALL BANKED{
    if(star_length == 0) return 0;
    char star='+';
    if(star_length < 0){
        star='-';
        star_length *= -1;
    }
    for(int i=0;i<star_length;i++){
        *d++ = star;
    }
    return star_length;
}

BYTE load_menu_item(BYTE skill_id, unsigned char *d) OLDCALL BANKED {
  char skill_str[7];
  load_skill_name(skill_id, skill_str);
  BYTE str_len = strlen(skill_str);
  for (int i = 0; i < str_len; i++) {
    *d++ = skill_str[i];
  }
  return str_len;
}

void loadHeroMenu(SCRIPT_CTX *THIS) OLDCALL BANKED {
  THIS;
  struct entity_data *player = &turn_slots[VM_GLOBAL(VAR_ATTACKER_ID)];
  unsigned char *d = ui_text_data;
  d+=create_hero_data(player, d, 0);
  *d-- = '\n';
  *d++ = 0x01;
  *d++ = 1;
  *d++ = 0x03;
  *d++ = 2;
  *d++ = 6;
  for (int i = 0; i < 4; i++) {
    d += load_menu_item(player->skills[i], d);
    *d++ = '\n';
    d += load_stars(player->skill_costs[i], d);
    *d++ = '\n';
  }
  const char r_menu[25] = "Item >\nMagic>\nBlock-\nRun";
  for (int i = 0; i < strlen(r_menu); i++) {
    *d++ = r_menu[i];
  }
  *d++='\0';
}