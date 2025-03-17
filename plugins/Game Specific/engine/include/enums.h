#ifndef FF_ENUMS
#define FF_ENUMS

typedef enum {
  EMPTY_ENEMY_SLOT,
  IMP,
  GrIMP,
  WOLF,
  MADPONY,
  CREEP,
  BONE,
  SPIDER
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
  GUARD,
  COVER,
  BLADE_BLITZ,
  FIRE,
  ICE,
  HARM,
  HEAL,
  GOBLIN_PUNCH,
  HOWL,
  THRASH,
  LUSTER,
  STUN,
  WEAK,
  SNEAK,
  FOCUS,
  WRECK,
  PIERCE,
  LOAD,
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
  CRITICAL_MISS = 1 << 0,
  ATTACK_MISSED = 1 << 1,
  ATTACK_HIT = 1 << 2,
  CRITICAL_HIT = 1 << 3,
  TARGET_DEFEATED = 1 << 4,
  MAGIC_HIT = 1 << 5,
  MAGIC_RESISTED = 1 << 6,
  SKILL_HIT = 1 << 7
} ATTACK_RESULTS;

typedef enum {
  DEAD = 1 << 0,
  PETRIFIED = 1 << 1,
  POISONED = 1 << 2,
  BLIND = 1 << 3,
  PARALYZED = 1 << 4,
  ASLEEP = 1 << 5,
  SILENCED = 1 << 6,
  CONFUSED = 1 << 7,
  DEFENDING = 1 << 8,
  WEAKENED = 1 << 9,
} STATUS_EFFECT;

typedef enum {
  FIELD,
  FOREST,
} BATTLE_ID;

typedef enum {
  NO_TURN,
  PLAYER_TURN,
  ENEMY_TURN
} TURN_TYPE;

typedef enum {
  NO_ELEMENT,
  FIRE_ELEMENT
} SPELL_ELEMENT;
#endif