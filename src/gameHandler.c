#pragma bank 2

#include "gb.h"
#include "cgb.h"
#include <stdio.h>
#include <stdlib.h>

#include <string.h>

#include "maps.h"

#include "commonFunc.h"
#include "spriteHandler.h"
#include "gameHandler.h"

uint8_t mapTileSet = 0;
uint8_t currentMapBank = 5;

unsigned char *currentMapPLN0;
unsigned char *currentMapPLN1;

// current and old positions of the camera in pixels
int16_t camera_y, old_camera_y;
// current and old position of the map in tiles
uint8_t map_pos_y;
uint8_t old_map_pos_y;

struct windowStruct {
    char Cash[10];
    char Health[3];
    char Shield[3];
} windowData;

char* itoa8(int8_t i, char b[]) BANKED
{
    char const digit[] = "0123456789";
    char* p = b;
    if(i<0){
        *p++ = '-';
        i *= -1;
    }
    int8_t shifter = i;
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

char* itoa32(int32_t i, char b[]) BANKED
{
    char const digit[] = "0123456789";
    char* p = b;
    if(i<0){
        *p++ = '-';
        i *= -1;
    }
    int32_t shifter = i;
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

void updateHud() BANKED
{
    itoa32(ship.cashAmount, windowData.Cash);
    itoa8(ship.curHealth, windowData.Health);
    itoa8(ship.curShield, windowData.Shield);

    for (uint8_t i = 40; i--;)
    {
        //Line 1
        if (i == 5) //Cash Pos 0
        {
            RaptorWindowUpdatePLN0[i] = 0x66 + windowData.Cash[0] -48U;
        }
        if (i == 6) //Cash Pos 1
        {
            if (ship.cashAmount >= 10)
            {
                RaptorWindowUpdatePLN0[i] = 0x66 + windowData.Cash[1] -48U;
            }
        }
        if (i == 7) //Cash Pos 2
        {
            if (ship.cashAmount >= 100)
            {
                RaptorWindowUpdatePLN0[i] = 0x66 + windowData.Cash[2] -48U;
            }
        }
        if (i == 8) //Cash Pos 3
        {
            if (ship.cashAmount >= 1000)
            {
                RaptorWindowUpdatePLN0[i] = 0x66 + windowData.Cash[3] -48U;
            }
        }
        if (i == 9) //Cash Pos 4
        {
            if (ship.cashAmount >= 10000)
            {
                RaptorWindowUpdatePLN0[i] = 0x66 + windowData.Cash[4] -48U;
            }
        }
        if (i == 10) //Cash Pos 5
        {
            if (ship.cashAmount >= 100000)
            {
                RaptorWindowUpdatePLN0[i] = 0x66 + windowData.Cash[5] -48U;
            }
        }
        if (i == 11) //Cash Pos 6
        {
            if (ship.cashAmount >= 1000000)
            {
                RaptorWindowUpdatePLN0[i] = 0x66 + windowData.Cash[6] -48U;
            }
        }
        if (i == 12) //Cash Pos 7
        {
            if (ship.cashAmount >= 10000000)
            {
                RaptorWindowUpdatePLN0[i] = 0x66 + windowData.Cash[7] -48U;
            }
        }
        if (i == 13) //Cash Pos 8
        {
            if (ship.cashAmount >= 100000000)
            {
                RaptorWindowUpdatePLN0[i] = 0x66 + windowData.Cash[8] -48U;
            }
        }
        if (i == 14) //Cash Pos 9
        {
            if (ship.cashAmount >= 1000000000)
            {
                RaptorWindowUpdatePLN0[i] = 0x66 + windowData.Cash[9] -48U;
            }
        }
        
        //Line 2
        if (i == 22) //Health Pos 1
        {
            RaptorWindowUpdatePLN0[i] = 0x47 + windowData.Health[0] -17U;
        }
        if (i == 23) //Health Pos 2
        {
            if (ship.curHealth >= 10)
            {
                RaptorWindowUpdatePLN0[i] = 0x47 + windowData.Health[1] -17U;
            }
        }
        if (i == 24) //Health Pos 3
        {
            if (ship.curHealth >= 100)
            {
                RaptorWindowUpdatePLN0[i] = 0x47 + windowData.Health[2] -17U;
            }
        }
        if (i == 27) //Shield Pos 1
        {
            RaptorWindowUpdatePLN0[i] = 0x47 + windowData.Shield[0] -17U;
        }
        if (i == 28) //Shield Pos 2
        {
            if (ship.curShield >= 10)
            {
                RaptorWindowUpdatePLN0[i] = 0x47 + windowData.Shield[1] -17U;
            }
        }
        if (i == 29) //Shield Pos 3
        {
            if (ship.curShield >= 100)
            {
                RaptorWindowUpdatePLN0[i] = 0x47 + windowData.Shield[2] -17U;
            }
        }
        if (i == 31) //Shield Icon Pos 1
        {
            if (ship.numShields > 0)
                RaptorWindowUpdatePLN0[i] = 0x7D;
            else
                RaptorWindowUpdatePLN0[i] = 0x7E;
        }
        if (i == 32) //Shield Icon Pos 2
        {
            if (ship.numShields > 1)
                RaptorWindowUpdatePLN0[i] = 0x7D;
            else
                RaptorWindowUpdatePLN0[i] = 0x7E;
        }
        if (i == 33) //Shield Icon Pos 3
        {
            if (ship.numShields > 2)
                RaptorWindowUpdatePLN0[i] = 0x7D;
            else
                RaptorWindowUpdatePLN0[i] = 0x7E;
        }
        if (i == 34) //Shield Icon Pos 4
        {
            if (ship.numShields > 3)
                RaptorWindowUpdatePLN0[i] = 0x7D;
            else
                RaptorWindowUpdatePLN0[i] = 0x7E;
        }
        if (i == 35) //Shield Icon Pos 5
        {
            if (ship.numShields > 4)
                RaptorWindowUpdatePLN0[i] = 0x7D;
            else
                RaptorWindowUpdatePLN0[i] = 0x7E;
        }
        if (i == 38) //Weapon
        {
            RaptorWindowUpdatePLN0[i] = 0x74 + ship.weapon;
        }
    }
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

    //mapTileSet = 1;

    //uint8_t currentRow;
    //uint8_t currentColumn;
    //uint8_t entryValue = BravoWave1PLN2[(20 * currentRow) + currentColumn];
    uint8_t entryValue = BravoWave1PLN2[(20 * (map_pos_y >> 2)) + 0];

    if (entryValue == TileSetSecond)
    {
        printf("Test");
    }

    /*if (camera_y < -1124 && camera_y > -1450)
    {
        //mapTileSet = 1; //Switch map to second tileset.
    } else if (camera_y < -1450) {
        //mapTileSet = 0; //Switch map to second tileset.
    }*/
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
                set_bkg_based_submap(0, map_pos_y, 20, 1, (unsigned char*)currentMapPLN0, 20, 128);
            }
            else
            {
                set_bkg_based_submap(0, map_pos_y, 20, 1, (unsigned char*)currentMapPLN0, 20, 0);
            }
            updateHud();
            set_win_tiles(0, 0, 20, 2, RaptorWindowUpdatePLN0);
        }
        old_map_pos_y = map_pos_y; 
    }
    
    // set old camera position to current camera position
    old_camera_y = camera_y;

    SWITCH_ROM(2);
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

    set_win_data(101, 27, RaptorDialog);

    VBK_REG = 1;
    set_win_tiles(0, 0, 20, 2, RaptorWindowPLN1);
    VBK_REG = 0;
    set_win_tiles(0, 0, 20, 2, RaptorWindowUpdatePLN0);

    move_win(7, 128);
}

void gameLoop() NONBANKED
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