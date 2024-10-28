#ifndef FF_ACTION_HANDLER
#define FF_ACTION_HANDLER
#include <asm/types.h>

typedef enum {
  ATTACKER_Fight,
  ATTACKER_StartNextTurn,
  ATTACKER_TakeNextTurn,
  DEFENDER_TakeDamage,
  PANEL_ClosePanel,
  PANEL_DisplayCurrentActor,
  PANEL_DisplayMenu,
  PANEL_DisplayParty,
  PANEL_DisplayPartyActors,
  PANEL_HideCurrentActor,
  PANEL_HidePartyActors,
  PANEL_LoadItems,
  PANEL_OpenPanel,
  PICK_GetPlayerChoice,
  PICK_Item,
  PICK_Magic,
  PICK_Run,
  REPORT_AttackResults,
  REPORT_Prepare,
  REPORT_RejectMenuChoice,
  SCENE_FadeIn,
  TURN_BuildInitiative,
  TURN_RollInitiative,
  TURN_SortInitiative,
} ACTION_TYPE;

void handle_action(ACTION_TYPE action_type) BANKED;
void take_action(void) BANKED;
void dispatch_action(ACTION_TYPE action_type) BANKED;
void init_actions(void) BANKED;
void attacker_prepareNextTurn_Hero(void) BANKED;
void attacker_prepareNextTurn_Enemy(void) BANKED;
#endif