#pragma bank 2

#include "gb.h"
//#include "sgb.h"
#include "cgb.h"
#include "bgb_emu.h"
#include <stdio.h>
#include <stdlib.h>

#include <string.h>

#include "maps.h"

#include "commonFunc.h"
#include "spriteHandler.h"
#include "backgroundHandler.h"

#include "../Window/RaptorDialogTilesV2.h"
#include "../Window/RaptorWindowV2.h"

int8_t BGP_REG_OLD;

uint8_t mapTileSet = 0;
uint8_t currentTileBank = 3;
uint8_t currentMapBank = 5;
unsigned char *currentMapPLN0;
unsigned char *currentMapPLN1;

const enum selected {Shop = 0, Fly = 1, Save = 2, Exit = 3};

static const uint16_t black_palette[] = {RGB_BLACK, RGB_BLACK, RGB_BLACK, RGB_BLACK, RGB_BLACK, RGB_BLACK, RGB_BLACK};
static const uint16_t white_palette[] = {RGB_WHITE, RGB_WHITE, RGB_WHITE, RGB_WHITE, RGB_WHITE, RGB_WHITE, RGB_WHITE};
static const uint16_t fadeout_palette[] = {RGB_WHITE, RGB_LIGHTGRAY,  RGB_DARKGRAY, RGB_BLACK, RGB_BLACK, RGB_BLACK, RGB_BLACK};

unsigned char RaptorWindowUpdatePLN0[] =
{
  0x75,0x75,0x75,0x75,0x67,0x75,0x75,0x75,0x75,0x75,
  0x75,0x75,0x75,0x75,0x75,0x75,0x75,0x75,0x75,0x75,
  0x75,0x72,0x75,0x75,0x75,0x75,0x73,0x75,0x75,0x75,
  0x75,0x7D,0x7D,0x7D,0x7D,0x7D,0x75,0x74,0x75,0x75
};

// current and old positions of the camera in pixels
int16_t camera_y, old_camera_y;
// current and old position of the map in tiles
uint8_t map_pos_y;
uint8_t old_map_pos_y;

/*
//Thanks to GB Studio which the SGB code is based off.
typedef struct sgb_pal_packet_t {
    UBYTE cmd;
    UWORD palettes[7];
} sgb_pal_packet_t;

void SGBTransferPalettes(const UWORD *SGBPallete) BANKED
{
    sgb_pal_packet_t data;
    data.cmd = (SGB_PAL_01 << 3) | 1;
    memcpy(data.palettes, &SGBPallete[0], sizeof(data.palettes));
    sgb_transfer((void *)&data);
}*/

struct windowStruct {
    char Cash[10];
    char Health[3];
    char Shield[3];
} windowData;

