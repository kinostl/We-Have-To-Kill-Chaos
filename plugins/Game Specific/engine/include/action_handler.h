#ifndef FF_ACTION_HANDLER
#define FF_ACTION_HANDLER
#include "entity_data.h"
#include "enums.h"
#include <asm/types.h>

typedef enum {
  EMPTY_ACTION,
  ANIMATE_EnemyDefeated,
  ATTACKER_StartNextTurn,
  ATTACKER_TakeNextTurn,
  ATTACKER_FinishTurn,
  PANEL_ClosePanel,
  PANEL_DisplayCurrentActor,
  PANEL_DisplayMenu,
  PANEL_DisplayParty,
  PANEL_UpdateParty,
  PANEL_DisplayPartyActors,
  PANEL_HideCurrentActor,
  PANEL_HidePartyActors,
  PANEL_LoadItems,
  PANEL_OpenPanel,
  PICK_GetPlayerActionChoice,
  PICK_GetEnemyActionChoice,
  PICK_Item,
  PICK_Magic,
  PICK_Block,
  PICK_Run,
  REPORT_AttackResults,
  REPORT_Prepare,
  REPORT_RejectMenuChoice,
  SCENE_FadeIn,
  TURN_BuildInitiative,
  TURN_EndTurn,
} ACTION_TYPE;

typedef struct action_t {
  ACTION_TYPE action;
  struct action_t * next;
} action_t;

void handle_action(ACTION_TYPE action_type) BANKED;
void take_action(void) BANKED;
void dispatch_action(ACTION_TYPE action_type) BANKED;
void init_actions(void) BANKED;
void attacker_prepareNextTurn_Hero(void) BANKED;
void attacker_prepareNextTurn_Enemy(void) BANKED;
#endif