#include "gb.h"
#include "sgb.h"
#include "cgb.h"
#include <stdio.h>
#include <stdlib.h>

#include <string.h>

#include "maps.h"

#include "commonFunc.h"
#include "spriteHandler.h"

#include "../Window/RaptorDialogTiles.h"
#include "../Window/RaptorWindow.h"

int8_t BGP_REG_OLD;

enum selected {Shop = 0, Fly = 1, Save = 2, Exit = 3};

static const uint16_t black_palette[] = {RGB_BLACK, RGB_BLACK, RGB_BLACK, RGB_BLACK};
static const uint16_t fadeout_palette[] = {RGB_WHITE, RGB_LIGHTGRAY,  RGB_DARKGRAY, RGB_BLACK, RGB_BLACK, RGB_BLACK, RGB_BLACK};

const UWORD bkgSGBPaletteTitle[] = {
	RGB_WHITE, RGB(15, 15, 15), RGB_RED, RGB(5, 5, 5)
};

const UWORD bkgSGBPaletteHanger[] = {
    RaptorMapTilesCGBPal0c0, RaptorMapTilesCGBPal0c1, RaptorMapTilesCGBPal0c2, RaptorMapTilesCGBPal0c3,
};

const UWORD bkgSGBPaletteWater[] = {
	RaptorMapTilesCGBPal1c0, RaptorMapTilesCGBPal1c1, RaptorMapTilesCGBPal2c2, RGB(5, 5, 5),
};

const UWORD bkgPalette[] = {
	RaptorMapTilesCGBPal0c0, RaptorMapTilesCGBPal0c1, RaptorMapTilesCGBPal0c2, RaptorMapTilesCGBPal0c3,
    RaptorMapTilesCGBPal1c0, RaptorMapTilesCGBPal1c1, RaptorMapTilesCGBPal1c2, RaptorMapTilesCGBPal1c3,
    RaptorMapTilesCGBPal2c0, RaptorMapTilesCGBPal2c1, RaptorMapTilesCGBPal2c2, RaptorMapTilesCGBPal2c3,
    RaptorMapTilesCGBPal3c0, RaptorMapTilesCGBPal3c1, RaptorMapTilesCGBPal3c2, RaptorMapTilesCGBPal3c3,
    RaptorMapTilesCGBPal4c0, RaptorMapTilesCGBPal4c1, RaptorMapTilesCGBPal4c2, RaptorMapTilesCGBPal4c3,
    RaptorMapTilesCGBPal5c0, RaptorMapTilesCGBPal5c1, RaptorMapTilesCGBPal5c2, RaptorMapTilesCGBPal5c3,
    RaptorMapTilesCGBPal6c0, RaptorMapTilesCGBPal6c1, RaptorMapTilesCGBPal6c2, RaptorMapTilesCGBPal6c3,
    RaptorMapTilesCGBPal7c0, RaptorMapTilesCGBPal7c1, RaptorMapTilesCGBPal7c2, RaptorMapTilesCGBPal7c3,
};

unsigned char RaptorWindowUpdatePLN0[] =
{
  0x75,0x75,0x75,0x75,0x48,0x49,0x49,0x49,0x49,0x49,
  0x49,0x49,0x49,0x49,0x49,0x75,0x75,0x75,0x75,0x75,
  0x75,0x5A,0x49,0x49,0x49,0x75,0x65,0x49,0x49,0x49,
  0x75,0x7D,0x7D,0x7D,0x7D,0x7D,0x75,0x69,0x76,0x75
};

// current and old positions of the camera in pixels
int16_t camera_y, old_camera_y;
// current and old position of the map in tiles
uint8_t map_pos_y, old_map_pos_y;

//Thanks to GB Studio which the SGB code is based off.
typedef struct sgb_pal_packet_t {
    UBYTE cmd;
    UWORD palettes[7];
} sgb_pal_packet_t;

void SGBTransferPalettes(const UWORD *SGBPallete) BANKED {
    sgb_pal_packet_t data;
    data.cmd = (SGB_PAL_01 << 3) | 1;
    memcpy(data.palettes, &SGBPallete[0], sizeof(data.palettes));
    sgb_transfer((void *)&data);
}

struct windowDataStruct {
    uint8_t CashP1:4,
            CashP2:4;
    uint8_t CashP3:4,
            CashP4:4;
    uint8_t CashP5:4,
            CashP6:4;
    uint8_t CashP7:4,
            CashP8:4;
    uint8_t CashP9:4;

    uint8_t HlthP1:4,
            HlthP2:4;
    uint8_t HlthP3:4;

    uint8_t ShldP1:4,
            ShldP2:4;
    uint8_t ShldP3:4;
} windowData;

