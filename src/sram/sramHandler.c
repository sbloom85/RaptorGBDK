#include "../gb.h"
#include "../spriteStructs.h"

#include "sramHandler.h"

extern struct Player ship;

char playerName[12] = {"PlayerName"};
char playerCoSign[12] = {"CallSign"};
struct Player shipData;

void saveData()
{
    ENABLE_RAM;

    SWITCH_RAM(0);
    
    shipData.cashAmount = ship.cashAmount;
    shipData.colliderBottom = ship.colliderBottom;
    shipData.colliderLeft = ship.colliderLeft;
    shipData.colliderRight = ship.colliderRight;
    shipData.colliderTop = ship.colliderTop;
    shipData.curHealth = ship.curHealth;
    shipData.curShield = ship.curShield;
    shipData.enabled = ship.enabled;
    shipData.height = ship.height;
    shipData.ionScanner = ship.ionScanner;
    shipData.mBomb = ship.mBomb;
    shipData.numShields = ship.numShields;

    DISABLE_RAM;
}

void loadData()
{
    ENABLE_RAM;

    SWITCH_RAM(0);

    ship.cashAmount = shipData.cashAmount;
    ship.colliderBottom = shipData.colliderBottom;
    ship.colliderLeft = shipData.colliderLeft;
    ship.colliderRight = shipData.colliderRight;
    ship.colliderTop = shipData.colliderTop;
    ship.curHealth = shipData.curHealth;
    ship.curShield = shipData.curShield;
    ship.enabled = shipData.enabled;
    ship.height = shipData.height;
    ship.ionScanner = shipData.ionScanner;
    ship.mBomb = shipData.mBomb;
    ship.numShields = shipData.numShields;

    DISABLE_RAM;
}