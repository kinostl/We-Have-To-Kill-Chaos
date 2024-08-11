#include <asm/types.h>
#include <string.h>
#include <types.h>
#pragma bank 255
#include "extra_data.h"
#include "item_slot.h"

#define ITEM_NOT_FOUND MAX_ITEM_SLOTS + 1

BYTE getItemSlotIndex(BYTE item_id, enum I_TYPE type) OLDCALL BANKED {
    for(int i=0;i<MAX_ITEM_SLOTS;i++){
        if(item_slots[i].id == item_id && item_slots[i].type == type){
            return i;
        };
    }
    return ITEM_NOT_FOUND;
}

BYTE getNextItemSlotIndex(void) OLDCALL BANKED {
    for(int i=0;i<MAX_ITEM_SLOTS;i++){
        if(item_slots[i].type == NULL_I){
            return i;
        };
    }
    return ITEM_NOT_FOUND;
}

BYTE addItems(BYTE item_id, enum I_TYPE type, BYTE count) OLDCALL BANKED{
    UBYTE slot_i = getItemSlotIndex(item_id, type);
    if (slot_i >= ITEM_NOT_FOUND) {
      slot_i = getNextItemSlotIndex();
      if (slot_i >= ITEM_NOT_FOUND) {
        return ITEM_NOT_FOUND;
      }

      item_slots[slot_i].id = item_id;
      item_slots[slot_i].type = type;
      item_slots[slot_i].count = 0;
    }

    item_slots[slot_i].count+= count;

    return slot_i;
}

BYTE addItem(BYTE item_id, enum I_TYPE type) OLDCALL BANKED{
    return addItems(item_id, type, 1);
}

BYTE addWeaponItem(BYTE item_id) OLDCALL BANKED {
  return addItem(item_id, WEAPON_I);
}
BYTE addArmorItem(BYTE item_id) OLDCALL BANKED {
  return addItem(item_id, ARMOR_I);
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
        item_slots[slot_i] = item_slots[slot_i + 1];
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