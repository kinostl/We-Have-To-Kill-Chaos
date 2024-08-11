#include "extra_data.h"
#include "handle_submapping.h"
#include "item_slot.h"
#include "load_font_into_bg.h"
#include "weapon_data.h"
#include "armor_data.h"
#include <asm/types.h>
#include <data/game_globals.h>
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
inline void screenfw(unsigned char *d, UBYTE x, UBYTE y, UBYTE w) {
  clearChSection(x, y, w, 1);
  for (UBYTE i = 0; i < strlen(d); i++) {
    UBYTE j = d[i];
    d[i] = ReadBankedUBYTE(bg_font.recode_table + j, bg_font_bank);
    d[i] += start_of_bkg_vram;
  }

  set_bkg_tiles(x, y, strlen(d), 1, d);
}

inline void screenf(unsigned char *d, UBYTE x, UBYTE y) {
  screenfw(d, x, y, strlen(d));
}

inline void addStatToString(unsigned char string[9], UBYTE stat) {
  unsigned char stat_str[4];
  itoa_fmt(stat, stat_str);
  UBYTE stat_len = strlen(stat_str);
  strcpy(&string[8 - stat_len], stat_str);
}

inline BYTE calculateEvasion(UBYTE weight, UBYTE agility){
  return 48 + agility - weight;
}
inline BYTE calculateAttack(BYTE attack, BYTE strength){
  return attack + (strength / 2);
}

inline BYTE calculateAccuracy(BYTE weapon_hit_chance, BYTE hit_chance){
  return weapon_hit_chance + hit_chance;
}

inline BYTE calculateCritChance(BYTE weapon_crit_chance, BYTE luck){
  return weapon_crit_chance + (luck /2);

}

void loadStatsArea(SCRIPT_CTX *THIS) OLDCALL BANKED {
  THIS;
  clearAttrsSection(0, 8, 10, 7);
  setAttrsSectionColor(0, 8, 10, 7, 1);
  // clearChSection(1, 9, 8, 5);

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

  BYTE strength = 10;
  BYTE luck = 8;
  BYTE agility = 8;
  BYTE base_hit_chance = 5;

  unsigned char attack[9] = "ATK     ";
  unsigned char accuracy[9] = "ACC     ";
  unsigned char crit[9] = "CRT     ";
  unsigned char defense[9] = "DEF     ";
  unsigned char evasion[9] = "EVA     ";

  addStatToString(attack, calculateAttack(weapon_slots[0].attack, strength));
  addStatToString(accuracy, calculateAccuracy(weapon_slots[0].hit_chance, base_hit_chance));
  addStatToString(crit, calculateCritChance(weapon_slots[0].crit_chance, luck));
  //Normally this should just be the weapon's index number, and luck normally does nothing.

  addStatToString(defense, armor_slots[0].defense);
  addStatToString(evasion, calculateEvasion(armor_slots[0].weight, agility));

  screenf(attack, 11, 9);
  screenf(accuracy, 11, 10);
  screenf(crit, 11, 11);
  screenf(defense, 11, 12);
  screenf(evasion, 11, 13);
}



