#pragma bank 2

#include "gb.h"
#include "sgb.h"
#include "cgb.h"
#include <stdio.h>
#include <stdlib.h>

#include <string.h>

#include "maps.h"

#include "commonFunc.h"
#include "spriteHandler.h"
#include "backgroundHandler.h"

#include "../Window/RaptorDialogTiles.h"
#include "../Window/RaptorWindow.h"

int8_t BGP_REG_OLD;

uint8_t currentMapBank = 3;
unsigned char *currentMapPLN0;
unsigned char *currentMapPLN1;

const enum selected {Shop = 0, Fly = 1, Save = 2, Exit = 3};

static const uint16_t black_palette[] = {RGB_BLACK, RGB_BLACK, RGB_BLACK, RGB_BLACK};
static const uint16_t fadeout_palette[] = {RGB_WHITE, RGB_LIGHTGRAY,  RGB_DARKGRAY, RGB_BLACK, RGB_BLACK, RGB_BLACK, RGB_BLACK};

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

void SGBTransferPalettes(const UWORD *SGBPallete) BANKED
{
    sgb_pal_packet_t data;
    data.cmd = (SGB_PAL_01 << 3) | 1;
    memcpy(data.palettes, &SGBPallete[0], sizeof(data.palettes));
    sgb_transfer((void *)&data);
}

struct windowCashStruct {
    char Cash[10];
} windowCash;

    uint8_t HlthP1,
            HlthP2,
            HlthP3;

    uint8_t ShldP1,
            ShldP2,
            ShldP3;

uint8_t * splitter(uint32_t number) NONBANKED
{
    static uint8_t values[8];

    for (int i = 0; i < 8; i++)
    {
        values[i] = (uint8_t)(number & 0xF);
        number = (number >> 4);
    }

    return values;
}

char* itoa2(int i, char b[]) NONBANKED
{
    char const digit[] = "0123456789";
    char* p = b;
    if(i<0){
        *p++ = '-';
        i *= -1;
    }
    int shifter = i;
    do{ //Move to where representation ends
        ++p;
        shifter = shifter/10;
    }while(shifter);
    *p = '\0';
    do{ //Move back, inserting digits as u go
        *--p = digit[i%10];
        i = i/10;
    }while(i);
    return b;
}

