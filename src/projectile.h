#include "gb.h"
#include "../sprites/MchBullet.h"

struct projectile {
    uint8_t id;
    int16_t x;
    int16_t y;
    uint8_t enabled;
};