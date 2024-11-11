#ifndef FF_ENUMS
#define FF_ENUMS

typedef enum {
  IMP,
  WOLF,
  MADPONY,
} ENEMY_TYPE;

typedef enum {
  NO_ENEMY_FAMILY,
  GIANT,
} ENEMY_FAMILY;

typedef enum {
  NUDE,
  CLOTH,
  WOOD_ARMOR,
  CHAIN_ARMOR,
  CAP,
} ARMOR_TYPE;

typedef enum {
  UNARMORED,
  ARMOR,
  ROBE,
  BRACELET,
  SHIELD,
  HELMET,
  GAUNTLET,
} ARMOR_FAMILY;

typedef enum {

  UNARMED,
  WOOD_NUNCHUCKS,
  SMALL_KNIFE,
  WOOD_STAFF,
  RAPIER,
  IRON_HAMMER,
  WERE_SWORD,
  RUNE_SWORD,

} WEAPON_TYPE;

typedef enum {

  NO_WEAPON_FAMILY,
  FISTS,
  DAGGER,
  HAMMER,
  NUNCHUCKS,
  STAFF,
  SWORD_1,
  SWORD_2,
  SWORD_3,

} WEAPON_FAMILY;

typedef enum {
  DMG,
  BROWN,
  GREY,
  PURPLE,
  PINK,
} WEAPON_COLOR;

typedef enum {
  BLANK,
  FIGHT,
  SHIELD_SKILL,
  LUSTER,
  FIRE,
  ICE,
  HARM,
  HEAL,
  GOBLIN_PUNCH,
  HOWL,
  THRASH,
  RUNE_SWORD_SKILL
} BATTLE_SKILL;

typedef enum {
  TARGET_SELF,
  TARGET_ALLY,
  TARGET_ALL_ALLY,
  TARGET_ENEMY,
  TARGET_ALL_ENEMY,
  TARGET_ALL
} SKILL_TARGET;

typedef enum {
  CRITICAL_MISS,
  ATTACK_MISSED,
  ATTACK_HIT,
  CRITICAL_HIT,
  TARGET_DEFEATED
} ATTACK_RESULTS;

#endif