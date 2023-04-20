/*-----------------------------------------------------------------------------
 *
 *  RaptorGB: a Gameboy Demake based off the MSDOS Game 
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

#ifndef MAPS_H_INCLUDE
#define MAPS_H_INCLUDE

#ifdef __TARGET_gb
#include <gb/gb.h>
#include <gb/cgb.h>
#endif
#ifdef __TARGET_gg
#include <sms/sms.h>
#endif

#include "../backgrounds/Title.h"
#include "../backgrounds/TitleGG.h"
#include "../backgrounds/Menu.h"
#include "../backgrounds/MenuGG.h"
#include "../backgrounds/Hanger.h"
#include "../backgrounds/HangerGG.h"
#include "../backgrounds/Shop.h"
#include "../backgrounds/ShopTiles.h"

#include "../maps/TileAttributes.h"

#include "../maps/BravoW1TilesMain.h"
#include "../maps/BravoW1TilesSGB.h"
#include "../maps/BravoW1TilesVBank1.h"
#include "../maps/BravoW1TilesGG.h"
#include "../maps/BravoW1Map.h"
#include "../maps/BravoW1MapGG.h"

extern unsigned char *currentMapPLN0;
extern unsigned char *currentMapPLN1;
extern unsigned char *currentMapPLN2;

static unsigned char RaptorWindowUpdatePLN0[] =
{
  0x74,0x74,0x74,0x74,0x66,0x74,0x74,0x74,0x74,0x74,
  0x74,0x74,0x74,0x74,0x74,0x74,0x74,0x74,0x74,0x74,
  0x74,0x71,0x74,0x74,0x74,0x74,0x72,0x74,0x74,0x74,
  0x74,0x7E,0x7E,0x7E,0x7E,0x7E,0x74,0x73,0x74,0x74
};

static unsigned char RaptorWindowUpdateGGPLN0[] =
{
  0x6F,0x6F,0x6F,0x6F,0x70,0x6F,0x6F,0x6F,0x6F,0x6F,
  0x6F,0x6F,0x6F,0x6F,0x6F,0x6F,0x6F,0x6F,0x6F,0x6F,
  0x6F,0x7B,0x6F,0x6F,0x6F,0x6F,0x7C,0x6F,0x6F,0x6F,
  0x6F,0x84,0x84,0x84,0x84,0x84,0x6F,0x7D,0x6F,0x6F
};

static const UWORD bkgShopPalette[] = {
    ShopTilesCGBPal0c0, ShopTilesCGBPal0c1, ShopTilesCGBPal0c2, ShopTilesCGBPal0c3,
    ShopTilesCGBPal1c0, ShopTilesCGBPal1c1, ShopTilesCGBPal1c2, ShopTilesCGBPal1c3,
    ShopTilesCGBPal2c0, ShopTilesCGBPal2c1, ShopTilesCGBPal2c2, ShopTilesCGBPal2c3,
    ShopTilesCGBPal3c0, ShopTilesCGBPal3c1, ShopTilesCGBPal3c2, ShopTilesCGBPal3c3,
};

static const UWORD bkgSGBBravo1Palette[] = {
  RGB(31, 31, 20), RGB(0, 8, 16), RGB(0, 12, 20), RGB(6, 6, 6)
};

static const UWORD bkgBravo1Palette[] = {
	  Bravo1MapTilesMainCGBPal0c0, Bravo1MapTilesMainCGBPal0c1, Bravo1MapTilesMainCGBPal0c2, Bravo1MapTilesMainCGBPal0c3,
    Bravo1MapTilesMainCGBPal1c0, Bravo1MapTilesMainCGBPal1c1, Bravo1MapTilesMainCGBPal1c2, Bravo1MapTilesMainCGBPal1c3,
    Bravo1MapTilesMainCGBPal2c0, Bravo1MapTilesMainCGBPal2c1, Bravo1MapTilesMainCGBPal2c2, Bravo1MapTilesMainCGBPal2c3,
    Bravo1MapTilesMainCGBPal3c0, Bravo1MapTilesMainCGBPal3c1, Bravo1MapTilesMainCGBPal3c2, Bravo1MapTilesMainCGBPal3c3,
    Bravo1MapTilesMainCGBPal4c0, Bravo1MapTilesMainCGBPal4c1, Bravo1MapTilesMainCGBPal4c2, Bravo1MapTilesMainCGBPal4c3,
    Bravo1MapTilesMainCGBPal5c0, Bravo1MapTilesMainCGBPal5c1, Bravo1MapTilesMainCGBPal5c2, Bravo1MapTilesMainCGBPal5c3,
    Bravo1MapTilesMainCGBPal6c0, Bravo1MapTilesMainCGBPal6c1, Bravo1MapTilesMainCGBPal6c2, Bravo1MapTilesMainCGBPal6c3,
    Bravo1MapTilesMainCGBPal7c0, Bravo1MapTilesMainCGBPal7c1, Bravo1MapTilesMainCGBPal7c2, Bravo1MapTilesMainCGBPal7c3,
};

static const palette_color_t bkgBravo1SMSPalette[] = {
	  RGBHTML(0x000000), RGBHTML(0x555555), RGBHTML(0xAAAAAA), RGBHTML(0xFFFFFF),
    RGBHTML(0x000000), RGBHTML(0x005500), RGBHTML(0x00AA00), RGBHTML(0x00FF00),
    RGBHTML(0x000000), RGBHTML(0x0000AA), RGBHTML(0x0055AA), RGBHTML(0x00AAAA),
    RGBHTML(0x000000), RGBHTML(0xAA5500), RGBHTML(0xFF5500), RGBHTML(0xFFAA00),
};

#endif