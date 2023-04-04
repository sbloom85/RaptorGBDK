#pragma bank 2

#include "gb.h"
#include "cgb.h"
#include <stdio.h>
#include <stdlib.h>
#include <rand.h>

#include <string.h>

#include "maps.h"

#include "commonFunc.h"
#include "spriteHandler.h"
#include "gameHandler.h"

#define 	RAND_MAX   255

uint8_t mapTileSet = 0;
uint8_t currentMapBank = 5;

unsigned char *currentMapPLN0;
unsigned char *currentMapPLN1;
unsigned char *currentMapPLN2;

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
    if (IS_FRAME_2)
    {
        itoa32(ship.cashAmount, windowData.Cash);
        itoa8(ship.curHealth, windowData.Health);
        itoa8(ship.curShield, windowData.Shield);

        for (uint8_t i = 40; i--;)
        {
            //Line 1
            if (i == 5) //Cash Pos 0
            {
                RaptorWindowUpdatePLN0[i] = 0x67 + windowData.Cash[0] -48U;
            }
            if (i == 6) //Cash Pos 1
            {
                if (ship.cashAmount >= 10)
                {
                    RaptorWindowUpdatePLN0[i] = 0x67 + windowData.Cash[1] -48U;
                }
            }
            if (i == 7) //Cash Pos 2
            {
                if (ship.cashAmount >= 100)
                {
                    RaptorWindowUpdatePLN0[i] = 0x67 + windowData.Cash[2] -48U;
                }
            }
            if (i == 8) //Cash Pos 3
            {
                if (ship.cashAmount >= 1000)
                {
                    RaptorWindowUpdatePLN0[i] = 0x67 + windowData.Cash[3] -48U;
                }
            }
            if (i == 9) //Cash Pos 4
            {
                if (ship.cashAmount >= 10000)
                {
                    RaptorWindowUpdatePLN0[i] = 0x67 + windowData.Cash[4] -48U;
                }
            }
            if (i == 10) //Cash Pos 5
            {
                if (ship.cashAmount >= 100000)
                {
                    RaptorWindowUpdatePLN0[i] = 0x67 + windowData.Cash[5] -48U;
                }
            }
            if (i == 11) //Cash Pos 6
            {
                if (ship.cashAmount >= 1000000)
                {
                    RaptorWindowUpdatePLN0[i] = 0x67 + windowData.Cash[6] -48U;
                }
            }
            if (i == 12) //Cash Pos 7
            {
                if (ship.cashAmount >= 10000000)
                {
                    RaptorWindowUpdatePLN0[i] = 0x67 + windowData.Cash[7] -48U;
                }
            }
            if (i == 13) //Cash Pos 8
            {
                if (ship.cashAmount >= 100000000)
                {
                    RaptorWindowUpdatePLN0[i] = 0x67 + windowData.Cash[8] -48U;
                }
            }
            if (i == 14) //Cash Pos 9
            {
                if (ship.cashAmount >= 1000000000)
                {
                    RaptorWindowUpdatePLN0[i] = 0x67 + windowData.Cash[9] -48U;
                }
            }
            
            //Line 2
            if (i == 22) //Health Pos 1
            {
                RaptorWindowUpdatePLN0[i] = 0x48 + windowData.Health[0] -17U;
            }
            if (i == 23) //Health Pos 2
            {
                if (ship.curHealth >= 10)
                {
                    RaptorWindowUpdatePLN0[i] = 0x48 + windowData.Health[1] -17U;
                }
            }
            if (i == 24) //Health Pos 3
            {
                if (ship.curHealth >= 100)
                {
                    RaptorWindowUpdatePLN0[i] = 0x48 + windowData.Health[2] -17U;
                }
            }
            if (i == 27) //Shield Pos 1
            {
                RaptorWindowUpdatePLN0[i] = 0x48 + windowData.Shield[0] -17U;
            }
            if (i == 28) //Shield Pos 2
            {
                if (ship.curShield >= 10)
                {
                    RaptorWindowUpdatePLN0[i] = 0x48 + windowData.Shield[1] -17U;
                }
            }
            if (i == 29) //Shield Pos 3
            {
                if (ship.curShield >= 100)
                {
                    RaptorWindowUpdatePLN0[i] = 0x48 + windowData.Shield[2] -17U;
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
                RaptorWindowUpdatePLN0[i] = 0x75 + ship.weapon;
            }
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
}

void set_camera() NONBANKED
{
    // update hardware scroll position
    SCY_REG = camera_y;

    SWITCH_ROM(currentMapBank);

    uint8_t tileAttr;
    uint8_t shotTileAttr;
    uint8_t shotId;

    //Check every 14 Frames
    if (IS_FRAME_8 && IS_FRAME_4 && IS_FRAME_2)
    {
        for (uint8_t map_pos_x = 21; map_pos_x--;)
        {
            tileAttr = BravoWave1PLN2[(20 * map_pos_y) + map_pos_x];
            //curBgTile = get_bkg_tile_xy(i, map_pos_y);

            if(tileAttr == TileSetSecond)
            {
                mapTileSet = 1;
            }

            //Scan 14 Lines not just 1
            for (uint8_t curLine = 1; curLine < 15; curLine++)
            {
                shotTileAttr = BravoWave1PLN2[((20 * map_pos_y) + curLine) + map_pos_x];
                for (shotId = 8; shotId--;)
                {
                    //Working X and Y?
                    // && (newProjectile[shotId].y / 6 ) == ((map_pos_y / 14) + 1U)
                    // && (newProjectile[shotId].x / 8 ) == ((map_pos_x +1U) //Right Shot
                    if(shotTileAttr == DestrutableLand && (newProjectile[shotId].x >> 3 ) == (map_pos_x  +1U) && ((newProjectile[shotId].y * 0x2B) >> 8) == (((map_pos_y * 0x13) >> 8) + curLine))
                    {
                        set_bkg_tile_xy(map_pos_x, map_pos_y, 0x50);
                        set_bkg_tile_xy(map_pos_x +1U, map_pos_y, 0x50);
                    }
                }
            }
        }
    }

    if (IS_FRAME_2)
    {
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
    }
    
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

    set_win_data(102, 27, RaptorDialog);

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