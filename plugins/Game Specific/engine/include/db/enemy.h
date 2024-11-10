#ifndef FF_DB_ENEMY
#define FF_DB_ENEMY

#include "enemy_data.h"
#include "enemy_data/imp.h"
#include "enemy_data/mad_pony.h"
#include "enemy_data/wolf.h"

const enemy_data * enemy_db[] = {
    [IMP] = &imp,
    [MADPONY] = &mad_pony,
    [WOLF] = &wolf
};

#endif