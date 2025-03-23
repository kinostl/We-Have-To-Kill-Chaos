#ifndef FF_SKILL_DEFS
#define FF_SKILL_DEFS

#include <data/explosion_palettes.h>
#include <gb/gb.h>
#include "entity_data.h"
#include "enums.h"
#include "hero_data.h"
#include "position_data.h"

void display_skill(BATTLE_SKILL skill) BANKED;
BOOLEAN handle_skill(BATTLE_SKILL skill) BANKED;
void prepare_for_skill(BATTLE_SKILL skill) BANKED;
void spend_ap_for_skill(BATTLE_SKILL skill_id, hero_data * hero) BANKED;

typedef enum {
    FIGHT_ATTACK,
    MAGIC_ATTACK,
    MAGIC_SUPPORT
} SKILL_TYPE ;

typedef struct {
    UBYTE damage;
    EXPLOSION_PALETTES color;
    SKILL_TYPE skill_type;
    BYTE number_of_hits;
    ATTACK_RESULTS attack_results;
    entity_data * target;
} ATTACK;

extern BYTE target_enemy;
extern ATTACK * damage_queue; //Arbitrary value not based on the docs, this queue is for multi-type attacks like Luster and Load
extern ATTACK * damage_queue_tail;
extern ATTACK * damage_queue_head;
#endif