void updateHud()
{
    for (uint8_t i = 40; i--;)
    {
        //Line 1
        if (i < 4 || i > 14 && i < 20) //Empty Space
        {
            RaptorWindowUpdatePLN0[i] = 0x75;
        }
        if (i == 4) //Cash Sign
        {
            RaptorWindowUpdatePLN0[i] = 0x48;
        }
        if (i == 5) //Cash Pos 1
        {
            RaptorWindowUpdatePLN0[i] = 0x49 + windowData.CashP1;
        }
        if (i == 6) //Cash Pos 2
        {
            RaptorWindowUpdatePLN0[i] = 0x49 + windowData.CashP2;
        }
        if (i == 7) //Cash Pos 3
        {
            RaptorWindowUpdatePLN0[i] = 0x49 + windowData.CashP3;
        }
        if (i == 8) //Cash Pos 4
        {
            RaptorWindowUpdatePLN0[i] = 0x49 + windowData.CashP4;
        }
        if (i == 9) //Cash Pos 5
        {
            RaptorWindowUpdatePLN0[i] = 0x49 + windowData.CashP5;
        }
        if (i == 10) //Cash Pos 6
        {
            RaptorWindowUpdatePLN0[i] = 0x49 + windowData.CashP6;
        }
        if (i == 11) //Cash Pos 7
        {
            RaptorWindowUpdatePLN0[i] = 0x49 + windowData.CashP7;
        }
        if (i == 12) //Cash Pos 8
        {
            RaptorWindowUpdatePLN0[i] = 0x49 + windowData.CashP8;
        }
        if (i == 13) //Cash Pos 9
        {
            RaptorWindowUpdatePLN0[i] = 0x49 + windowData.CashP9;
        }
        
        //Line 2
        if (i == 20 || i == 25 || i == 30 || i == 36 || i == 39) //Empty Space
        {
            RaptorWindowUpdatePLN0[i] = 0x75;
        }
        if (i == 21) //H Char
        {
            RaptorWindowUpdatePLN0[i] = 0x5A;
        }
        if (i == 22) //Health Pos 1
        {
            RaptorWindowUpdatePLN0[i] = 0x49 + windowData.HlthP1;
        }
        if (i == 23) //Health Pos 2
        {
            RaptorWindowUpdatePLN0[i] = 0x49 + windowData.HlthP2;
        }
        if (i == 24) //Health Pos 3
        {
            RaptorWindowUpdatePLN0[i] = 0x49 + windowData.HlthP3;
        }
        if (i == 26) //S Char
        {
            RaptorWindowUpdatePLN0[i] = 0x65;
        }
        if (i == 27) //Shield Pos 1
        {
            RaptorWindowUpdatePLN0[i] = 0x49  + windowData.ShldP1;
        }
        if (i == 28) //Shield Pos 2
        {
            RaptorWindowUpdatePLN0[i] = 0x49  + windowData.ShldP2;
        }
        if (i == 29) //Shield Pos 3
        {
            RaptorWindowUpdatePLN0[i] = 0x49  + windowData.ShldP3;
        }
        if (i == 31) //Shield Icon Pos 1
        {
            RaptorWindowUpdatePLN0[i] = 0x7D;
        }
        if (i == 32) //Shield Icon Pos 2
        {
            RaptorWindowUpdatePLN0[i] = 0x7D;
        }
        if (i == 33) //Shield Icon Pos 3
        {
            RaptorWindowUpdatePLN0[i] = 0x7D;
        }
        if (i == 34) //Shield Icon Pos 4
        {
            RaptorWindowUpdatePLN0[i] = 0x7D;
        }
        if (i == 35) //Shield Icon Pos 5
        {
            RaptorWindowUpdatePLN0[i] = 0x7D;
        }
        if (i == 37) //W Char
        {
            RaptorWindowUpdatePLN0[i] = 0x69;
        }
        if (i == 38) //Weapon
        {
            RaptorWindowUpdatePLN0[i] = 0x76;
        }
    }
}

void fadein()
{
    //BGP_REG_OLD = BGP_REG;
    for (int i = 4; --i;)
    {
        BGP_REG = (0xFFE4 >> (i << 1));
        set_bkg_palette(0, 1, fadeout_palette + i);
        set_sprite_palette(0, 1, fadeout_palette + i);
        PerformantDelay(20);
    }
    //BGP_REG = BGP_REG_OLD;
}

//Thanks to basxto for the fadeout code.
//Slightly edited.
void fadeout()
{
    BGP_REG_OLD = BGP_REG;
    for (int i = 1; i != 4; ++i) 
    {
        BGP_REG = (0xFFE4 >> (i << 1));
        set_bkg_palette(0, 1, fadeout_palette + i);
        set_sprite_palette(0, 1, fadeout_palette + i);
        PerformantDelay(20);
    }
    BGP_REG = BGP_REG_OLD;
}

void init_camera()
{
    camera_y = -154;
    old_camera_y = camera_y;

    // update hardware scroll position
    SCY_REG = camera_y;
}

