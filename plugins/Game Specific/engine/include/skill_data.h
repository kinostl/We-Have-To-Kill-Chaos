#ifndef FF_SKILLS
#define FF_SKILLS
#include <asm/types.h>
#include <gb/gb.h>
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
  RUNE_SWORD
} BATTLE_SKILL;

typedef enum {
  TARGET_SELF,
  TARGET_ALLY,
  TARGET_ALL_ALLY,
  TARGET_ENEMY,
  TARGET_ALL_ENEMY,
  TARGET_ALL
} SKILL_TARGET;

typedef struct {
  BATTLE_SKILL id;
  const unsigned char name[8];
  BYTE cost;
  SKILL_TARGET target;
} skill_data;

extern const skill_data skill_db[];
void load_skill(skill_data * skill, BATTLE_SKILL skill_id) BANKED;
#endif