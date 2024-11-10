#include "armor_data/naked.h"
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

#define calculateEvasion(weight, agility) 48 + agility - weight

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

inline UBYTE sum_armor_def(UBYTE i) {
  return 0;
  // return armor_slots[i].defense + shield_slots[i].defense +
  //        helmet_slots[i].defense + glove_slots[i].defense;
}

inline UBYTE sum_armor_weight(UBYTE i) {
  return 0;
  // return armor_slots[i].weight + shield_slots[i].weight +
  //        helmet_slots[i].weight + glove_slots[i].weight;
}

void loadSubStatsArea(SCRIPT_CTX *THIS) OLDCALL BANKED {
  THIS;
  // // clearAttrsSection(10, 8, 10, 7);
  // // setAttrsSectionColor(10, 8, 10, 7, 1);
  // // clearChSection(11, 9, 8, 5);

  // BYTE strength = 10;
  // BYTE luck = 8;
  // BYTE agility = 8;
  // BYTE base_hit_chance = 5;

  // unsigned char attack[9] = "ATK     ";
  // unsigned char accuracy[9] = "ACC     ";
  // unsigned char crit[9] = "CRT     ";
  // unsigned char defense[9] = "DEF     ";
  // unsigned char evasion[9] = "EVA     ";

  // addStatToString(attack, calculateAttack(weapon_slots[0].attack, strength));
  // addStatToString(accuracy, calculateAccuracy(weapon_slots[0].hit_chance, base_hit_chance));
  // addStatToString(crit, calculateCritChance(weapon_slots[0].crit_chance, luck));
  // //Normally this should just be the weapon's index number, and luck normally does nothing.

  // addStatToString(defense, sum_armor_def(0));
  // addStatToString(evasion, calculateEvasion( sum_armor_weight(0) , agility));

  // screenf(attack, 11, 9);
  // screenf(accuracy, 11, 10);
  // screenf(crit, 11, 11);
  // screenf(defense, 11, 12);
  // screenf(evasion, 11, 13);
}





