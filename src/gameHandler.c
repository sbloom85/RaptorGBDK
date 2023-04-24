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

#pragma bank 3

#ifdef __TARGET_gb
#include <gb/gb.h>
#include <gb/cgb.h>
#endif
#ifdef __TARGET_gg
#include <sms/sms.h>
#endif
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "maps.h"

#include "commonFunc.h"
#include "spriteHandler.h"
#include "gameHandler.h"

extern struct PlayerData playData;
extern struct PlayerShip ship;

uint8_t doneScroll = 0;

uint8_t mapTileSet = 1;
uint8_t currentMapBank = 5;

unsigned char *currentMapPLN0;
unsigned char *currentMapPLN1;
unsigned char *currentMapPLN2;

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

// current and old positions of the camera in pixels
//int16_t  fake_camera_x;
int16_t camera_y;
int16_t old_camera_y;
// current and old position of the map in tiles
//uint8_t map_pos_x;
#ifdef __TARGET_gb
uint8_t AT(0xFFA5) map_pos_y;
uint8_t AT(0xFFA6) old_map_pos_y;
#else
uint8_t map_pos_y;
uint8_t old_map_pos_y;
#endif

struct windowStruct {
    char Cash[10];
    char Health[3];
    char Shield[3];
} windowData;

char* itoa8(int8_t i, char b[])
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

char* itoa32(int32_t i, char b[])
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

void GGDisplayHud()
{
    #ifdef __TARGET_gg
    set_tile_map_compat(0, (uint8_t)(camera_y >> 3u) +17U, 20, 2, RaptorWindowUpdateGGPLN0);
    #endif
}

