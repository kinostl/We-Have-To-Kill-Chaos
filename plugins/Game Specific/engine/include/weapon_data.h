#ifndef FF_WEAPON_DATA
#define FF_WEAPON_DATA
#include "class_data.h" // IWYU pragma: export
#include "enums.h"
#include <asm/types.h>


typedef struct {
  WEAPON_TYPE id;
  WEAPON_FAMILY type;
  WEAPON_COLOR color;
  BYTE attack;
  BYTE hit_chance;
  BYTE crit_chance;
  UWORD price;
  JOB classes; // Flag
} weapon_data ;

extern const weapon_data weapon_db[];

void load_weapon(weapon_data *weapon, WEAPON_TYPE weapon_id) OLDCALL BANKED;
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