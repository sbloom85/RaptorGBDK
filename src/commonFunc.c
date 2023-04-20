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
#include <gb/sgb.h>
#include <gb/cgb.h>
#include "../sounds/hUGEDriver.h"
#endif
#ifdef __TARGET_gg
#include <sms/sms.h>
#endif
#include "commonFunc.h"

#include <stdio.h>
#include <stdlib.h>

#include <string.h>

int8_t BGP_REG_OLD;

static const uint16_t fadeout_palette[] = {RGB_WHITE, RGB_LIGHTGRAY,  RGB_DARKGRAY, RGB_BLACK, RGB_BLACK, RGB_BLACK, RGB_BLACK};

// More CPU efficient delay
void PerformantDelay(uint8_t numLoops)
{
    for (uint8_t i = numLoops; i--;)
    {
        wait_vbl_done();
    }
}

void PerformantDelayMusic(uint8_t numLoops)
{
    for (uint8_t i = numLoops; i--;)
    {
        #ifdef __TARGET_gb
        hUGE_dosound();
        #endif
        #ifdef __TARGET_gg
        //Todo
        #endif
        wait_vbl_done();
    }
}

#ifdef __TARGET_gb
uint8_t getGBType()
{
    switch (_cpu) {
	case 0x01:
        if (sgb_check())
        {
            return 2; //SGB1
        } else {
            return 1; //DMG or MEGADUCK
        }
		break;
	case 0xFF:
		if (sgb_check())
        {
            return 4; //SGB2
        } else {
            return 3; //POCKET
        }
		break;
	case 0x11:
        if (_is_GBA)
        {
            return 6; //GBA
        } else {
            return 5; //COLOR
        }
		break;
	default:
		return 0; //OTHER
		break;
	}
}

//Thanks to GB Studio which the SGB code is based off.
typedef struct sgb_pal_packet_t {
    UBYTE cmd;
    UWORD palettes[7];
} sgb_pal_packet_t;

void SGBTransferPalettes(const UWORD *SGBPallete) NONBANKED
{
    sgb_pal_packet_t data;
    data.cmd = (SGB_PAL_01 << 3) | 1;
    memcpy(data.palettes, &SGBPallete[0], sizeof(data.palettes));
    sgb_transfer((void *)&data);
}

void fadein() NONBANKED
{
    for (int i = 4; --i;)
    {
        set_bkg_palette(0, 1, fadeout_palette + i);
        set_sprite_palette(0, 1, fadeout_palette + i);
        PerformantDelay(5);
    }
}
#endif

//Thanks to basxto for the fadeout code.
//Edited
void fadeout()
{
    #ifdef __TARGET_gb
    if (getGBType() == 5 || getGBType() == 6)
    {
        fadeoutCGB();
    } else {
        fadeoutDMG();
    }
    #endif
}

#ifdef __TARGET_gb
//Must be Banked to work
void fadeoutDMG() BANKED
{
    BGP_REG_OLD = BGP_REG;
    for (int i = 1; i != 4; ++i) 
    {
        BGP_REG = (0xFFE4 >> (i << 1));
        PerformantDelay(18);
    }
    BGP_REG = BGP_REG_OLD;

    set_bkg_tiles(0, 0, 20, 18, BlckScrTiles);
}

void fadeoutCGB() NONBANKED
{
    VBK_REG = 1;
    set_bkg_tiles(0, 0, 20, 18, Blank_map_attributes);
    VBK_REG = 0;

    for (int i = 1; i < 4; i++) 
    {
        set_bkg_palette(0, 1, fadeout_palette + i);
        set_sprite_palette(0, 1, fadeout_palette + i);
        PerformantDelay(18);
    }

    set_bkg_tiles(0, 0, 20, 18, BlckScrTiles);
}
#endif

//Thanks to DAN COX for the collison code.
uint8_t collisionCheck(uint8_t x1, uint8_t y1, uint8_t w1, uint8_t h1, uint8_t x2, uint8_t y2, uint8_t w2, uint8_t h2) 
{
	if ((x1 < (x2+w2)) && ((x1+w1) > x2) && (y1 < (h2+y2)) && ((y1+h1) > y2)) 
    {
		return 1;
	} else {
		return 0;
	}
}