void write_weapon_name(BYTE item_id, unsigned char *item_s) OLDCALL BANKED{
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

void write_armor_name(BYTE item_id, unsigned char *item_s) OLDCALL BANKED{
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

void load_equip_area(UBYTE character_id) OLDCALL BANKED {
  unsigned char weapon[9] = "";
  write_weapon_name(weapon_slots[character_id].id, weapon);
  screenfw(weapon, 8, 3, 8);
  unsigned char armor[9] = "";
  write_armor_name(armor_slots[character_id].id, armor);
  screenfw(armor, 8, 4, 8);
  unsigned char shield[9] = "";
  add_armor_sym(shield, SHIELD);
  screenfw(shield, 8, 5, 8);
  unsigned char helmet[9] = "";
  add_armor_sym(helmet, HELMET);
  screenfw(helmet, 8, 6, 8);
  unsigned char gloves[9] = "";
  add_armor_sym(gloves, GAUNTLET);
  screenfw(gloves, 8, 7, 8);
}

void loadEquipArea(SCRIPT_CTX *THIS) OLDCALL BANKED {
  THIS;
  UBYTE currentPlayer = *(UBYTE *)VM_REF_TO_PTR(FN_ARG0);
  load_equip_area(currentPlayer);
}

void loadEquipMenu(SCRIPT_CTX *THIS) OLDCALL BANKED {
  THIS;

  unsigned char name[7] = "Fred";
  screenf(name, 1, 1);

  unsigned char hp[11] = "HP 999/999";
  screenf(hp, 9, 1);

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

  loadEquipArea(THIS);
  loadStatsArea(THIS);
  loadSubStatsArea(THIS);
}

void loadEquipWeaponList(SCRIPT_CTX *THIS) OLDCALL BANKED {
  UBYTE currentPlayer = *(UBYTE *)VM_REF_TO_PTR(FN_ARG0);
  turn_slots[currentPlayer].type = WHITE_MAGE;

  clearAttrsSection(0, 8, 10, 7);
  clearChSection(1, 9, 8, 5);

  int i = 0;
  int inv_i = 0;
  struct item_slot i_slot;
  struct weapon_data w_data;
  while (i < 5) {
    i_slot = item_slots[inv_i++];
    if (i_slot.type == NULL_I) {
      break;
    }
    if (i_slot.type != WEAPON_I) {
      continue;
    }

    set_weapon(i_slot.id, &w_data);
    // if (!CHK_FLAG(w_data.classes, turn_slots[currentPlayer].type)) {
    //   continue;
    // }

    unsigned char line[8] = "";
    write_weapon_name(i_slot.id, line);
    screenf(line, 2, 9 + i);
    i++;
  }
  if (i - 1 > 0) {
    VM_GLOBAL(VAR_TEMP_FRAME) = i - 1;
  } else {
    VM_GLOBAL(VAR_TEMP_FRAME) = 0;
  }
}

void loadEquipArmorList(SCRIPT_CTX *THIS) OLDCALL BANKED {
  UBYTE currentPlayer = *(UBYTE *)VM_REF_TO_PTR(FN_ARG0);
  turn_slots[currentPlayer].type = WHITE_MAGE;

  clearAttrsSection(0, 8, 10, 7);
  clearChSection(1, 9, 8, 5);

  int i = 0;
  int inv_i = 0;
  struct item_slot i_slot;
  struct armor_data a_data;
  while (i < 5) {
    i_slot = item_slots[inv_i++];
    if (i_slot.type == NULL_I) {
      break;
    }
    if (i_slot.type != ARMOR_I) {
      continue;
    }

    set_armor(i_slot.id, &a_data);
    // if (!CHK_FLAG(w_data.classes, turn_slots[currentPlayer].type)) {
    //   continue;
    // }

    unsigned char line[8] = "";
    write_armor_name(i_slot.id, line);
    screenf(line, 2, 9 + i);
    i++;
  }
  if (i - 1 > 0) {
    VM_GLOBAL(VAR_TEMP_FRAME) = i - 1;
  } else {
    VM_GLOBAL(VAR_TEMP_FRAME) = 0;
  }
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
  BYTE strength = 10;
  BYTE luck = 8;
  BYTE base_hit_chance = 5;

  THIS;
  UBYTE character_id = *(UBYTE *)VM_REF_TO_PTR(FN_ARG0);
  UBYTE check_id = *(UBYTE *)VM_REF_TO_PTR(FN_ARG1);
  struct weapon_data equip_w, check_w;
  BYTE weapon_slot = getNthItemSlotIndexOfItem(check_id, WEAPON_I);

  set_weapon(weapon_slots[character_id].id, &equip_w);
  set_weapon(item_slots[weapon_slot].id, &check_w);

  unsigned char lines[3][9];
  strcpy(lines[0], "ATK     ");
  strcpy(lines[1], "ACC     ");
  strcpy(lines[2], "CRT     ");

  //Displaying wrong because not doing calculations correctly

  BYTE check_attack = calculateAttack(check_w.attack, strength);
  BYTE check_accuracy = calculateAccuracy(check_w.hit_chance, base_hit_chance);
  BYTE check_crit = calculateCritChance(check_w.crit_chance, luck);

  BYTE equip_attack = calculateAttack(equip_w.attack, strength);
  BYTE equip_accuracy = calculateAccuracy(equip_w.hit_chance, base_hit_chance);
  BYTE equip_crit = calculateCritChance(equip_w.crit_chance, luck);

  addStatToString(lines[0], check_attack);
  addStatToString(lines[1], check_accuracy);
  addStatToString(lines[2], check_crit);

  addCompareToString(lines[0], check_attack, equip_attack, 0);
  addCompareToString(lines[1], check_accuracy, equip_accuracy, 1);
  addCompareToString(lines[2], check_crit, equip_crit, 2);

  screenf(lines[0], 11, 9 + 0);
  screenf(lines[1], 11, 9 + 1);
  screenf(lines[2], 11, 9 + 2);
}

void loadSubStatsCompareArmorArea(SCRIPT_CTX *THIS) OLDCALL BANKED {
  THIS;
  UBYTE character_id = *(UBYTE *)VM_REF_TO_PTR(FN_ARG0);
  UBYTE check_id = *(UBYTE *)VM_REF_TO_PTR(FN_ARG1);
  struct armor_data equip_a, check_a;
  BYTE armor_slot = getNthItemSlotIndexOfItem(check_id, ARMOR_I);

  set_armor(armor_slots[character_id].id, &equip_a);
  set_armor(item_slots[armor_slot].id, &check_a);

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

void equipWeapon(SCRIPT_CTX * THIS) OLDCALL BANKED {
  UBYTE character_id = *(UBYTE *)VM_REF_TO_PTR(FN_ARG0);
  UBYTE equip_id = *(UBYTE *)VM_REF_TO_PTR(FN_ARG1);

  UBYTE weapon_id = weapon_slots[character_id].id;
  BYTE equip_slot = getNthItemSlotIndexOfItem(equip_id, WEAPON_I);
  BYTE e_weapon_id = item_slots[equip_slot].id;

  set_weapon(e_weapon_id, &weapon_slots[character_id]);
  removeItem(e_weapon_id, WEAPON_I);
  addWeaponItem(weapon_id);
}

void equipArmor(SCRIPT_CTX * THIS) OLDCALL BANKED {
  UBYTE character_id = *(UBYTE *)VM_REF_TO_PTR(FN_ARG0);
  UBYTE equip_id = *(UBYTE *)VM_REF_TO_PTR(FN_ARG1);

  UBYTE armor_id = armor_slots[character_id].id;
  BYTE equip_slot = getNthItemSlotIndexOfItem(equip_id, ARMOR_I);
  BYTE e_armor_id = item_slots[equip_slot].id;

  set_armor(e_armor_id, &armor_slots[character_id]);
  removeItem(e_armor_id, ARMOR_I);
  addArmorItem(armor_id);
}

void equipHelmet(SCRIPT_CTX * THIS) OLDCALL BANKED {
  UBYTE character_id = *(UBYTE *)VM_REF_TO_PTR(FN_ARG0);
  UBYTE equip_id = *(UBYTE *)VM_REF_TO_PTR(FN_ARG1);

  UBYTE helmet_id = helmet_slots[character_id].id;
  BYTE equip_slot = getNthItemSlotIndexOfItem(equip_id, HELMET_I);
  BYTE e_helmet_id = item_slots[equip_slot].id;

  set_armor(e_helmet_id, &helmet_slots[character_id]);
  removeItem(e_helmet_id, HELMET_I);
  addHelmetItem(helmet_id);
}

void falsifyData(SCRIPT_CTX * THIS) OLDCALL BANKED {
  THIS;
  addArmorItem(2);
  addArmorItem(3);
  addArmorItem(26);
  addWeaponItem(2);
  addWeaponItem(3);
  set_weapon(1, &weapon_slots[0]);
  set_armor(1, &armor_slots[0]);
}