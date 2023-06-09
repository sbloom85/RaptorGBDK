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

#pragma bank 3

#ifdef __TARGET_gb
#include <gb/gb.h>
#include <gb/cgb.h>
#endif
#ifdef __TARGET_gg
#include <sms/sms.h>
#endif

#include "maps.h"

#include "commonFunc.h"
#include "spriteHandler.h"
#include "gameHandler.h"
#include "gameSectionsCommon.h"
#include "gameSectionsB0.h"
#include "gameSectionsB3.h"

#include "sram/sramHandler.h"

const enum selected {Shop = 0, Fly = 1, Save = 2, Exit = 3};

static const uint16_t black_palette[] = {RGB_BLACK, RGB_BLACK, RGB_BLACK, RGB_BLACK, RGB_BLACK, RGB_BLACK, RGB_BLACK};

struct PlayerData playData;

void initPlayer()
{
    playData.weapon = 0;
    playData.mBomb = 0;
    playData.ionScanner = 0;
    playData.numShields = 0;

    playData.ownsMachGun = 1;
    playData.ownsAirMiss = 0;
    playData.ownsGrnMiss = 0;
    playData.ownsPlasCannon = 0;
    playData.ownsDumbFire = 0;
    playData.ownsMicroMiss = 0;
    playData.ownsPulseCannon = 0;
    playData.ownsDeathRay = 0;

    playData.curHealth = 75;
    playData.curShield = 0;
    playData.cashAmount = 10000;
}

void WepShop()
{
    set_bkg_palette(0, 4, &bkgShopPalette[0]);
    
    set_bkg_data(0, 47, ShopTiles);

    #ifdef __TARGET_gb
    if (sgb_check()) {
        SGBTransferPalettes(bkgShopPalette);
    }
    

    VBK_REG = 1;
    set_bkg_tiles(0, 0, 20, 18, ShopScreenPLN1);
    VBK_REG = 0;
    #endif
    set_bkg_tiles(0, 0, 20, 18, ShopScreenPLN0);
    

    HIDE_SPRITES;
    SHOW_BKG;

    while (1)
    {
        wait_vbl_done();
        
        if (joypad() & J_A)
        {
            fadeout();
            HIDE_BKG;
            SHOW_SPRITES;
            Hanger();
        }
    }
}

void HangerSelection(enum selected selection)
{
    #ifdef __TARGET_gb
    if (selection == Fly)
    {
        MoveCursor(28, 115);
    } else if (selection == Shop)
    {
        MoveCursor(135, 111);
    } else if (selection == Save)
    {
        MoveCursor(104, 59);
    } else //Exit
    {
        MoveCursor(80, 144);
    }
    #endif
    #ifdef __TARGET_gg
    if (selection == Fly)
    {
        MoveCursor(68, 115);
    } else if (selection == Shop)
    {
        MoveCursor(173, 115);
    } else if (selection == Save)
    {
        MoveCursor(142, 66);
    } else //Exit
    {
        MoveCursor(120, 154);
    }
    #endif
}

void Hanger() NONBANKED
{
    //Prevents accidentally activating an option
    PerformantDelay(8);

    #ifdef __TARGET_gb
    hUGE_init(&RapHanger);
    hUGE_dosound();
    #endif

    #ifdef __TARGET_gb
    //Helps hide some graphics corruption
    set_bkg_palette(0, 1, &black_palette[0]);
    
    set_bkg_data(0, Hanger_TILE_COUNT, Hanger_tiles);
    set_bkg_palette(0, Hanger_PALETTE_COUNT, &Hanger_palettes[0]);
    
    if (sgb_check()) {
        SGBTransferPalettes(Hanger_palettes);
    }
    
    VBK_REG = 1;
    set_bkg_tiles(0, 0, 20, 18, Hanger_map_attributes);
    VBK_REG = 0;
    
    set_bkg_tiles(0, 0, 20, 18, Hanger_map);
    #endif
    
    #ifdef __TARGET_gg
    set_palette(0, HangerGG_PALETTE_COUNT, &HangerGG_palettes[0]);

    set_bkg_4bpp_data(0, HangerGG_TILE_COUNT, HangerGG_tiles);

    set_tile_map_compat(0, 0, 20, 18, HangerGG_map);
    #endif

    enum selected selection;
    selection = 1;

    InitCursor();
    #ifdef __TARGET_gb
    MoveCursor(28, 115); //Default to Fly for now.
    #endif
    #ifdef __TARGET_gg
    MoveCursor(68, 115); //Default to Fly for now.
    #endif

    initPlayer();

    SHOW_SPRITES;
    SHOW_BKG;

    while (1)
    {
        uint8_t joyInput = joypad();

        //PerformantDelay(8);

        for (uint16_t i = 8; i--;)
        {
            #ifdef __TARGET_gb
            hUGE_dosound();
            #endif
            #ifdef __TARGET_gg
            //Todo
            #endif
            wait_vbl_done();
        }

        if (joyInput & J_LEFT)
        {
            if (selection > 0)
            {
                selection--;
            } else {
                selection = 3;
            }

            HangerSelection(selection);

        } else if (joyInput & J_RIGHT) {
            if (selection < 3)
            {
                selection++;
            } else {
                selection = 0;
            }

            HangerSelection(selection);
        }

        if (joyInput & J_UP)
        {
            if (selection > 0)
            {
                selection--;
            } else {
                selection = 3;
            }

            HangerSelection(selection);

        } else if (joyInput & J_DOWN) {
            if (selection < 3)
            {
                selection++;
            } else {
                selection = 0;
            }

            HangerSelection(selection);
        }

        if (joyInput & J_A && selection == Fly)
        {
            HIDE_SPRITES;
            fadeout();
            gameInit();
            BravoOne();
            gameLoop();
        } else if (joyInput & J_A && selection == Shop) {
            fadeout();
            WepShop();
        } else if (joyInput & J_A && selection == Save) {
            saveData(0);
        } else if (joyInput & J_A && selection == Exit) {
            fadeout();
            SWITCH_ROM(1);
            HIDE_SPRITES;
            Menu();
            //reset();
        }
    }
}