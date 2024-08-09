#include "load_font_into_bg.h"
#include <asm/types.h>
#include <gb/gb.h>
#include <string.h>
#include <vm.h>
#pragma bank 255

inline void screenf(unsigned char *d, UBYTE x, UBYTE y, UBYTE w, UBYTE h) {
  for (UBYTE i = 0; i < strlen(d); i++) {
    // if(d[i] == '\n'){
    //     for(int w=0;w<wrap;w++){
    //         d[i+w] = ReadBankedUBYTE(bg_font.recode_table + ' ',
    //         bg_font_bank); d[i+w] += start_of_bkg_vram;
    //     }
    //     continue;
    // }
    UBYTE j = d[i];
    d[i] = ReadBankedUBYTE(bg_font.recode_table + j, bg_font_bank);
    d[i] += start_of_bkg_vram;
  }

  set_bkg_tiles(x, y, w, h, d);
}

void loadEquipMenu(SCRIPT_CTX *THIS) OLDCALL BANKED {
  THIS;
  unsigned char opts[12] = "Choose Best";
  screenf(opts, 1, 1, strlen(opts), 1);

  unsigned char label[6] = "Equip";
  screenf(label, 14, 1, strlen(label), 1);

  unsigned char name[12] = "Monk Fred";
  screenf(name, 8, 3, strlen(name), 1);
  unsigned char weapon[12] = "W Nunchucks";
  weapon[1] = 150;
  screenf(weapon, 8, 5, strlen(weapon), 1);
  unsigned char armor[12] = "A Cloth";
  armor[1] = 150;
  screenf(armor, 8, 7, strlen(armor), 1);
  unsigned char exp[12] = "+++--  Lv 2";
  screenf(exp, 8, 9, strlen(exp), 1);

  unsigned char hp[6] = " 6/ 9";
  screenf(hp, 1, 9, strlen(hp), 1);

  unsigned char strength[9] = "STR   10";
  unsigned char agility[9] = "AGL    8";
  unsigned char intel[9] = "INT    1";
  unsigned char stamina[9] = "STA   15";
  unsigned char luck[9] = "LCK    8";

  screenf(strength, 1, 12, strlen(strength), 1);
  screenf(agility, 1, 13, strlen(agility), 1);
  screenf(intel, 1, 14, strlen(intel), 1);
  screenf(stamina, 1, 15, strlen(stamina), 1);
  screenf(luck, 1, 16, strlen(luck), 1);

  unsigned char attack[9] = "ATK   10";
  unsigned char accuracy[9] = "ACC   28";
  unsigned char defense[9] = "DEF    1";
  unsigned char evasion[9] = "EVA   15";
  screenf(attack, 11, 12, strlen(attack), 1);
  screenf(accuracy, 11, 13, strlen(accuracy), 1);
  screenf(defense, 11, 14, strlen(defense), 1);
  screenf(evasion, 11, 15, strlen(evasion), 1);
}