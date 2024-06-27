#pragma bank 255

#include <stdint.h>

enum {
    IMP,
    WOLF,
    BONE,
    CREEP,
    GHOST,
    ZOMBIE,
    MADPONY,
    GARLAND
};

const int8_t enemy_comps[16][4] = {
    { IMP, WOLF },
    { BONE, CREEP },
    { GHOST, ZOMBIE },
    { MADPONY },
    { GARLAND },
};