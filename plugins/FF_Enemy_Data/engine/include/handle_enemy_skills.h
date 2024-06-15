#ifndef FF_HANDLE_ENEMY_SKILLS
#define FF_HANDLE_ENEMY_SKILLS

#include <stdint.h>
#include <vm.h>

#define GET_GLOBAL_VAL(X) *(int16_t *)VM_REF_TO_PTR(X)
#define GET_GLOBAL_PTR(X) (int16_t *)VM_REF_TO_PTR(X)

enum { GOBLIN_PUNCH, HOWL };
void goblinPunch(SCRIPT_CTX *THIS) OLDCALL BANKED;
void howl(SCRIPT_CTX *THIS) OLDCALL BANKED;

// only 129 enemies in FF1
//
// Maybe I should have this be a Family based thing.
// Bosses get up to 12
// Max seems to be 12
// Most enemies look like they have 4
enum { IMP, GRIMP };
int8_t enemy_skills[2][5] = {[IMP] = {GOBLIN_PUNCH}, [GRIMP] = {GOBLIN_PUNCH}};

void handleChooseEnemySkill(SCRIPT_CTX *THIS) OLDCALL BANKED;
void handleEnemySkills(SCRIPT_CTX *THIS) OLDCALL BANKED;
#endif