#ifndef FF_ACTION_DATA
#define FF_ACTION_DATA
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
  PICK_ChoiceMade,
  PICK_EnablePlayer,
  PICK_HandleChoice,
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
} ACTION_TYPE ;

extern BYTE action_cursor;

#endif