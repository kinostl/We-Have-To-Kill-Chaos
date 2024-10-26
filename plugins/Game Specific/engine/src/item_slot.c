#include <asm/types.h>
#include <string.h>
#include <types.h>
#pragma bank 255
#include "extra_data.h"
#include "item_slot.h"

BYTE get_item_slot_index(BYTE item_id, enum I_TYPE type, item_slot * slots) OLDCALL BANKED{
    for(int i=0;i<MAX_ITEM_SLOTS;i++){
        if(slots[i].id == item_id && slots[i].type == type){
            return i;
        };
    }
    return ITEM_NOT_FOUND;
}

BYTE getItemSlotIndex(BYTE item_id, enum I_TYPE type) OLDCALL BANKED {
    return get_item_slot_index(item_id, type, item_slots);
}

BYTE get_next_item_slot_index(item_slot * slots){
    for(int i=0;i<MAX_ITEM_SLOTS;i++){
        if(slots[i].type == NULL_I){
            return i;
        };
    }
    return ITEM_NOT_FOUND;

}
BYTE getNextItemSlotIndex(void) OLDCALL BANKED {
    return get_next_item_slot_index(item_slots);
}
BYTE add_items(BYTE item_id, enum I_TYPE type, BYTE count, item_slot * slots) OLDCALL BANKED{
    UBYTE slot_i = get_item_slot_index(item_id, type, slots);
    if (slot_i >= ITEM_NOT_FOUND) {
      slot_i = get_next_item_slot_index(slots);
      if (slot_i >= ITEM_NOT_FOUND) {
        return ITEM_NOT_FOUND;
      }

      slots[slot_i].id = item_id;
      slots[slot_i].type = type;
      slots[slot_i].count = 0;
    }

    slots[slot_i].count+= count;

    return slot_i;
}

BYTE addItems(BYTE item_id, enum I_TYPE type, BYTE count) OLDCALL BANKED{
    return add_items(item_id, type, count, item_slots);
}

BYTE addMenuItems(BYTE item_id, enum I_TYPE type, BYTE count) OLDCALL BANKED{
    return add_items(item_id, type, count, menu_slots);
}

BYTE addItem(BYTE item_id, enum I_TYPE type) OLDCALL BANKED{
    return addItems(item_id, type, 1);
}

BYTE addMenuItem(BYTE item_id, enum I_TYPE type) OLDCALL BANKED{
    return addMenuItems(item_id, type, 1);
}

BYTE getMenuLength(void) OLDCALL BANKED {
    BYTE n=0;
    for(int i=0;i<MAX_ITEM_SLOTS;i++){
        if(menu_slots[i].type == NULL_I){
            break;
        }
        n++;
    }
    return n;
}

BYTE addWeaponItem(BYTE item_id) OLDCALL BANKED {
  return addItem(item_id, WEAPON_I);
}
BYTE addArmorItem(BYTE item_id) OLDCALL BANKED {
  return addItem(item_id, ARMOR_I);
}
BYTE addShieldItem(BYTE item_id) OLDCALL BANKED {
  return addItem(item_id, SHIELD_I);
}
BYTE addGloveItem(BYTE item_id) OLDCALL BANKED {
  return addItem(item_id, GLOVE_I);
}
BYTE addHelmetItem(BYTE item_id) OLDCALL BANKED {
  return addItem(item_id, HELMET_I);
}
BYTE addPotionItem(BYTE item_id) OLDCALL BANKED {
  return addItem(item_id, POTION_I);
}

BYTE removeItems(BYTE item_id, enum I_TYPE type, BYTE count) OLDCALL BANKED {
  BYTE slot_i = getItemSlotIndex(item_id, type);
  if (slot_i >= ITEM_NOT_FOUND) {
    return ITEM_NOT_FOUND;
  }
  item_slots[slot_i].count-= count;

  if (item_slots[slot_i].count < 1) {
    for(int i=slot_i;i<MAX_ITEM_SLOTS - 1;i++){
        item_slots[i] = item_slots[i + 1];
    }

    item_slots[MAX_ITEM_SLOTS - 1].id = NULL;
    item_slots[MAX_ITEM_SLOTS - 1].type = NULL_I;
    item_slots[MAX_ITEM_SLOTS - 1].count = 0;
    return ITEM_NOT_FOUND;
  }

  return slot_i;
}

BYTE removeItem(BYTE item_id, enum I_TYPE type) OLDCALL BANKED {
  return removeItems(item_id, type, 1);
}

BYTE getNthItemSlotIndexOfItem(BYTE nth, enum I_TYPE type) OLDCALL BANKED {
  BYTE n = 0;
  for (int i = 0; i < MAX_ITEM_SLOTS; i++) {
    if (item_slots[i].type == type) {
      if (nth == n) {
        return i;
      }
      n++;
    }
  }
  return ITEM_NOT_FOUND;
}

void clearMenu(void) OLDCALL BANKED{
    for(int i=0;i<MAX_ITEM_SLOTS;i++){
        menu_slots[i].id = NULL;
        menu_slots[i].type = NULL_I;
        menu_slots[i].count = 0;
    }
}

void sortMenu(void) OLDCALL BANKED {
  item_slot temp;
  UBYTE largest;
  for (int i = 0; i < MAX_ITEM_SLOTS - 1; i++) {
    largest = i;
    for (int j = i + 1; j < MAX_ITEM_SLOTS; j++) {
      if (menu_slots[largest].id < menu_slots[j].id) {
        largest = j;
      }
    }
    temp = menu_slots[i];
    menu_slots[i] = menu_slots[largest];
    menu_slots[largest] = temp;
  }
}