void updateHud() BANKED
{
    //int32_t testCashVar = 2147483647;

    itoa32(ship.cashAmount, windowData.Cash);
    itoa8(ship.curHealth, windowData.Health);
    itoa8(ship.curShield, windowData.Shield);

    for (uint8_t i = 40; i--;)
    {
        //Line 1
        if (i == 5) //Cash Pos 0
        {
            RaptorWindowUpdatePLN0[i] = 0x68 + windowData.Cash[0] -48U;
        }
        if (i == 6) //Cash Pos 1
        {
            if (ship.cashAmount >= 10)
            {
                RaptorWindowUpdatePLN0[i] = 0x68 + windowData.Cash[1] -48U;
            }
        }
        if (i == 7) //Cash Pos 2
        {
            if (ship.cashAmount >= 100)
            {
                RaptorWindowUpdatePLN0[i] = 0x68 + windowData.Cash[2] -48U;
            }
        }
        if (i == 8) //Cash Pos 3
        {
            if (ship.cashAmount >= 1000)
            {
                RaptorWindowUpdatePLN0[i] = 0x68 + windowData.Cash[3] -48U;
            }
        }
        if (i == 9) //Cash Pos 4
        {
            if (ship.cashAmount >= 10000)
            {
                RaptorWindowUpdatePLN0[i] = 0x68 + windowData.Cash[4] -48U;
            }
        }
        if (i == 10) //Cash Pos 5
        {
            if (ship.cashAmount >= 100000)
            {
                RaptorWindowUpdatePLN0[i] = 0x68 + windowData.Cash[5] -48U;
            }
        }
        if (i == 11) //Cash Pos 6
        {
            if (ship.cashAmount >= 1000000)
            {
                RaptorWindowUpdatePLN0[i] = 0x68 + windowData.Cash[6] -48U;
            }
        }
        if (i == 12) //Cash Pos 7
        {
            if (ship.cashAmount >= 10000000)
            {
                RaptorWindowUpdatePLN0[i] = 0x68 + windowData.Cash[7] -48U;
            }
        }
        if (i == 13) //Cash Pos 8
        {
            if (ship.cashAmount >= 100000000)
            {
                RaptorWindowUpdatePLN0[i] = 0x68 + windowData.Cash[8] -48U;
            }
        }
        if (i == 14) //Cash Pos 9
        {
            if (ship.cashAmount >= 1000000000)
            {
                RaptorWindowUpdatePLN0[i] = 0x68 + windowData.Cash[9] -48U;
            }
        }
        
        //Line 2
        if (i == 22) //Health Pos 1
        {
            RaptorWindowUpdatePLN0[i] = 0x49 + windowData.Health[0] -17U;
        }
        if (i == 23) //Health Pos 2
        {
            if (ship.curHealth >= 10)
            {
                RaptorWindowUpdatePLN0[i] = 0x49 + windowData.Health[1] -17U;
            }
        }
        if (i == 24) //Health Pos 3
        {
            if (ship.curHealth >= 100)
            {
                RaptorWindowUpdatePLN0[i] = 0x49 + windowData.Health[2] -17U;
            }
        }
        if (i == 27) //Shield Pos 1
        {
            RaptorWindowUpdatePLN0[i] = 0x49 + windowData.Shield[0] -17U;
        }
        if (i == 28) //Shield Pos 2
        {
            if (ship.curShield >= 10)
            {
                RaptorWindowUpdatePLN0[i] = 0x49 + windowData.Shield[1] -17U;
            }
        }
        if (i == 29) //Shield Pos 3
        {
            if (ship.curShield >= 100)
            {
                RaptorWindowUpdatePLN0[i] = 0x49 + windowData.Shield[2] -17U;
            }
        }
        if (i == 31) //Shield Icon Pos 1
        {
            if (ship.numShields > 0)
                RaptorWindowUpdatePLN0[i] = 0x7D;
            else
                RaptorWindowUpdatePLN0[i] = 0x7C;
        }
        if (i == 32) //Shield Icon Pos 2
        {
            if (ship.numShields > 1)
                RaptorWindowUpdatePLN0[i] = 0x7D;
            else
                RaptorWindowUpdatePLN0[i] = 0x7C;
        }
        if (i == 33) //Shield Icon Pos 3
        {
            if (ship.numShields > 2)
                RaptorWindowUpdatePLN0[i] = 0x7D;
            else
                RaptorWindowUpdatePLN0[i] = 0x7C;
        }
        if (i == 34) //Shield Icon Pos 4
        {
            if (ship.numShields > 3)
                RaptorWindowUpdatePLN0[i] = 0x7D;
            else
                RaptorWindowUpdatePLN0[i] = 0x7C;
        }
        if (i == 35) //Shield Icon Pos 5
        {
            if (ship.numShields > 4)
                RaptorWindowUpdatePLN0[i] = 0x7D;
            else
                RaptorWindowUpdatePLN0[i] = 0x7C;
        }
        if (i == 38) //Weapon
        {
            RaptorWindowUpdatePLN0[i] = 0x76 + ship.weapon;
        }
    }
}

void fadeinCGB() BANKED
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

void fadein() BANKED
{
    
    for (int i = 3; i--;)
    {
        switch (i)
        {
            case 0:
                BGP_REG = 0xE4;
                break;
            case 1:
                BGP_REG = 0xF9;
                break;
            case 2:
                BGP_REG = 0xFE;
                break;
            case 3:
                BGP_REG = 0xFF;
                break;
        }
        //PerformantDelay(10);
    }
}

//Thanks to basxto for the fadeout code.
//Slightly edited.
void fadeoutCGB() BANKED
{
    BGP_REG_OLD = BGP_REG;
    for (int i = 1; i < 4; i++) 
    {
        BGP_REG = (0xFFE4 >> (i << 1));
        set_bkg_palette(0, 1, fadeout_palette + i);
        set_sprite_palette(0, 1, fadeout_palette + i);
        PerformantDelay(20);
    }
    BGP_REG = BGP_REG_OLD;
}

