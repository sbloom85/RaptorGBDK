#ifndef PROJECTILE_H_INCLUDE
#define PROJECTILE_H_INCLUDE
#include <gb/gb.h>
#include "../sprites/WProjectiles.h"

struct projectile {
    uint8_t id;
    uint8_t x;
    uint8_t y;
    uint8_t enabled:4,
            finished:4;
};

#endif