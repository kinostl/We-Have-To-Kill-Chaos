#ifndef FF_INV_SLOTS
#define FF_INV_SLOTS
#include <asm/types.h>

enum I_TYPE{
    NULL_I,
    POTION_I,
    WEAPON_I,
    ARMOR_I
};

struct item_slot{
    BYTE id;
    enum I_TYPE type; //Armor, Weapon, Potion, etc
    BYTE count;
};

BYTE getItemSlotIndex(BYTE item_id, enum I_TYPE type) OLDCALL BANKED;
BYTE getNextItemSlotIndex(void) OLDCALL BANKED;
BYTE addItems(BYTE item_id, enum I_TYPE type, BYTE count) OLDCALL BANKED;
BYTE addItem(BYTE item_id, enum I_TYPE type) OLDCALL BANKED;
BYTE addWeaponItem(BYTE item_id) OLDCALL BANKED;
BYTE addArmorItem(BYTE item_id) OLDCALL BANKED;
BYTE addPotionItem(BYTE item_id) OLDCALL BANKED;
BYTE removeItems(BYTE item_id, enum I_TYPE type, BYTE count) OLDCALL BANKED;
BYTE removeItem(BYTE item_id, enum I_TYPE type) OLDCALL BANKED;
BYTE getNthItemSlotIndexOfItem(BYTE nth, enum I_TYPE type) OLDCALL BANKED;

#endif