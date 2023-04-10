#ifndef PROJECTILE_H_INCLUDE
#define PROJECTILE_H_INCLUDE
#ifdef __TARGET_gb
#include <gb/gb.h>
#endif
#if defined(__TARGET_sms) || defined(__TARGET_gg)
#include <sms/sms.h>
#endif
#include "../sprites/WProjectiles.h"

struct projectile {
    uint8_t id;
    uint8_t x;
    uint8_t y;
    uint8_t enabled:4,
            finished:4;
};

#endif