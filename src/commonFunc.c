#pragma bank 0

#include "gb.h"
#include "sgb.h"
#include "cgb.h"
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

//Thanks to basxto for the fadeout code.
//Edited
void fadeout()
{
    if (getGBType() == 5 || getGBType() == 6)
    {
        fadeoutCGB();
    } else {
        fadeoutDMG();
    }
}

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