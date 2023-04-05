#pragma bank 2

#include "../gb.h"
#include "../spriteStructs.h"

#include "sramHandler.h"

extern struct Player ship;

//8 Arrays each 12 Chars long
char playerName[12][8];
char playerCoSign[12][8];
struct Player shipSavData;

void saveData()
{
    ENABLE_RAM;

    SWITCH_RAM(0);
    
    playerName[0][0] = (char)"Test1";
    playerCoSign[0][0] = (char)"Test2";

    shipSavData.weapon = ship.weapon;
    shipSavData.mBomb = ship.mBomb;
    shipSavData.ionScanner = ship.ionScanner;
    shipSavData.numShields = ship.numShields;

    shipSavData.ownsMachGun = ship.ownsMachGun;
    shipSavData.ownsAirMiss = ship.ownsAirMiss;
    shipSavData.ownsGrnMiss = ship.ownsGrnMiss;
    shipSavData.ownsPlasCannon = ship.ownsPlasCannon;
    shipSavData.ownsDumbFire = ship.ownsDumbFire;
    shipSavData.ownsMicroMiss = ship.ownsMicroMiss;
    shipSavData.ownsPulseCannon = ship.ownsPulseCannon;
    shipSavData.ownsDeathRay = ship.ownsDeathRay;

    shipSavData.curHealth = ship.curHealth;
    shipSavData.curShield = ship.curShield;
    shipSavData.cashAmount = ship.cashAmount;
    
    DISABLE_RAM;
}

void loadData()
{
    ENABLE_RAM;

    SWITCH_RAM(0);

    playerName[0][0] = (char)"Test1";
    playerCoSign[0][0] = (char)"Test2";

    ship.weapon = shipSavData.weapon;
    ship.mBomb = shipSavData.mBomb;
    ship.ionScanner = shipSavData.ionScanner;
    ship.numShields = shipSavData.numShields;

    ship.ownsMachGun = shipSavData.ownsMachGun;
    ship.ownsAirMiss = shipSavData.ownsAirMiss;
    ship.ownsGrnMiss = shipSavData.ownsGrnMiss;
    ship.ownsPlasCannon = shipSavData.ownsPlasCannon;
    ship.ownsDumbFire = shipSavData.ownsDumbFire;
    ship.ownsMicroMiss = shipSavData.ownsMicroMiss;
    ship.ownsPulseCannon = shipSavData.ownsPulseCannon;
    ship.ownsDeathRay = shipSavData.ownsDeathRay;

    ship.curHealth = shipSavData.curHealth;
    ship.curShield = shipSavData.curShield;
    ship.cashAmount = shipSavData.cashAmount;

    DISABLE_RAM;
}