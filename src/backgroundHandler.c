#include "gb.h"
#include "sgb.h"
#include "cgb.h"
#include <stdio.h>
#include <stdlib.h>

#include <string.h>

#include "maps.h"

#include "commonFunc.h"
#include "spriteHandler.h"

enum selected {Shop = 0, Fly = 1, Save = 2, Exit = 3};

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
};

// current and old positions of the camera in pixels
int32_t camera_y, old_camera_y;
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
    // up or down
    map_pos_y = (uint8_t)(camera_y >> 3u); //Row that updates + 18u updates last line.
    if (map_pos_y != old_map_pos_y) { 
        if (camera_y < old_camera_y) {
            VBK_REG = 1;
            set_bkg_submap(0, map_pos_y, 20, 1, BravoWave1PLN1, 20);
            VBK_REG = 0;
            set_bkg_submap(0, map_pos_y, 20, 1, BravoWave1PLN0, 20);
        } else {
            if ((BravoWave1Height - 18u) > map_pos_y)
            {
                VBK_REG = 1;
                set_bkg_submap(0, map_pos_y + 18u, 20, 1, BravoWave1PLN1, 20);
                VBK_REG = 0;
                set_bkg_submap(0, map_pos_y + 18u, 20, 1, BravoWave1PLN0, 20);
            }  
        }
        old_map_pos_y = map_pos_y; 
    }
    
    // set old camera position to current camera position
    old_camera_y = camera_y;
}

void FadeIn()
{
    for (uint8_t i = 4; i--;)
    {
        switch(i)
        {
            case 4:
                BGP_REG = 0xFF;
            break;
            
            case 3:
                BGP_REG = 0xFE;
                break;
            
            case 2:
                BGP_REG = 0xF9;
                break;
            
            case 1:
                BGP_REG = 0xE4;
                break;
        }
        PerformantDelay(100);
    }
}

void FadeOut()
{
    for (uint8_t i = 4; i--;)
    {
        switch(i)
        {
            case 4:
                BGP_REG = 0xE4;
            break;
            
            case 3:
                BGP_REG = 0xF9;
                break;
            
            case 2:
                BGP_REG = 0xFE;
                break;
            
            case 1:
                BGP_REG = 0xFF;
                break;
        }
        PerformantDelay(100);
    }
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
    set_bkg_palette(0, Hanger_PALETTE_COUNT, &Hanger_palettes[0]);
    set_bkg_data(0, Hanger_TILE_COUNT, Hanger_tiles);
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
            break;
        } /*else if (joyInput & J_A && selection == Shop) {
            //Todo
        } else if (joyInput & J_A && selection == Save) {
            //Todo
        } else if (joyInput & J_A && selection == Exit) {
            //Todo
        }*/
    }
}

void BravoOne()
{
    set_bkg_palette(0, 4, &bkgPalette[0]);
    set_bkg_data(0, 51, RaptorMapTiles);
    if (sgb_check()) {
        SGBTransferPalettes(bkgSGBPaletteWater);
    }

    map_pos_y = (uint8_t)(camera_y >> 3u);

    for (uint8_t i = 144; i--;)
    {
        VBK_REG = 1;
        set_bkg_submap(0, map_pos_y +i, 20, 1, BravoWave1PLN1, 20);
        VBK_REG = 0;
        set_bkg_submap(0, map_pos_y +i, 20, 1, BravoWave1PLN0, 20);
    }

    //map_pos_y = 0;
    old_map_pos_y = 255;
}