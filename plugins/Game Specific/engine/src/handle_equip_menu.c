#include "extra_data.h"
#include "handle_submapping.h"
#include "item_slot.h"
#include "load_font_into_bg.h"
#include "weapon_data.h"
#include "armor_data.h"
#include <asm/types.h>
#include <gb/gb.h>
#include <gb/hardware.h>
#include <macro.h>
#include <string.h>
#include <vm.h>
#include "menu_helper.h"
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

void loadSubStatsArea(SCRIPT_CTX *THIS) OLDCALL BANKED {
  THIS;
  // clearAttrsSection(10, 8, 10, 7);
  // setAttrsSectionColor(10, 8, 10, 7, 1);
  // clearChSection(11, 9, 8, 5);

  unsigned char attack[9] = "ATK   10";
  unsigned char accuracy[9] = "ACC   28";
  unsigned char crit[9] = "CRT    1";
  unsigned char defense[9] = "DEF    1";
  unsigned char evasion[9] = "EVA   15";
  screenf(attack, 11, 9);
  screenf(accuracy, 11, 10);
  screenf(crit, 11, 11);
  screenf(defense, 11, 12);
  screenf(evasion, 11, 13);
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
  loadSubStatsArea(THIS);
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
    add_weapon_sym(item_s, NUNCHUCKS);
    strcat(item_s, "WOOD");
    break;
  case 2:
    add_weapon_sym(item_s, DAGGER);
    strcat(item_s, "SMALL");
    break;
  case 3:
    add_weapon_sym(item_s, STAFF);
    strcat(item_s, "WOOD");
    break;
  case 4:
    add_weapon_sym(item_s, SWORD_1);
    strcat(item_s, "RAPIER");
    break;
  case 5:
    add_weapon_sym(item_s, HAMMER);
    strcat(item_s, "IRON");
    break;
  }
}

inline void write_armor_name(BYTE item_id, unsigned char *item_s) {
  // TODO should display item type symbol then name
  // Also should make so and so wide
  // Max Count is 99 I guess
  switch (item_id) {
  default:
    strcat(item_s, " ");
    break;
  case 1:
    add_armor_sym(item_s, ROBE);
    strcat(item_s, "CLOTH");
    break;
  case 2:
    add_armor_sym(item_s, ARMOR);
    strcat(item_s, "WOOD");
    break;
  case 3:
    add_armor_sym(item_s, ARMOR);
    strcat(item_s, "CHAIN");
    break;
  }
}

void loadEquipWeaponList(SCRIPT_CTX *THIS) OLDCALL BANKED {
  UBYTE currentPlayer = *(UBYTE *)VM_REF_TO_PTR(FN_ARG0);
  turn_slots[currentPlayer].type = WHITE_MAGE;

  clearAttrsSection(0, 8, 10, 7);
  clearChSection(1, 9, 8, 5);
  item_slots[0].count = 2;
  item_slots[0].type = 5;
  item_slots[1].count = 1;
  item_slots[1].type = 1;

  int i = 0;
  int inv_i = 0;
  struct item_slot i_slot;
  struct weapon_data w_data;
  while (i < 5) {
    i_slot = item_slots[inv_i++];
    if (i_slot.type == NULL) {
      break;
    }

    set_weapon(i_slot.type, &w_data);
    // if (!CHK_FLAG(w_data.classes, turn_slots[currentPlayer].type)) {
    //   continue;
    // }

    unsigned char line[8] = "";
    write_weapon_name(i_slot.type, line);
    screenf(line, 2, 9 + i);
    i++;
  }
}

void loadEquipArmorList(SCRIPT_CTX *THIS) OLDCALL BANKED {
  UBYTE currentPlayer = *(UBYTE *)VM_REF_TO_PTR(FN_ARG0);
  turn_slots[currentPlayer].type = WHITE_MAGE;

  clearAttrsSection(0, 8, 10, 7);
  clearChSection(1, 9, 8, 5);
  item_slots[0].count = 2;
  item_slots[0].type = 3;
  item_slots[1].count = 1;
  item_slots[1].type = 1;

  int i = 0;
  int inv_i = 0;
  struct item_slot i_slot;
  struct armor_data a_data;
  while (i < 5) {
    i_slot = item_slots[inv_i++];
    if (i_slot.type == NULL) {
      break;
    }

    set_armor(i_slot.type, &a_data);
    // if (!CHK_FLAG(w_data.classes, turn_slots[currentPlayer].type)) {
    //   continue;
    // }

    unsigned char line[8] = "";
    write_armor_name(i_slot.type, line);
    screenf(line, 2, 9 + i);
    i++;
  }
}