void fadeout() BANKED
{
    BGP_REG_OLD = BGP_REG;
    /*if (sgb_check()) {
        SGBTransferPalettes(fadeout_palette);
    }*/
    for (int i = 0; i < 4; i++)
    {
        switch (i)
        {
            case 0:
                BGP_REG = 0xE4;
                break;
            case 1:
                BGP_REG = 0xF9;
                break;
            case 2:
                BGP_REG = 0xFE;
                break;
            case 3:
                BGP_REG = 0xFF;
                break;
        }
        PerformantDelay(20);
    }
    BGP_REG = BGP_REG_OLD;
}

void init_camera() BANKED
{
    camera_y = -154;
    old_camera_y = camera_y;

    // update hardware scroll position
    SCY_REG = camera_y;
}

void scroll_cam_up() BANKED
{
    //Check frames for slight slow down.
    if (camera_y > -2048 && (IS_FRAME_ODD || IS_FRAME_4))
    {
        camera_y--;
    }

    if (camera_y < -1024)
    {
        mapTileSet = 1; //Switch map to second tileset.
        currentMapPLN1 = (unsigned char*)BravoWave1_2PLN1; //Todo make usable by any map.
    }
}

void set_camera() NONBANKED
{
    // update hardware scroll position
    SCY_REG = camera_y;

    SWITCH_ROM(currentMapBank);

    //Row that updates + 18u updates last line.
    map_pos_y = (uint8_t)(camera_y >> 3u); 
    if (map_pos_y != old_map_pos_y) { 
        if (camera_y < old_camera_y) {
            VBK_REG = VBK_ATTRIBUTES;
            set_bkg_based_submap(0, map_pos_y, 20, 1, (unsigned char*)currentMapPLN1, 20, 0);
            VBK_REG = VBK_TILES;
            if (mapTileSet)
            {
                set_bkg_based_submap(0, map_pos_y, 20, 1, (unsigned char*)currentMapPLN0, 20, 127);
            }
            else
            {
                set_bkg_based_submap(0, map_pos_y, 20, 1, (unsigned char*)currentMapPLN0, 20, 0);
            }
            updateHud();
            VBK_REG = VBK_ATTRIBUTES;
            set_win_tiles(0, 0, 20, 2, RaptorWindowPLN1);
            VBK_REG = VBK_TILES;
            set_win_tiles(0, 0, 20, 2, RaptorWindowUpdatePLN0);
            
        }
        old_map_pos_y = map_pos_y; 
    }
    
    // set old camera position to current camera position
    old_camera_y = camera_y;

    SWITCH_ROM(2);
}

void Title() NONBANKED
{
    set_bkg_palette(0, Intro_PALETTE_COUNT, &Intro_palettes[0]);
    set_bkg_data(0, Intro_TILE_COUNT, Intro_tiles);
    /*if (sgb_check()) {
        SGBTransferPalettes(bkgSGBPaletteTitle);
    }*/
    //VBK_REG = 1;
    set_bkg_tiles(0, 0, 20, 18, Intro_map);
    //VBK_REG = 0;
    //set_bkg_tiles(0, 0, 20, 18, Intro_map);

    PerformantDelay(130);
    if (getGBType() == 3)
    {
        fadeoutCGB();
    } else {
        fadeout();
    }
    HIDE_BKG;
}

void Menu() NONBANKED
{
    //fadeinnew();
    set_bkg_palette(0, Menu_PALETTE_COUNT, &Menu_palettes[0]);
    set_bkg_data(0, Menu_TILE_COUNT, Menu_tiles);
    /*if (sgb_check()) {
        SGBTransferPalettes(bkgSGBPaletteWater);
    }*/
    VBK_REG = 1;
    set_bkg_tiles(0, 0, 20, 18, Menu_map_attributes);
    VBK_REG = 0;
    set_bkg_tiles(0, 0, 20, 18, Menu_map);

    SHOW_BKG;

    while (1)
    {
        if (joypad() & J_A)
        {
            if (getGBType() == 3)
            {
                fadeoutCGB();
            } else {
                fadeout();
            }
            HIDE_BKG;
            SHOW_SPRITES;
            break;
        }
    }
}