void scroll_cam_up()
{
    if (camera_y > -2040)
    {
        camera_y--;
    }
}

void set_camera() {
    // update hardware scroll position
    SCY_REG = camera_y;

    map_pos_y = (uint8_t)(camera_y >> 3u); //Row that updates + 18u updates last line.
    if (map_pos_y != old_map_pos_y) { 
        if (camera_y < old_camera_y) {
            VBK_REG = 1;
            set_bkg_submap(0, map_pos_y, 20, 1, BravoWave1PLN1, 20);
            VBK_REG = 0;
            set_bkg_submap(0, map_pos_y, 20, 1, BravoWave1PLN0, 20);

            updateHud();
            VBK_REG = 1;
            set_win_tiles(0, 0, 20, 2, RaptorWindowPLN1);
            VBK_REG = 0;
            set_win_tiles(0, 0, 20, 2, RaptorWindowUpdatePLN0);
        }
        old_map_pos_y = map_pos_y; 
    }
    
    // set old camera position to current camera position
    old_camera_y = camera_y;
}

void Title()
{
    set_bkg_palette(0, Intro_PALETTE_COUNT, &Intro_palettes[0]);
    set_bkg_data(0, Intro_TILE_COUNT, Intro_tiles);
    if (sgb_check()) {
        SGBTransferPalettes(bkgSGBPaletteTitle);
    }
    //VBK_REG = 1;
    set_bkg_tiles(0, 0, 20, 18, Intro_map);
    //VBK_REG = 0;
    //set_bkg_tiles(0, 0, 20, 18, Intro_map);

    while (1)
    {
        if (joypad() & J_A)
        {
            fadeout();
            break;
        }
    }
}

void HangerSelection(enum selected selection)
{
    if (selection == Fly)
    {
        MoveCursor(30, 74);
    } else if (selection == Shop)
    {
        MoveCursor(135, 74);
    } else if (selection == Save)
    {
        MoveCursor(150, 50);
    } else //Exit
    {
        MoveCursor(80, 140);
    }
}

void Hanger()
{
    set_bkg_palette(0, 1, &black_palette[0]); //Helps hide some graphics corruption
    set_bkg_data(0, Hanger_TILE_COUNT, Hanger_tiles);
    set_bkg_palette(0, Hanger_PALETTE_COUNT, &Hanger_palettes[0]);
    
    if (sgb_check()) {
        SGBTransferPalettes(bkgSGBPaletteHanger);
    }

    //VBK_REG = 1;
    set_bkg_tiles(0, 0, 20, 18, Hanger_map);
    //VBK_REG = 0;
    //set_bkg_tiles(0, 0, 20, 18, Intro_map);

    enum selected selection;
    selection = 1;

    InitCursor();
    MoveCursor(30, 74); //Default to Fly for now.

    while (1)
    {
        uint8_t joyInput = joypad();

        delay(100);

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
            fadeout();
            break;
        } /*else if (joyInput & J_A && selection == Shop) {
            //Todo
        } else if (joyInput & J_A && selection == Save) {
            //Todo
        }*/ else if (joyInput & J_A && selection == Exit) {
            reset();
        }
    }
}

void BravoOne()
{
    set_bkg_palette(0, 8, &bkgPalette[0]);
    set_bkg_data(0, 51, RaptorMapTiles);
    if (sgb_check()) {
        SGBTransferPalettes(bkgSGBPaletteWater);
    }

    //HIDE_WIN;

    map_pos_y = (uint8_t)(camera_y >> 3u);

    for (uint8_t i = 144; i--;)
    {
        VBK_REG = 1;
        set_bkg_submap(0, map_pos_y +i, 20, 1, BravoWave1PLN1, 20);
        VBK_REG = 0;
        set_bkg_submap(0, map_pos_y +i, 20, 1, BravoWave1PLN0, 20);
    }

    SHOW_WIN;

    set_win_data(72, 55, RaptorDialog);

    VBK_REG = 1;
    set_win_tiles(0, 0, 20, 2, RaptorWindowPLN1);
    VBK_REG = 0;
    set_win_tiles(0, 0, 20, 2, RaptorWindowUpdatePLN0);
    
    move_win(7, 128);

   /* 
    //Make this Cash line
    VBK_REG = 1;
    set_bkg_submap(0, map_pos_y, 20, 1, BravoWave1PLN1, 20);
    VBK_REG = 0;
    set_bkg_submap(0, map_pos_y, 20, 1, BravoWave1PLN0, 20);

    //Make this Health / Shield line
    VBK_REG = 1;
    set_bkg_submap(0, map_pos_y + 1, 20, 1, BravoWave1PLN1, 20);
    VBK_REG = 0;
    set_bkg_submap(0, map_pos_y + 1, 20, 1, BravoWave1PLN0, 20);
    */

    //map_pos_y = 0;
    old_map_pos_y = 255;
}