inline void addStatToString(unsigned char string[9], UBYTE stat) {
  unsigned char stat_str[4];
  itoa_fmt(stat, stat_str);
  UBYTE stat_len = strlen(stat_str);
  strcpy(&string[8 - stat_len], stat_str);
}

inline void addCompareToString(unsigned char string[9], UBYTE a, UBYTE b, UBYTE row){
  if(a > b){
    string[4]='>';
    setAttrsSectionColor(15, 9+row, 1, 1, 2);
  } else if(a < b){
    string[4]='<';
    setAttrsSectionColor(15, 9+row, 1, 1, 3);
  } else {
    string[4]='=';
    setAttrsSectionColor(15, 9+row, 1, 1, 4);
  }
}

void loadSubStatsCompareWeaponArea(SCRIPT_CTX *THIS) OLDCALL BANKED {
  THIS;
  item_slots[0].count = 2;
  item_slots[0].type = 5;
  item_slots[1].count = 1;
  item_slots[1].type = 1;
  UBYTE equip_id = *(UBYTE *)VM_REF_TO_PTR(FN_ARG0);
  UBYTE check_id = *(UBYTE *)VM_REF_TO_PTR(FN_ARG1);
  struct weapon_data equip_w, check_w;

  set_weapon(item_slots[equip_id].type, &equip_w);
  set_weapon(item_slots[check_id].type, &check_w);

  unsigned char lines[3][9];
  strcpy(lines[0], "ATK     ");
  strcpy(lines[1], "ACC     ");
  strcpy(lines[2], "CRT     ");

  addStatToString(lines[0], check_w.attack);
  addStatToString(lines[1], check_w.hit_chance);
  addStatToString(lines[2], check_w.crit_chance);

  addCompareToString(lines[0], check_w.attack, equip_w.attack, 0);
  addCompareToString(lines[1], check_w.hit_chance, equip_w.hit_chance, 1);
  addCompareToString(lines[2], check_w.crit_chance, equip_w.crit_chance, 2);

  screenf(lines[0], 11, 9 + 0);
  screenf(lines[1], 11, 9 + 1);
  screenf(lines[2], 11, 9 + 2);
}

inline BYTE calculateEvasion(UBYTE weight, UBYTE agility){
  return 48 + agility - weight;
}

void loadSubStatsCompareArmorArea(SCRIPT_CTX *THIS) OLDCALL BANKED {
  THIS;
  item_slots[0].count = 1;
  item_slots[0].type = 1;
  item_slots[1].count = 1;
  item_slots[1].type = 3;
  UBYTE equip_id = *(UBYTE *)VM_REF_TO_PTR(FN_ARG0);
  UBYTE check_id = *(UBYTE *)VM_REF_TO_PTR(FN_ARG1);
  struct armor_data equip_a, check_a;

  set_armor(item_slots[equip_id].type, &equip_a);
  set_armor(item_slots[check_id].type, &check_a);

  unsigned char lines[2][9];
  strcpy(lines[0], "DEF     ");
  strcpy(lines[1], "EVA     ");

  BYTE equip_evasion =  calculateEvasion(equip_a.weight, 8);
  BYTE check_evasion =  calculateEvasion(check_a.weight, 8);

  addStatToString(lines[0], check_a.defense);
  addStatToString(lines[1], check_evasion);

  addCompareToString(lines[0], check_a.defense, equip_a.defense, 3);
  addCompareToString(lines[1], check_evasion, equip_evasion, 4);

  screenf(lines[0], 11, 9 + 3);
  screenf(lines[1], 11, 9 + 4);
}