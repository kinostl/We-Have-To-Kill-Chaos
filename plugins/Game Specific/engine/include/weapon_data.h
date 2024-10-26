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

typedef struct {
  BYTE id;
  enum W_TYPE type;
  enum W_COLOR color;
  BYTE attack;
  BYTE hit_chance;
  BYTE crit_chance;
  UWORD price;
  UWORD classes; // Flag
} weapon_data ;

void set_weapon(BYTE weapon_id, weapon_data *weapon) OLDCALL BANKED;
void load_weapon_info_text(weapon_data w_data, unsigned char * item_s, UBYTE width, UBYTE offset) OLDCALL BANKED;

inline BYTE calculateAttack(BYTE attack, BYTE strength){
  return attack + (strength / 2);
}

inline BYTE calculateAccuracy(BYTE weapon_hit_chance, BYTE hit_chance){
  return weapon_hit_chance + hit_chance;
}

inline BYTE calculateCritChance(BYTE weapon_crit_chance, BYTE luck){
  return weapon_crit_chance + (luck /2);

}

#endif