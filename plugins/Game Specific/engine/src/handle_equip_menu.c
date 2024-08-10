#include "extra_data.h"
#include "handle_submapping.h"
#include "item_slot.h"
#include "load_font_into_bg.h"
#include "weapon_data.h"
#include <asm/types.h>
#include <gb/gb.h>
#include <gb/hardware.h>
#include <macro.h>
#include <string.h>
#include <vm.h>
#pragma bank 255

inline void clearChSection(UBYTE x, UBYTE y, UBYTE w, UBYTE h) {
  UBYTE blank_ch_tile;
  blank_ch_tile = ReadBankedUBYTE(bg_font.recode_table + ' ', bg_font_bank);
  blank_ch_tile += start_of_bkg_vram;
  fill_bkg_rect(x, y, w, h, blank_ch_tile);
}

inline void screenf(unsigned char *d, UBYTE x, UBYTE y) {
  clearChSection(x, y, strlen(d), 1);
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

  set_bkg_tiles(x, y, strlen(d), 1, d);
}

void loadStatsArea(SCRIPT_CTX *THIS) OLDCALL BANKED {
  THIS;
  clearAttrsSection(0, 8, 10, 7);
  setAttrsSectionColor(0, 8, 10, 7, 1);
  clearChSection(1, 9, 8, 5);

  unsigned char strength[9] = "STR   10";
  unsigned char agility[9] = "AGL    8";
  unsigned char intel[9] = "INT    1";
  unsigned char stamina[9] = "STA   15";
  unsigned char luck[9] = "LCK    8";

  screenf(strength, 1, 9);
  screenf(agility, 1, 10);
  screenf(intel, 1, 11);
  screenf(stamina, 1, 12);
  screenf(luck, 1, 13);
}

void loadEquipMenu(SCRIPT_CTX *THIS) OLDCALL BANKED {
  THIS;

  unsigned char name[7] = "Fred";
  screenf(name, 1, 1);

  unsigned char hp[11] = "HP 999/999";
  screenf(hp, 9, 1);

  unsigned char weapon[12] = "W Nunchucks";
  weapon[1] = 150;
  screenf(weapon, 8, 4);
  unsigned char armor[12] = "A Cloth";
  armor[1] = 150;
  screenf(armor, 8, 6);

  unsigned char lv_label[3] = "Lv";
  screenf(lv_label, 1, 15);
  unsigned char total_exp_label[] = "EXP";
  screenf(total_exp_label, 5, 15);
  unsigned char next_exp_label[] = "NxtLv";
  screenf(next_exp_label, 13, 15);

  unsigned char lv[] = "49";
  unsigned char total_exp[] = "956841";
  unsigned char next_exp[] = " 32800";

  screenf(lv, 1, 16);
  screenf(total_exp, 5, 16);
  screenf(next_exp, 13, 16);

  loadStatsArea(THIS);

  unsigned char attack[9] = "ATK < 10";
  unsigned char accuracy[9] = "ACC > 28";
  unsigned char defense[9] = "DEF =  1";
  unsigned char evasion[9] = "EVA = 15";
  screenf(attack, 11, 9);
  screenf(accuracy, 11, 10);
  screenf(defense, 11, 11);
  screenf(evasion, 11, 12);

  unsigned char mdef[9] = "MDEF 206";
  screenf(mdef, 11, 13);
}

inline void add_item_sym(unsigned char *d, BYTE sym_id) {
  const unsigned char sym_base = 137;
  unsigned char sym[2] = {sym_base + sym_id, '\0'};
  strcat(d, sym);
}

inline void write_weapon_name(BYTE item_id, unsigned char *item_s) {
  // TODO should display item type symbol then name
  // Also should make so and so wide
  // Max Count is 99 I guess
  switch (item_id) {
  default:
    strcat(item_s, " ");
    break;
  case 1:
    add_item_sym(item_s, 2);
    strcat(item_s, "WOOD");
    break;
  case 2:
    add_item_sym(item_s, 0);
    strcat(item_s, "SMALL");
    break;
  case 3:
    add_item_sym(item_s, 3);
    strcat(item_s, "WOOD");
    break;
  case 4:
    add_item_sym(item_s, 4);
    strcat(item_s, "RAPIER");
    break;
  case 5:
    add_item_sym(item_s, 1);
    strcat(item_s, "IRON");
    break;
  }
}

void loadEquipList(SCRIPT_CTX *THIS) OLDCALL BANKED {
  UBYTE listType = *(UBYTE *)VM_REF_TO_PTR(FN_ARG0);
  // UBYTE currentPlayer = *(UBYTE *)VM_REF_TO_PTR(FN_ARG1);
  UBYTE currentPlayer = 0;
  turn_slots[0].type = WHITE_MAGE;

  //ATK > 10
  //ATK < 10
  //ATK = 10

  clearAttrsSection(0, 8, 10, 7);
  clearChSection(1, 9, 8, 5);
  item_slots[0].count = 2;
  item_slots[0].type = 5;
  item_slots[1].count = 1;
  item_slots[1].type = 1;
  

  int i;
  int inv_i;
  switch (listType) {
  default:
    for (i = 0; i < 5; i++) {
      unsigned char line[8] = " ";
      screenf(line, 2, 9 + i);
    }
    break;
  case 0:
    i = 0;
    inv_i = 0;
    struct item_slot i_slot;
    struct weapon_data w_data;
    while (i < 5) {
      i_slot = item_slots[inv_i++];
      if (i_slot.type == NULL) {
        break;
      }

      set_weapon(i_slot.type, &w_data);
      if (!CHK_FLAG(w_data.classes, turn_slots[currentPlayer].type)) {
        continue;
      }

      unsigned char line[8] = "";
      write_weapon_name(i_slot.type, line);
      screenf(line, 2, 9 + i);
      i++;
    }
    break;
  }
}