//Needs to be Banked?
void updateHud() BANKED
{
    if (IS_FRAME_2)
    {
        itoa32(playData.cashAmount, windowData.Cash);
        itoa8(playData.curHealth, windowData.Health);
        itoa8(playData.curShield, windowData.Shield);

        for (uint8_t i = 40; i--;)
        {
            switch (i)
            {
                //Line 1
                case 5: //Cash Pos 0
                    RaptorWindowUpdatePLN0[i] = 0x67 + windowData.Cash[0] -48U;
                    break;
                case 6: //Cash Pos 1
                    if (playData.cashAmount >= 10)
                    {
                        RaptorWindowUpdatePLN0[i] = 0x67 + windowData.Cash[1] -48U;
                    }
                    break;
                case 7: //Cash Pos 2
                    if (playData.cashAmount >= 100)
                    {
                        RaptorWindowUpdatePLN0[i] = 0x67 + windowData.Cash[2] -48U;
                    }
                    break;
                case 8: //Cash Pos 3
                    if (playData.cashAmount >= 1000)
                    {
                        RaptorWindowUpdatePLN0[i] = 0x67 + windowData.Cash[3] -48U;
                    }
                    break;
                case 9: //Cash Pos 4
                    if (playData.cashAmount >= 10000)
                    {
                        RaptorWindowUpdatePLN0[i] = 0x67 + windowData.Cash[4] -48U;
                    }
                    break;
                case 10: //Cash Pos 5
                    if (playData.cashAmount >= 100000)
                    {
                        RaptorWindowUpdatePLN0[i] = 0x67 + windowData.Cash[5] -48U;
                    }
                    break;
                case 11: //Cash Pos 6
                    if (playData.cashAmount >= 1000000)
                    {
                        RaptorWindowUpdatePLN0[i] = 0x67 + windowData.Cash[6] -48U;
                    }
                    break;
                case 12: //Cash Pos 7
                    if (playData.cashAmount >= 10000000)
                    {
                        RaptorWindowUpdatePLN0[i] = 0x67 + windowData.Cash[7] -48U;
                    }
                    break;
                case 13: //Cash Pos 8
                    if (playData.cashAmount >= 100000000)
                    {
                        RaptorWindowUpdatePLN0[i] = 0x67 + windowData.Cash[8] -48U;
                    }
                    break;
                case 14: //Cash Pos 9
                    if (playData.cashAmount >= 1000000000)
                    {
                        RaptorWindowUpdatePLN0[i] = 0x67 + windowData.Cash[9] -48U;
                    }
                    break;
                
                //Line 2
                case 22: //Health Pos 1
                    RaptorWindowUpdatePLN0[i] = 0x48 + windowData.Health[0] -17U;
                    break;
                case 23: //Health Pos 2
                    if (playData.curHealth >= 10)
                    {
                        RaptorWindowUpdatePLN0[i] = 0x48 + windowData.Health[1] -17U;
                    }
                    break;
                case 24: //Health Pos 3
                    if (playData.curHealth >= 100)
                    {
                        RaptorWindowUpdatePLN0[i] = 0x48 + windowData.Health[2] -17U;
                    }
                    break;
                case 27: //Shield Pos 1
                    RaptorWindowUpdatePLN0[i] = 0x48 + windowData.Shield[0] -17U;
                    break;
                case 28: //Shield Pos 2
                    if (playData.curShield >= 10)
                    {
                        RaptorWindowUpdatePLN0[i] = 0x48 + windowData.Shield[1] -17U;
                    }
                    break;
                case 29: //Shield Pos 3
                    if (playData.curShield >= 100)
                    {
                        RaptorWindowUpdatePLN0[i] = 0x48 + windowData.Shield[2] -17U;
                    }
                    break;
                case 31: //Shield Icon Pos 1
                    if (playData.numShields > 0)
                        RaptorWindowUpdatePLN0[i] = 0x7D;
                    else
                        RaptorWindowUpdatePLN0[i] = 0x7E;
                    break;
                case 32: //Shield Icon Pos 2
                    if (playData.numShields > 1)
                        RaptorWindowUpdatePLN0[i] = 0x7D;
                    else
                        RaptorWindowUpdatePLN0[i] = 0x7E;
                    break;
                case 33: //Shield Icon Pos 3
                    if (playData.numShields > 2)
                        RaptorWindowUpdatePLN0[i] = 0x7D;
                    else
                        RaptorWindowUpdatePLN0[i] = 0x7E;
                    break;
                case 34: //Shield Icon Pos 4
                    if (playData.numShields > 3)
                        RaptorWindowUpdatePLN0[i] = 0x7D;
                    else
                        RaptorWindowUpdatePLN0[i] = 0x7E;
                    break;
                case 35: //Shield Icon Pos 5
                    if (playData.numShields > 4)
                        RaptorWindowUpdatePLN0[i] = 0x7D;
                    else
                        RaptorWindowUpdatePLN0[i] = 0x7E;
                    break;
                case 38: //Weapon
                    RaptorWindowUpdatePLN0[i] = 0x75 + playData.weapon;
                    break;
                default:
                    break;
            }
        }
    }
}

void init_camera()
{
    camera_y = -154;
    old_camera_y = camera_y;

    // update hardware scroll position
    #ifdef __TARGET_gb
    SCY_REG = camera_y;
    #endif
    #ifdef __TARGET_gg
    move_bkg(0, camera_y);
    #endif
}

void scroll_cam_up()
{
    //Check frames for slight slow down.
    if (camera_y != -2048 && (IS_FRAME_ODD || IS_FRAME_4))
    {
        camera_y--;
        //fake_camera_x--;
    } else if (camera_y == -2048) {
        doneScroll = 1;
    }
}