void load_equip_area(UBYTE character_id) OLDCALL BANKED {
  // unsigned char weapon[9] = "";
  // weapon_name_short_cat(weapon_slots[character_id].id, weapon);
  // screenfw(weapon, 8, 3, 8);
  // unsigned char armor[9] = "";
  // armor_name_short_cat(armor_slots[character_id].id, ARMOR, armor);
  // screenfw(armor, 8, 4, 8);
  // unsigned char shield[9] = "";
  // add_armor_sym(shield, SHIELD);
  // screenfw(shield, 8, 5, 8);
  // unsigned char helmet[9] = "";
  // armor_name_short_cat(helmet_slots[character_id].id, HELMET, helmet);
  // screenfw(helmet, 8, 6, 8);
  // unsigned char gloves[9] = "";
  // add_armor_sym(gloves, GAUNTLET);
  // screenfw(gloves, 8, 7, 8);
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

void loadEquipList(SCRIPT_CTX *THIS) OLDCALL BANKED {
  // UBYTE currentPlayer = *(UBYTE *)VM_REF_TO_PTR(FN_ARG0);
  // UBYTE currentPlayer = 0;
  // UBYTE entityType = *(UBYTE *)VM_REF_TO_PTR(FN_ARG1);
  // turn_slots[currentPlayer].type = MONK;

  // clearAttrsSection(0, 8, 10, 7);
  // clearChSection(1, 9, 8, 5);
  // clearMenu();

  // int i = 0;
  // int inv_i = 0;
  // item_slot i_slot;
  // weapon_data w_data;
  // armor_data a_data;
  // enum I_TYPE i_type = WEAPON_I + entityType;

  // while (i < 5) {
  //   i_slot = item_slots[inv_i++];
  //   if (!i_slot.type) {
  //     break;
  //   }
  //   if (i_slot.type != i_type) {
  //     continue;
  //   }

  //   if (i_type == WEAPON_I) {
  //     set_weapon(i_slot.id, &w_data);
  //     if (!CHK_FLAG(w_data.classes, turn_slots[currentPlayer].type))
  //       continue;
  //   } else {
  //     set_armor(i_slot.id, &a_data);
  //     if (!CHK_FLAG(a_data.classes, turn_slots[currentPlayer].type))
  //       continue;
  //   }
  //   i++;
  //   if (addMenuItem(i_slot.id, i_type) >= 4)
  //     break;
  // }
  // sortMenu();
  // if (i - 1 > 0) {
  //   VM_GLOBAL(VAR_TEMP_FRAME) = i - 1;
  // } else {
  //   VM_GLOBAL(VAR_TEMP_FRAME) = 0;
  // }
  // for (i = 0; i < 5; i++) {
  //   i_slot = menu_slots[i];
  //   if(menu_slots[i].type == NULL_I) break;
  //   unsigned char line[8] = "";
  //   if (i_type == WEAPON_I) {
  //     weapon_name_short_cat(i_slot.id, line);
  //   } else {
  //     armor_name_short_cat(i_slot.id, NULL, line);
  //   }
  //   if (i_slot.id == 0) {
  //     strcpy(line, "Remove");
  //   }
  //   screenf(line, 2, 9 + i);
  // }
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
  // BYTE strength = 10;
  // BYTE luck = 8;
  // BYTE base_hit_chance = 5;

  // THIS;
  // // UBYTE character_id = *(UBYTE *)VM_REF_TO_PTR(FN_ARG0);
  // UBYTE character_id = 0;
  // UBYTE check_id = *(UBYTE *)VM_REF_TO_PTR(FN_ARG1);
  // weapon_data equip_w, check_w;

  // set_weapon(weapon_slots[character_id].id, &equip_w);
  // set_weapon(menu_slots[check_id].id, &check_w);

  // unsigned char lines[3][9];
  // strcpy(lines[0], "ATK     ");
  // strcpy(lines[1], "ACC     ");
  // strcpy(lines[2], "CRT     ");

  // //Displaying wrong because not doing calculations correctly

  // BYTE check_attack = calculateAttack(check_w.attack, strength);
  // BYTE check_accuracy = calculateAccuracy(check_w.hit_chance, base_hit_chance);
  // BYTE check_crit = calculateCritChance(check_w.crit_chance, luck);

  // BYTE equip_attack = calculateAttack(equip_w.attack, strength);
  // BYTE equip_accuracy = calculateAccuracy(equip_w.hit_chance, base_hit_chance);
  // BYTE equip_crit = calculateCritChance(equip_w.crit_chance, luck);

  // addStatToString(lines[0], check_attack);
  // addStatToString(lines[1], check_accuracy);
  // addStatToString(lines[2], check_crit);

  // addCompareToString(lines[0], check_attack, equip_attack, 0);
  // addCompareToString(lines[1], check_accuracy, equip_accuracy, 1);
  // addCompareToString(lines[2], check_crit, equip_crit, 2);

  // screenf(lines[0], 11, 9 + 0);
  // screenf(lines[1], 11, 9 + 1);
  // screenf(lines[2], 11, 9 + 2);
}

void loadSubStatsCompareArmorArea(SCRIPT_CTX *THIS) OLDCALL BANKED {
  // THIS;
  // // UBYTE character_id = *(UBYTE *)VM_REF_TO_PTR(FN_ARG0);
  // UBYTE character_id = 0;
  // UBYTE check_id = *(UBYTE *)VM_REF_TO_PTR(FN_ARG1);
  // armor_data check_t;
  // UBYTE check_d, equip_d;
  // UBYTE check_w, equip_w;

  // equip_d = sum_armor_def(character_id);
  // check_d = equip_d;
  // equip_w = sum_armor_weight(character_id);
  // check_w = equip_w;

  // set_armor(menu_slots[check_id].id, &check_t);

  // switch (menu_slots[check_id].type) {
  // case ARMOR_I:
  //   check_d -= armor_slots[character_id].defense;
  //   check_w -= armor_slots[character_id].weight;
  //   break;
  // case SHIELD_I:
  //   check_d -= shield_slots[character_id].defense;
  //   check_w -= shield_slots[character_id].weight;
  //   break;
  // case HELMET_I:
  //   check_d -= helmet_slots[character_id].defense;
  //   check_w -= helmet_slots[character_id].weight;
  //   break;
  // case GLOVE_I:
  //   check_d -= glove_slots[character_id].defense;
  //   check_w -= glove_slots[character_id].weight;
  //   break;
  // default:
  //   break;
  // }

  // check_d += check_t.defense;
  // check_w += check_t.weight;

  // unsigned char lines[2][9];
  // strcpy(lines[0], "DEF     ");
  // strcpy(lines[1], "EVA     ");

  // UBYTE equip_evasion =  calculateEvasion(equip_w, 8);
  // UBYTE check_evasion =  calculateEvasion(check_w, 8);

  // addStatToString(lines[0], check_d);
  // addStatToString(lines[1], check_evasion);

  // addCompareToString(lines[0], check_d, equip_d, 3);
  // addCompareToString(lines[1], check_evasion, equip_evasion, 4);

  // screenf(lines[0], 11, 9 + 3);
  // screenf(lines[1], 11, 9 + 4);
}

void equipWeapon(SCRIPT_CTX *THIS) OLDCALL BANKED {
  // UBYTE character_id = *(UBYTE *)VM_REF_TO_PTR(FN_ARG0);
  // UBYTE equip_id = *(UBYTE *)VM_REF_TO_PTR(FN_ARG1);

  // UBYTE weapon_id = weapon_slots[character_id].id;

  // set_weapon(menu_slots[equip_id].id, &weapon_slots[character_id]);
  // removeItem(menu_slots[equip_id].id, WEAPON_I);
  // addWeaponItem(weapon_id);
  // VM_GLOBAL(VAR_1WEAPON_TYPE) = weapon_slots[character_id].type;
  // VM_GLOBAL(VAR_1WEAPON_COLORS) = weapon_slots[character_id].color;
}

void equipArmor(SCRIPT_CTX *THIS) OLDCALL BANKED {
  // UBYTE character_id = *(UBYTE *)VM_REF_TO_PTR(FN_ARG0);
  // UBYTE equip_id = *(UBYTE *)VM_REF_TO_PTR(FN_ARG1);

  // UBYTE armor_id = armor_slots[character_id].id;

  // set_armor(menu_slots[equip_id].id, &armor_slots[character_id]);
  // removeItem(menu_slots[equip_id].id, ARMOR_I);
  // addArmorItem(armor_id);
}

void equipHelmet(SCRIPT_CTX * THIS) OLDCALL BANKED {
  // UBYTE character_id = *(UBYTE *)VM_REF_TO_PTR(FN_ARG0);
  // UBYTE equip_id = *(UBYTE *)VM_REF_TO_PTR(FN_ARG1);

  // UBYTE helmet_id = helmet_slots[character_id].id;

  // set_armor(menu_slots[equip_id].id, &helmet_slots[character_id]);
  // removeItem(menu_slots[equip_id].id, HELMET_I);
  // addHelmetItem(helmet_id);
}

void falsifyData(SCRIPT_CTX * THIS) OLDCALL BANKED {
  // THIS;
  // addArmorItem(1);
  // addArmorItem(2);
  // addArmorItem(3);

  // addHelmetItem(26);

  // addWeaponItem(1);
  // addWeaponItem(1);
  // addWeaponItem(2);
  // addWeaponItem(3);

  // set_weapon(0, &weapon_slots[0]);
  // set_armor(0, &armor_slots[0]);
  // set_armor(0, &shield_slots[0]);
  // set_armor(0, &helmet_slots[0]);
  // set_armor(0, &glove_slots[0]);
}