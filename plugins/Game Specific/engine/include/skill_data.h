#ifndef FF_SKILLS
#define FF_SKILLS
#include "enums.h"
#include <asm/types.h>
#include <gb/gb.h>

typedef struct {
  BATTLE_SKILL id;
  const unsigned char name[8];
  BYTE cost;
  SKILL_TARGET target;
} skill_data;

extern const skill_data skill_db[];
void load_skill(skill_data * skill, BATTLE_SKILL skill_id) BANKED;
#endif