#ifndef SPRITESRCT_H_INCLUDE
#define SPRITESRCT_H_INCLUDE

#ifdef __TARGET_gb
#include <gb/gb.h>
#endif
#if defined(__TARGET_sms) || defined(__TARGET_gg)
#include <sms/sms.h>
#endif

enum dmgTypes {DmgNormal = 0, DmgMissile = 1, DmgBomb = 3};
enum weapons {MachGun = 0, AirMiss = 1, GrnMiss = 2,
              PlasCannon = 3, DumbFire = 4, DeathRay = 5};

#define MAX_SAVES 4

struct PlayerData {
    uint8_t  weapon:3,          // Upto 7 diffrent weapons
             mBomb:2,           // Upto 3 mega bombs
             ionScanner:1;      // Bool
    uint8_t  numShields;        // Values upto 255
    uint8_t  ownsMachGun:1,     // Bool
             ownsAirMiss:1,     // Bool
             ownsGrnMiss:1,     // Bool
             ownsPlasCannon:1,  // Bool
             ownsDumbFire:1,    // Bool
             ownsMicroMiss:1,   // Bool
             ownsPulseCannon:1, // Bool
             ownsDeathRay:1;    // Bool
    int8_t   curHealth,         // Values upto 127
             curShield;         // Values upto 127
    int32_t  cashAmount;        // Values upto 2147483647
};

// Generic character structure: id, position, graphics
struct PlayerShip
{
    uint8_t  spriteids[12];     // Character uses 12 sprites
    uint8_t  x, y,              // Character X and Y positions
             width, height;     // Character width and height
    uint8_t  visible:1,         // Bool
             enabled:1;         // Bool

    uint8_t  colliderLeft;      // Left collider
    uint8_t  colliderRight;     // Right collider
    uint8_t  colliderTop;       // Top collider
    uint8_t  colliderBottom;    // Bottom collider
};

struct Enemy {
    uint8_t  spriteids[12];     // Character uses 12 sprites
    int16_t  x, y;              // Character X and Y positions
    uint8_t  width, height;     // Character width and height
    uint8_t  visible:1,         // Bool
             enabled:1,         // Bool
             dmgType:2,         // Values upto 3
             speed:4;           // Values upto 15
    uint8_t  dmgAmount;         // Values upto 255
    uint8_t  health;            // Values upto 255
    uint16_t cashGiven;         // Values upto 65535
    uint8_t  colliderLeft;      // Left collider
    uint8_t  colliderRight;     // Right collider
    uint8_t  colliderColTop;    // Top collider
    uint8_t  colliderBottom;    // Bottom collider
};

#endif