void updateHud() NONBANKED
{
    uint32_t testCashVar = 1234;
    //sprintf(windowData.CashP0, "%u", 1);

    for (int i = 0; i < 10; i++)
    {
        windowCash.Cash[i] = 0;
    }

    //itoa(testCashVar, windowCash.Cash, 10);
    //itoa2(testCashVar, windowCash.Cash);

    //sprintf(windowCash.Cash, "%d", testCashVar >> 10);

    //memcpy(&windowCash.Cash, &testCashVar, sizeof(testCashVar));


    //windowData.CashP0 = splitter(testCashVar)[0];
    //windowData.CashP1 = (testCashVar >> 8) & 0xF;
    //windowData.CashP2 = testCashVar & 0x00F000000;
    //windowData.CashP3 = testCashVar & 0x000F00000;
    //windowData.CashP4 = testCashVar & 0x0000F0000;
    //windowData.CashP5 = (testCashVar * 68) & 0xF;
    //windowCash.CashP6 = (testCashVar >> 10) & 0xF;
    //windowCash.CashP7 = (testCashVar / 68) & 0xF;
    //windowData.CashP8 = (testCashVar / 309) & 0xF;
    //windowData.CashP9 = (testCashVar >> 8) & 0xFFFFFFFF;

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
        if (i == 5) //Cash Pos 0
        {
            RaptorWindowUpdatePLN0[i] = 0x49 + windowCash.Cash[0];
        }
        if (i == 6) //Cash Pos 1
        {
            RaptorWindowUpdatePLN0[i] = 0x49 + windowCash.Cash[1];
        }
        if (i == 7) //Cash Pos 2
        {
            RaptorWindowUpdatePLN0[i] = 0x49 + windowCash.Cash[2];
        }
        if (i == 8) //Cash Pos 3
        {
            RaptorWindowUpdatePLN0[i] = 0x49 + windowCash.Cash[3];
        }
        if (i == 9) //Cash Pos 4
        {
            RaptorWindowUpdatePLN0[i] = 0x49 + windowCash.Cash[4];
        }
        if (i == 10) //Cash Pos 5
        {
            RaptorWindowUpdatePLN0[i] = 0x49 + windowCash.Cash[5];
        }
        if (i == 11) //Cash Pos 6
        {
            RaptorWindowUpdatePLN0[i] = 0x49 + windowCash.Cash[6];
        }
        if (i == 12) //Cash Pos 7
        {
            RaptorWindowUpdatePLN0[i] = 0x49 + windowCash.Cash[7];
        }
        if (i == 13) //Cash Pos 8
        {
            RaptorWindowUpdatePLN0[i] = 0x49 + windowCash.Cash[8];
        }
        if (i == 14) //Cash Pos 9
        {
            RaptorWindowUpdatePLN0[i] = 0x49 + windowCash.Cash[9];
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
            //RaptorWindowUpdatePLN0[i] = 0x49 + windowData.HlthP1;
        }
        if (i == 23) //Health Pos 2
        {
            //RaptorWindowUpdatePLN0[i] = 0x49 + windowData.HlthP2;
        }
        if (i == 24) //Health Pos 3
        {
            //RaptorWindowUpdatePLN0[i] = 0x49 + windowData.HlthP3;
        }
        if (i == 26) //S Char
        {
            RaptorWindowUpdatePLN0[i] = 0x65;
        }
        if (i == 27) //Shield Pos 1
        {
            //RaptorWindowUpdatePLN0[i] = 0x49  + windowData.ShldP1;
        }
        if (i == 28) //Shield Pos 2
        {
            //RaptorWindowUpdatePLN0[i] = 0x49  + windowData.ShldP2;
        }
        if (i == 29) //Shield Pos 3
        {
            //RaptorWindowUpdatePLN0[i] = 0x49  + windowData.ShldP3;
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

void fadein() BANKED
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
void fadeout() BANKED
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

void init_camera() BANKED
{
    camera_y = -154;
    old_camera_y = camera_y;

    // update hardware scroll position
    SCY_REG = camera_y;
}

void scroll_cam_up() BANKED
{
    if (camera_y > -2040)
    {
        camera_y--;
    }
}

void set_camera() NONBANKED
{
    // update hardware scroll position
    SCY_REG = camera_y;

    #ifdef MEGADUCK
        SWITCH_ROM_MEGADUCK(currentMapBank);
    #else
        SWITCH_ROM_MBC5(currentMapBank);
    #endif

    //Row that updates + 18u updates last line.
    map_pos_y = (uint8_t)(camera_y >> 3u); 
    if (map_pos_y != old_map_pos_y) { 
        if (camera_y < old_camera_y) {
            VBK_REG = 1;
            set_bkg_submap(0, map_pos_y, 20, 1, (unsigned char*)currentMapPLN1, 20);
            VBK_REG = 0;
            set_bkg_submap(0, map_pos_y, 20, 1, (unsigned char*)currentMapPLN0, 20);

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

    #ifdef MEGADUCK
        SWITCH_ROM_MEGADUCK(2);
    #else
        SWITCH_ROM_MBC5(2);
    #endif
}

void Title() NONBANKED
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

    PerformantDelay(130);
    fadeout();
    HIDE_BKG;
}

void Menu() NONBANKED
{
    set_bkg_palette(0, Menu_PALETTE_COUNT, &Menu_palettes[0]);
    set_bkg_data(0, Menu_TILE_COUNT, Menu_tiles);
    if (sgb_check()) {
        SGBTransferPalettes(bkgSGBPaletteWater);
    }
    //VBK_REG = 1;
    set_bkg_tiles(0, 0, 20, 18, Menu_map);
    //VBK_REG = 0;
    //set_bkg_tiles(0, 0, 20, 18, Menu_map);

    SHOW_BKG;

    while (1)
    {
        if (joypad() & J_A)
        {
            fadeout();
            HIDE_BKG;
            break;
        }
    }
}

void WepShop() BANKED
{
    set_bkg_palette(0, 4, &bkgShopPalette[0]);
    set_bkg_data(0, 47, ShopTiles);
    if (sgb_check()) {
        SGBTransferPalettes(bkgSGBPaletteWater);
    }

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
            fadeout();
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
    SetColliders();

    SHOW_WIN;

    set_win_data(72, 55, RaptorDialog);

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
        set_camera();

        scroll_cam_up();

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
    //Helps hide some graphics corruption
    set_bkg_palette(0, 1, &black_palette[0]);
    set_bkg_data(0, Hanger_TILE_COUNT, Hanger_tiles);
    set_bkg_palette(0, Hanger_PALETTE_COUNT, &Hanger_palettes[0]);
    
    if (sgb_check()) {
        SGBTransferPalettes(bkgSGBPaletteHanger);
    }

    //VBK_REG = 1;
    //set_bkg_tiles(0, 0, 20, 18, Hanger_map);
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
            fadeout();
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
    set_bkg_palette(0, 8, &bkgBravo1Palette[0]);
    //Bank 3:
    //Bravo Map 1 and Enemy Sprites
    currentMapBank = 3;
    #ifdef MEGADUCK
        SWITCH_ROM_MEGADUCK(currentMapBank);
    #else
        SWITCH_ROM_MBC5(currentMapBank);
    #endif
    set_bkg_data(0, 52, Bravo1MapTiles);
    if (sgb_check()) {
        SGBTransferPalettes(bkgSGBPaletteWater);
    }

    map_pos_y = (uint8_t)(camera_y >> 3u);

    currentMapPLN0 = (unsigned char*)BravoWave1PLN0;
    currentMapPLN1 = (unsigned char*)BravoWave1PLN1;
    
    for (uint8_t i = 144; i--;)
    {
        VBK_REG = 1;
        set_bkg_submap(0, map_pos_y +i, 20, 1, (unsigned char*)currentMapPLN1, 20);
        VBK_REG = 0;
        set_bkg_submap(0, map_pos_y +i, 20, 1, (unsigned char*)currentMapPLN0, 20);
    }

    gameLoop();

    //map_pos_y = 0;
    old_map_pos_y = 255;

    //Switch back to Bank 2 for Background Handler use.
    #ifdef MEGADUCK
        SWITCH_ROM_MEGADUCK(2);
    #else
        SWITCH_ROM_MBC5(2);
    #endif
    
}