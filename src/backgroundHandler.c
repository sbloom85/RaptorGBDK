#include "gb.h"
#include "cgb.h"
#include <stdio.h>
#include <stdlib.h>

#include "maps.h"

#include "commonFunc.h"
#include "spriteHandler.h"

enum selected {Fly = 0, Shop = 1, Save = 2, Exit = 3};

const UWORD bkgPalette[] = {
	RaptorMapTilesCGBPal0c0, RaptorMapTilesCGBPal0c1, RaptorMapTilesCGBPal0c2, RaptorMapTilesCGBPal0c3,
    RaptorMapTilesCGBPal1c0, RaptorMapTilesCGBPal1c1, RaptorMapTilesCGBPal1c2, RaptorMapTilesCGBPal1c3,
    RaptorMapTilesCGBPal2c0, RaptorMapTilesCGBPal2c1, RaptorMapTilesCGBPal2c2, RaptorMapTilesCGBPal2c3,
    RaptorMapTilesCGBPal3c0, RaptorMapTilesCGBPal3c1, RaptorMapTilesCGBPal3c2, RaptorMapTilesCGBPal3c3,
};

// current and old positions of the camera in pixels
uint16_t camera_x, camera_y, old_camera_x, old_camera_y;
// current and old position of the map in tiles
uint8_t map_pos_x, map_pos_y, old_map_pos_x, old_map_pos_y;
// redraw flag, indicates that camera position was changed
uint8_t redraw;

void init_camera()
{
    camera_x = 0;
    //camera_y = 104;
    camera_y = 0;
    old_camera_x = camera_x; 
    old_camera_y = camera_y;

    redraw = TRUE;

    SCX_REG = camera_x; SCY_REG = camera_y;
}

void scroll_cam_up()
{
    camera_y--;
}

void set_camera() {
    // update hardware scroll position
    SCY_REG = camera_y; SCX_REG = camera_x; 
    // up or down
    map_pos_y = (uint8_t)(camera_y >> 3u);
    if (map_pos_y != old_map_pos_y) { 
        if (camera_y < old_camera_y) {
            VBK_REG = 1;
            set_bkg_submap(map_pos_x, map_pos_y, 20, 1, BravoWave1PLN1, 20);
            VBK_REG = 0;
            set_bkg_submap(map_pos_x, map_pos_y, 20, 1, BravoWave1PLN0, 20);
        } else {
            if ((BravoWave1Height - 18u) > map_pos_y)
            {
                VBK_REG = 1;
                set_bkg_submap(map_pos_x, map_pos_y + 18u, 20, 1, BravoWave1PLN1, 20);
                VBK_REG = 0;
                set_bkg_submap(map_pos_x, map_pos_y + 18u, 20, 1, BravoWave1PLN0, 20);
            }
                 
        }
        old_map_pos_y = map_pos_y; 
    }
    
    // set old camera position to current camera position
    old_camera_x = camera_x, old_camera_y = camera_y;
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
    } else if (selection == Exit)
    {
        MoveCursor(80, 140);
    }
}

void Hanger()
{
    set_bkg_palette(0, Hanger_PALETTE_COUNT, &Hanger_palettes[0]);
    set_bkg_data(0, Hanger_TILE_COUNT, Hanger_tiles);

    //VBK_REG = 1;
    set_bkg_tiles(0, 0, 20, 18, Hanger_map);
    //VBK_REG = 0;
    //set_bkg_tiles(0, 0, 20, 18, Intro_map);

    enum selected selection;
    selection = 0;

    InitCursor();
    MoveCursor(30, 74);

    while (1)
    {
        uint8_t joyInput = joypad();

        delay(100);

        if (joyInput & J_LEFT)
        {
            if (selection > 0)
            {
                selection--;
            }

            HangerSelection(selection);

        } else if (joyInput & J_RIGHT) {
            if (selection < 3)
            {
                selection++;
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
            //Title(); //Glitches
        }*/
    }
}

void BravoOne()
{
    set_bkg_palette(0, 4, &bkgPalette[0]);
    set_bkg_data(0, 51, RaptorMapTiles);

    VBK_REG = 1;
    set_bkg_submap(map_pos_x, map_pos_y, 20, 18, BravoWave1PLN1, 20);
    VBK_REG = 0;
    set_bkg_submap(map_pos_x, map_pos_y, 20, 18, BravoWave1PLN0, 20);

    map_pos_x = 0;
    //map_pos_y = 220;
    map_pos_y = 0;
    old_map_pos_x = 255;
    old_map_pos_y = 255;
}