void tileHitDetection() NONBANKED
{
    #ifdef __TARGET_gb
    if (!doneScroll)
    {
        SWITCH_ROM(currentMapBank);

        uint8_t curLine = 0;

        //Check every 14 Frames
        if (IS_FRAME_8 && IS_FRAME_4 && IS_FRAME_2)
        {
            for (uint8_t map_pos_x = 21; map_pos_x--;)
            {
                uint8_t tileAttr;
                tileAttr = BravoWave1PLN2[(20 * map_pos_y) + map_pos_x];

                if(tileAttr == TileSetSecond)
                {
                    mapTileSet = 1;
                }

                uint16_t mapPosYTile = ((camera_y)>>3);
                uint8_t mapPosXTile = map_pos_x +1U;

                //Scan 14 Lines not just 1
                //for (uint8_t curLine = 1; curLine < 15; curLine++)
                //{
                    
                    uint8_t shotId;
                    uint8_t shotTileAttr;
                    
                    for (shotId = 0; shotId < 8; shotId++)
                    {
                        curLine++;
                        uint8_t projectileX = (newProjectile[shotId].x >> 3)-1U;
                        uint16_t projectileY = (((uint16_t)newProjectile[shotId].y+camera_y)>>3)-1U;
                        if (curLine == 15)
                            curLine = 0;
                        shotTileAttr = BravoWave1PLN2[((20 * map_pos_y + curLine)) + map_pos_x];
                        //printf("P%d M%d ", projectileY, curLine); //mapPosYTile >> 9
                        if(shotTileAttr == DestrutableLand && projectileX == mapPosXTile && projectileY == mapPosYTile)
                        {
                            set_bkg_tile_xy(projectileX, projectileY, 0x50);
                            set_bkg_tile_xy(projectileX +1U, projectileY, 0x50);
                        } /*else if (shotTileAttr == DestrutableWater && projectileX == mapPosXTile && projectileY == mapPosYTile + curLine) 
                        {
                            set_bkg_tile_xy(map_pos_x, map_pos_y, 0x55);
                            set_bkg_tile_xy(map_pos_x +1U, map_pos_y, 0x55);
                        }*/
                    }
                //}
            }
        }

        SWITCH_ROM(3);
    }
    #endif
}

void set_camera() NONBANKED
{
    // update hardware scroll position
    #ifdef __TARGET_gb
    SCY_REG = camera_y;
    #endif
    #ifdef __TARGET_gg
    move_bkg(0, camera_y);
    #endif

    SWITCH_ROM(currentMapBank);

    //Row that updates + 18u updates last line.
    map_pos_y = (uint8_t)(camera_y >> 3u);
    //map_pos_x = (uint8_t)(fake_camera_x >> 3u); 
    if (map_pos_y != old_map_pos_y) { 
        if (camera_y < old_camera_y) {
            #ifdef __TARGET_gb
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
            #endif
            #ifdef __TARGET_gg
            set_tile_submap_compat(0, map_pos_y, 20, 1, 20, (unsigned char*)currentMapPLN0);
            #endif
            updateHud();
            #ifdef __TARGET_gb
            set_win_tiles(0, 0, 20, 2, RaptorWindowUpdatePLN0);
            #endif
        }
        old_map_pos_y = map_pos_y; 
    }
    // set old camera position to current camera position
    old_camera_y = camera_y;
    
    SWITCH_ROM(3);
}

void gameInit()
{
    initProjectiles();
    init_camera();
    setupShip();
    //SetupEnemyShip();
    SetColliders();

    SHOW_SPRITES;

    #ifdef __TARGET_gb
    SHOW_WIN;

    set_win_data(102, 27, RaptorDialog);

    VBK_REG = 1;
    set_win_tiles(0, 0, 20, 2, RaptorWindowPLN1);
    VBK_REG = 0;
    set_win_tiles(0, 0, 20, 2, RaptorWindowUpdatePLN0);

    move_win(7, 128);
    #endif

    //#ifdef __TARGET_gg
    //set_tile_map_compat(0, 0, 20, 2, RaptorWindowUpdateGGPLN0);
    //#endif
}

void gameLoop() NONBANKED
{
    //Main Game Loop
    while (1)
    {
        game_time++;

        SWITCH_ROM(6);
        #ifdef __TARGET_gb
        hUGE_dosound();
        #endif
        #ifdef __TARGET_gg
        //Todo
        #endif
        SWITCH_ROM(3);

        //GGDisplayHud();

        set_camera();

        //tileHitDetection();

        SWITCH_ROM(6);
        #ifdef __TARGET_gb
        hUGE_dosound();
        #endif
        #ifdef __TARGET_gg
        //Todo
        #endif
        SWITCH_ROM(3);

        //GGDisplayHud();

        scroll_cam_up();

        //MoveEnemy();

        moveProjectiles();

        inputLoop();

        SWITCH_ROM(6);
        #ifdef __TARGET_gb
        hUGE_dosound();
        #endif
        #ifdef __TARGET_gg
        //Todo
        #endif
        SWITCH_ROM(3);

        //GGDisplayHud();

        PerformantDelay(2);
    }
}