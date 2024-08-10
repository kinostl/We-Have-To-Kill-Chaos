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

  unsigned char name[7] = "Fred";
  screenf(name, 1, 1, strlen(name), 1);

  unsigned char hp[11] = "HP 999/999";
  screenf(hp, 9, 1, strlen(hp), 1);

  unsigned char weapon[12] = "W Nunchucks";
  weapon[1] = 150;
  screenf(weapon, 8, 4, strlen(weapon), 1);
  unsigned char armor[12] = "A Cloth";
  armor[1] = 150;
  screenf(armor, 8, 6, strlen(armor), 1);

unsigned char lv_label[3] = "Lv";
  screenf(lv_label, 1, 15, strlen(lv_label), 1);
  unsigned char total_exp_label[]="EXP";
  screenf(total_exp_label, 5, 15, strlen(total_exp_label), 1);
  unsigned char next_exp_label[]="NxtLv";
  screenf(next_exp_label, 13, 15, strlen(next_exp_label), 1);

  unsigned char lv[]="49";
  unsigned char total_exp[]="956841";
  unsigned char next_exp[]=" 32800";

  screenf(lv, 1, 16, strlen(lv), 1);
  screenf(total_exp, 5, 16, strlen(total_exp), 1);
  screenf(next_exp, 13, 16, strlen(next_exp), 1);


  unsigned char strength[9] = "STR   10";
  unsigned char agility[9] = "AGL    8";
  unsigned char intel[9] = "INT    1";
  unsigned char stamina[9] = "STA   15";
  unsigned char luck[9] = "LCK    8";

  screenf(strength, 1, 9, strlen(strength), 1);
  screenf(agility, 1, 10, strlen(agility), 1);
  screenf(intel, 1, 11, strlen(intel), 1);
  screenf(stamina, 1, 12, strlen(stamina), 1);
  screenf(luck, 1, 13, strlen(luck), 1);

  unsigned char attack[9] = "ATK   10";
  unsigned char accuracy[9] = "ACC   28";
  unsigned char defense[9] = "DEF    1";
  unsigned char evasion[9] = "EVA   15";
  screenf(attack, 11, 9, strlen(attack), 1);
  screenf(accuracy, 11, 10, strlen(accuracy), 1);
  screenf(defense, 11, 11, strlen(defense), 1);
  screenf(evasion, 11, 12, strlen(evasion), 1);

  unsigned char mdef[9] = "MDEF 206";
  screenf(mdef, 11, 13, strlen(mdef), 1);
}