void WepShop() BANKED
{
    //fadeinnew();
    set_bkg_palette(0, 4, &bkgShopPalette[0]);
    set_bkg_data(0, 47, ShopTiles);
    /*if (sgb_check()) {
        SGBTransferPalettes(bkgSGBPaletteWater);
    }*/

    VBK_REG = 1;
    set_bkg_tiles(0, 0, 20, 18, ShopScreenPLN1);
    VBK_REG = 0;
    set_bkg_tiles(0, 0, 20, 18, ShopScreenPLN0);

    HIDE_SPRITES;
    SHOW_BKG;

    while (1)
    {
        if (joypad() & J_A)
        {
            if (getGBType() == 3)
            {
                fadeoutCGB();
            } else {
                fadeout();
            }
            HIDE_BKG;
            SHOW_SPRITES;
            Hanger();
        }
    }
}

void gameInit() BANKED
{
    initProjectiles();
    init_camera();
    setupShip();
    //SetupEnemyShip();
    SetColliders();

    SHOW_SPRITES;
    SHOW_WIN;

    set_win_data(103, 24, RaptorDialog);

    VBK_REG = 1;
    set_win_tiles(0, 0, 20, 2, RaptorWindowPLN1);
    VBK_REG = 0;
    set_win_tiles(0, 0, 20, 2, RaptorWindowUpdatePLN0);

    move_win(7, 128);
}

void gameLoop() BANKED
{
    //Main Game Loop
    while (1)
    {
        game_time++;

        set_camera();

        scroll_cam_up();

        //MoveEnemy();

        moveProjectiles();

        inputLoop();

        PerformantDelay(2);
    }
}

void HangerSelection(enum selected selection) BANKED
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

void Hanger() BANKED
{
    //fadeinnew();
    //Helps hide some graphics corruption
    set_bkg_palette(0, 1, &black_palette[0]);
    set_bkg_data(0, Hanger_TILE_COUNT, Hanger_tiles);
    set_bkg_palette(0, Hanger_PALETTE_COUNT, &Hanger_palettes[0]);
    
    /*if (sgb_check()) {
        SGBTransferPalettes(bkgSGBPaletteHanger);
    }*/

    VBK_REG = 1;
    set_bkg_tiles(0, 0, 20, 18, Hanger_map_attributes);
    VBK_REG = 0;
    set_bkg_tiles(0, 0, 20, 18, Hanger_map);

    enum selected selection;
    selection = 1;

    InitCursor();
    MoveCursor(30, 74); //Default to Fly for now.

    SHOW_BKG;

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
            HIDE_SPRITES;
            if (getGBType() == 3)
            {
                fadeoutCGB();
            } else {
                fadeout();
            }
            gameInit();
            BravoOne();
            gameLoop();
        } else if (joyInput & J_A && selection == Shop) {
            WepShop();
        } /*else if (joyInput & J_A && selection == Save) {
            //Todo
        }*/ else if (joyInput & J_A && selection == Exit) {
            reset();
        }
    }
}

void BravoOne() NONBANKED
{
    mapTileSet = 0;
    set_bkg_palette(0, 8, &bkgBravo1Palette[0]);
    //Bank 3:
    //Bravo Map 1 and Enemy Sprites
    
    currentTileBank = 3;
    SWITCH_ROM(currentTileBank);

    //VBK_REG = 1;
    //set_bkg_data(0, 102, Bravo1MapTiles);
    //set_bkg_data(127, 102, Bravo1MapTiles);
    //VBK_REG = 0;
    set_bkg_data(0, 102, Bravo1MapTiles);
    set_bkg_data(127, 102, Bravo1MapTiles2);
    /*if (sgb_check()) {
        SGBTransferPalettes(bkgSGBPaletteWater);
    }*/

    map_pos_y = (uint8_t)(camera_y >> 3u);

    currentMapBank = 5;
    SWITCH_ROM(currentMapBank);

    currentMapPLN0 = (unsigned char*)BravoWave1PLN0;
    currentMapPLN1 = (unsigned char*)BravoWave1PLN1;
    
    for (uint8_t i = 144; i--;)
    {
        VBK_REG = VBK_ATTRIBUTES;
        set_bkg_based_submap(0, map_pos_y +i, 20, 1, (unsigned char*)currentMapPLN1, 20, 0);
        VBK_REG = VBK_TILES;
        set_bkg_based_submap(0, map_pos_y +i, 20, 1, (unsigned char*)currentMapPLN0, 20, 0);
    }

    gameLoop();

    //map_pos_y = 0;
    old_map_pos_y = 255;

    //Switch back to Bank 2 for Background Handler use.
    SWITCH_ROM(2);
}