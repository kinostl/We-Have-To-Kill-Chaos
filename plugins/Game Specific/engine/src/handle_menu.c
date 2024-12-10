#include "enemy_data.h"
#include "entity_data.h"
#include "extra_data.h"
#include <asm/types.h>
#include <bankdata.h>
#include <data/game_globals.h>
#include <string.h>
#include <ui.h>
#include <vm.h>
#include "hero_data.h"
#include "menu_helper.h"
#include "skill_data.h"
#pragma bank 255

BYTE create_hero_data(hero_data *player, unsigned char *d, BYTE row, BYTE col) OLDCALL BANKED {
  unsigned char *f = d;

  // Fast Text Speed
  *d++ = 0x01;
  *d++ = 1;

  // Set to Name Location
  *d++ = 0x03;
  *d++ = 2 + col;
  *d++ = 2+(row*4);
  // Load Name
  for (int i = 0; i < strlen(player->name); i++) {
    *d++ = player->name[i];
  }

  // Status Effect Area


  // Set to HP Location
  *d++ = 0x03;
  *d++ = 5 + col;
  *d++ = 4+(row*4);
  // HP Here
  if (player->ext.hp < 100) {
    *d++ = ' ';
  }
  if (player->ext.hp < 10) {
    *d++ = ' ';
  }
  d += itoa_format(player->ext.hp, d, 0);

  // Set to AP Location
  *d++ = 0x03;
  *d++ = 5 + col;
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

void loadPartyMenuOffset(BYTE col) BANKED {
  unsigned char *d = ui_text_data;
  for (int i = 0; i < 4; i++) {
    d += create_hero_data(&hero_slots[i], d, i, col);
    *d-- = '\n';
  }
}

void loadPartyMenu() BANKED {
  loadPartyMenuOffset(0);
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

BYTE load_menu_item(const unsigned char * skill_name, unsigned char *d) OLDCALL BANKED {
  BYTE str_len = strlen(skill_name);
  for (int i = 0; i < str_len; i++) {
    *d++ = skill_name[i];
  }
  return str_len;
}

void loadHeroMenu(hero_data * player) BANKED {
  skill_data skill;
  unsigned char *d = ui_text_data;

  d+=create_hero_data(player, d, 0, 0);
  *d-- = '\n';
  *d++ = 0x01;
  *d++ = 1;
  *d++ = 0x03;
  *d++ = 2;
  *d++ = 6;

  for (int i = 0; i < 4; i++) {
    load_skill(&skill, player->ext.skills[i]);
    d += load_menu_item(skill.name, d);
    *d++ = '\n';
    d += load_stars(skill.cost, d);
    *d++ = '\n';
  }
  const char r_menu[25] = "Item >\nMagic>\nBlock-\nRun";
  for (int i = 0; i < strlen(r_menu); i++) {
    *d++ = r_menu[i];
  }
  *d++='\0';
}