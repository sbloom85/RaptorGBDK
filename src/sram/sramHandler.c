
/*-----------------------------------------------------------------------------
 *
 *  RaptorGBDK: A Gameboy Demake based off the MSDOS Game 
 *  Raptor: Call of the Shadows
 *  Copyright (C) 1994 by
 *  Apogee Software, Scott Host, Rich Fleider, Tim Neveu,  
 *  Matt Murphy, Robert Prince, Les Dorscheid, Steven Maines
 *
 *  This program is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU General Public License
 *  as published by the Free Software Foundation; either version 2
 *  of the License, or (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA
 *  02111-1307, USA.
 *
 *-----------------------------------------------------------------------------*/

#pragma bank 0

#ifdef __TARGET_gb
#include <gb/gb.h>
#endif
#ifdef __TARGET_gg
#include <sms/sms.h>
#endif
#include "../spriteStructs.h"

#include <stdio.h>
#include <string.h>

#include "sramHandler.h"

#define MAX_SAVES 4

extern struct PlayerData playData;

char playerName[12][MAX_SAVES];
char playerCoSign[12][MAX_SAVES];
struct PlayerData playSavData[MAX_SAVES];
//struct PlayerData playSavData[MAX_SAVES];

void saveData(uint8_t saveSlot)
{
    ENABLE_RAM;

    SWITCH_RAM(0);
    
    memcpy(playerName[saveSlot], "Test1", 5);
    memcpy(playerCoSign[saveSlot], "Test2", 5);

    playSavData[saveSlot].weapon = playData.weapon;
    playSavData[saveSlot].mBomb = playData.mBomb;
    playSavData[saveSlot].ionScanner = playData.ionScanner;
    playSavData[saveSlot].numShields = playData.numShields;

    playSavData[saveSlot].ownsMachGun = playData.ownsMachGun;
    playSavData[saveSlot].ownsAirMiss = playData.ownsAirMiss;
    playSavData[saveSlot].ownsGrnMiss = playData.ownsGrnMiss;
    playSavData[saveSlot].ownsPlasCannon = playData.ownsPlasCannon;
    playSavData[saveSlot].ownsDumbFire = playData.ownsDumbFire;
    playSavData[saveSlot].ownsMicroMiss = playData.ownsMicroMiss;
    playSavData[saveSlot].ownsPulseCannon = playData.ownsPulseCannon;
    playSavData[saveSlot].ownsDeathRay = playData.ownsDeathRay;

    playSavData[saveSlot].curHealth = playData.curHealth;
    playSavData[saveSlot].curShield = playData.curShield;
    playSavData[saveSlot].cashAmount = playData.cashAmount;

    DISABLE_RAM;
}

/*void loadData(uint8_t saveSlot)
{
    ENABLE_RAM;

    SWITCH_RAM(0);
    
    //memcpy(playerName[saveSlot], "Test1", 5);
    //memcpy(playerCoSign[saveSlot], "Test2", 5);

    ship.weapon = playSavData[saveSlot].weapon;
    ship.mBomb = playSavData[saveSlot].mBomb;
    ship.ionScanner = playSavData[saveSlot].ionScanner;
    ship.numShields = playSavData[saveSlot].numShields;

    ship.ownsMachGun = playSavData[saveSlot].ownsMachGun;
    ship.ownsAirMiss = playSavData[saveSlot].ownsAirMiss;
    ship.ownsGrnMiss = playSavData[saveSlot].ownsGrnMiss;
    ship.ownsPlasCannon = playSavData[saveSlot].ownsPlasCannon;
    ship.ownsDumbFire = playSavData[saveSlot].ownsDumbFire;
    ship.ownsMicroMiss = playSavData[saveSlot].ownsMicroMiss;
    ship.ownsPulseCannon = playSavData[saveSlot].ownsPulseCannon;
    ship.ownsDeathRay = playSavData[saveSlot].ownsDeathRay;

    ship.curHealth = playSavData[saveSlot].curHealth;
    ship.curShield = playSavData[saveSlot].curShield;
    ship.cashAmount = playSavData[saveSlot].cashAmount;

    DISABLE_RAM;
}*/