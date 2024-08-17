#ifndef FF_WEAPON_DATA
#define FF_WEAPON_DATA
#include "class_data.h"
#include <asm/types.h>

enum W_TYPE {
  UNARMED,
  FISTS,
  DAGGER,
  HAMMER,
  NUNCHUCKS,
  STAFF,
  SWORD_1,
  SWORD_2,
  SWORD_3
};

enum W_COLOR { DMG, BROWN, GREY, PURPLE, PINK };

struct weapon_data {
  BYTE id;
  enum W_TYPE type;
  enum W_COLOR color;
  BYTE attack;
  BYTE hit_chance;
  BYTE crit_chance;
  UWORD price;
  UWORD classes; // Flag
};

void set_weapon(BYTE weapon_id, struct weapon_data *weapon) OLDCALL BANKED;
void load_weapon_info_text(struct weapon_data w_data, unsigned char * item_s, UBYTE width, UBYTE offset) OLDCALL BANKED;
#endif