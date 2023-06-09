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
//#include "spriteStructs.h"
#include "projectile.h"
#include "../sprites/Cursor.h"
#include "../sprites/Raptor.h"
#include "../sprites/BravoShip1.h"

#include "sound.h"
#include "spriteHandler.h"
#include "commonFunc.h"

#define MAX_PROJECTILES 20

struct projectile newProjectile[MAX_PROJECTILES];

#ifdef __TARGET_gb
//Place in free spot in HighRam
uint8_t AT(0xFF93) game_time;
#else
uint8_t game_time;
#endif

// Game Character Struct
extern struct PlayerData playData;
struct PlayerShip ship;
struct Enemy eShip1;

const uint8_t spriteSize = 8;
const uint8_t moveSpeed = 2;

int8_t shots = 0;

const UWORD sprPalette[] = {
	RGB_GREEN, RGB_RED, RGB(15, 15, 15), RGB(5, 5, 5),
    RGB_GREEN, RGB(20, 20, 20), RGB(15, 15, 15), RGB(5, 5, 5),
    RGB_GREEN, RGB_CYAN, RGB(15, 15, 15), RGB(5, 5, 5),
    //RGB_GREEN, RGB_BROWN, RGB(15, 15, 15), RGB(5, 5, 5),
};

void InitCursor()
{
    set_sprite_palette(0, 1, sprPalette);
    #ifdef __TARGET_gb
    set_sprite_data(0, 1, CursorTileTLE0);
    #endif
    #ifdef __TARGET_gg
    set_sprite_2bpp_data(0, 1, CursorTileTLE0);
    #endif
    set_sprite_tile(0, 0);
}

void MoveCursor(uint8_t x, uint8_t y) NONBANKED
{
    move_sprite(0, x, y);
}

// Move the character
void MovePlayer(uint8_t x, uint8_t y)
{
    move_sprite(ship.spriteids[0], x + (spriteSize + 0), y + (spriteSize + 0));
    move_sprite(ship.spriteids[1], x + (spriteSize + 8), y + (spriteSize + 0));
    move_sprite(ship.spriteids[2], x + (spriteSize + 0), y + (spriteSize + 8));
    move_sprite(ship.spriteids[3], x + (spriteSize + 8), y + (spriteSize + 8));
    move_sprite(ship.spriteids[4], x + (spriteSize - 8), y + (spriteSize + 16));
    move_sprite(ship.spriteids[5], x + (spriteSize + 0), y + (spriteSize + 16));
    move_sprite(ship.spriteids[6], x + (spriteSize + 8), y + (spriteSize + 16));
    move_sprite(ship.spriteids[7], x + (spriteSize + 16), y + (spriteSize + 16));
}

void MoveEnemy()
{
    eShip1.y += eShip1.speed;
    move_sprite(16, eShip1.x, eShip1.y);
    move_sprite(17, eShip1.x + 8, eShip1.y);
    move_sprite(18, eShip1.x + 16, eShip1.y);
    move_sprite(19, eShip1.x, eShip1.y + 8);
    move_sprite(20, eShip1.x + 8, eShip1.y + 8);
    move_sprite(21, eShip1.x + 16, eShip1.y + 8);
    move_sprite(22, eShip1.x + 24, eShip1.y + 8);
    //move_sprite(24, eShip1.x + 8, eShip1.y + 16);
    //move_sprite(25, eShip1.x + 16, eShip1.y + 16);
}

void initProjectiles()
{
    //Everything below 8 is resurved for ship.
    uint8_t shotStartID = 8;
    for (int8_t i = 0; i != MAX_PROJECTILES; i++)
    {
        newProjectile[i].id = shotStartID;
        shotStartID++;
        newProjectile[i].enabled = 0;
    }
}

void moveProjectiles() NONBANKED
{
    for (uint8_t i = 0; i != 8; i++)
    {
        if (newProjectile[i].enabled)
        {
            newProjectile[i].y -= 4;
            if (newProjectile[i].y > 4)
            {
                move_sprite(newProjectile[i].id, newProjectile[i].x, newProjectile[i].y);
            } else {
                newProjectile[i].enabled = 0;                
            }
        }
    }
}

void fireWeapon()
{
    while (shots < 8 && IS_FRAME_4)
    {
        if (!newProjectile[shots].enabled)
        {
            playData.cashAmount += 100; //Disable later.
            switch (playData.weapon)
            {
                case 0:
                    #ifdef __TARGET_gb
                    MachineGunSound();    // Plays sound effect from sound.h
                    set_sprite_data(newProjectile[shots].id, 1, WProjectilesTilesTLE0);
                    #endif
                    #ifdef __TARGET_gg
                    set_sprite_2bpp_data(newProjectile[shots].id, 1, WProjectilesTilesTLE0);
                    #endif
                    break;
                case 1:
                    #ifdef __TARGET_gb
                    MissileSound();    // Plays sound effect from sound.h
                    set_sprite_data(newProjectile[shots].id, 1, WProjectilesTilesTLE1);
                    #endif
                    #ifdef __TARGET_gg
                    set_sprite_2bpp_data(newProjectile[shots].id, 1, WProjectilesTilesTLE1);
                    #endif
                    break;
                case 2:
                    #ifdef __TARGET_gb
                    MissileSound();    // Plays sound effect from sound.h
                    set_sprite_data(newProjectile[shots].id, 1, WProjectilesTilesTLE2);
                    #endif
                    #ifdef __TARGET_gg
                    set_sprite_2bpp_data(newProjectile[shots].id, 1, WProjectilesTilesTLE2);
                    #endif
                    break;
                case 3:
                    #ifdef __TARGET_gb
                    MissileSound();    // Plays sound effect from sound.h
                    set_sprite_data(newProjectile[shots].id, 1, WProjectilesTilesTLE3);
                    #endif
                    #ifdef __TARGET_gg
                    set_sprite_2bpp_data(newProjectile[shots].id, 1, WProjectilesTilesTLE3);
                    #endif
                    break;
                case 4:
                    #ifdef __TARGET_gb
                    MachineGunSound();    // Plays sound effect from sound.h
                    set_sprite_data(newProjectile[shots].id, 1, WProjectilesTilesTLE4);
                    #endif
                    #ifdef __TARGET_gg
                    set_sprite_2bpp_data(newProjectile[shots].id, 1, WProjectilesTilesTLE4);
                    #endif
                    break;
            }
            
            newProjectile[shots].x = ship.x + 12;
            newProjectile[shots].y = ship.y + 4;
            newProjectile[shots].enabled = 1;
            set_sprite_tile(newProjectile[shots].id, newProjectile[shots].id);
            shots = MAX_PROJECTILES; //Break out of loop.
        }
        shots++;
    }
    shots = 0;
}
// Initialize ship struct
void setupShip()
{
    set_sprite_palette(0, 3, &sprPalette[0]);

    ship.x = 80;
    ship.y = 110;
    ship.width = 32;
    ship.height = 24;
    ship.enabled = 1;
    ship.visible = 1;

    // Load sprites for ship

    #ifdef __TARGET_gb
    set_sprite_data(0, 1, RaptorTLE0);
    set_sprite_data(2, 1, RaptorTLE2);
    set_sprite_data(3, 1, RaptorTLE3);
    set_sprite_data(4, 1, RaptorTLE4);
    set_sprite_data(5, 1, RaptorTLE5);
    set_sprite_data(6, 1, RaptorTLE6);
    set_sprite_data(7, 1, RaptorTLE7);
    #endif
    #ifdef __TARGET_gg
    set_sprite_2bpp_data(0, 1, RaptorTLE0);
    set_sprite_2bpp_data(2, 1, RaptorTLE2);
    set_sprite_2bpp_data(3, 1, RaptorTLE3);
    set_sprite_2bpp_data(4, 1, RaptorTLE4);
    set_sprite_2bpp_data(5, 1, RaptorTLE5);
    set_sprite_2bpp_data(6, 1, RaptorTLE6);
    set_sprite_2bpp_data(7, 1, RaptorTLE7);
    #endif

    
    set_sprite_tile(0, 0);
    ship.spriteids[0] = 0;
    set_sprite_data(1, 1, RaptorTLE1);
    set_sprite_tile(1, 1);
    ship.spriteids[1] = 1;
    
    set_sprite_tile(2, 2);
    ship.spriteids[2] = 2;
    
    set_sprite_tile(3, 3);
    ship.spriteids[3] = 3;
    
    set_sprite_tile(4, 4);
    ship.spriteids[4] = 4;
    
    set_sprite_tile(5, 5);
    ship.spriteids[5] = 5;
    
    set_sprite_tile(6, 6);
    ship.spriteids[6] = 6;
    
    set_sprite_tile(7, 7);
    ship.spriteids[7] = 7;

    SHOW_SPRITES;
    MovePlayer(ship.x, ship.y);
}

void SetupEnemyShip() NONBANKED
{
    eShip1.x = 80;
    eShip1.y = -220;
    eShip1.width = 32;
    eShip1.height = 24;
    eShip1.enabled = 1;
    eShip1.visible = 1;
    eShip1.speed = 2;

    if (eShip1.enabled)
    {
        SWITCH_ROM(BravoShip1TilesBank);
    
        // Load sprites for ship
        set_sprite_data(16, 8, BravoShip1Tiles);
        set_sprite_tile(16, 16);
        set_sprite_tile(17, 17);
        set_sprite_tile(18, 18);
        set_sprite_tile(19, 19);
        set_sprite_tile(20, 20);
        set_sprite_tile(21, 21);
        set_sprite_tile(22, 22);
        set_sprite_tile(23, 23);
        //set_sprite_tile(24, 24);
        //set_sprite_tile(25, 25);

        //Color the Sprites with Pal2 
        set_sprite_prop(16, 2);
        set_sprite_prop(17, 2);
        set_sprite_prop(18, 2);
        set_sprite_prop(19, 2);
        set_sprite_prop(20, 2);
        set_sprite_prop(21, 2);
        set_sprite_prop(22, 2);
        set_sprite_prop(23, 2);
        //set_sprite_prop(24, 2);
        //set_sprite_prop(25, 2);

        SWITCH_ROM(3);
    }

    /*set_sprite_data(16, 8, eShip01);
    set_sprite_tile(16, 16);
    set_sprite_tile(17, 17);
    set_sprite_tile(18, 18);
    set_sprite_tile(19, 19);
    set_sprite_tile(20, 20);
    set_sprite_tile(21, 21);
    //set_sprite_tile(22, 22);
    //set_sprite_tile(23, 23);
    
    move_sprite(16, eShip1.x, eShip1.y);
    move_sprite(17, eShip1.x + 8, eShip1.y);
    move_sprite(18, eShip1.x, eShip1.y + 8);
    move_sprite(19, eShip1.x + 8, eShip1.y + 8);
    move_sprite(20, eShip1.x, eShip1.y + 16);
    move_sprite(21, eShip1.x + 8, eShip1.y + 16);
    //move_sprite(22, eShip1.x, eShip1.y + 24);
    //move_sprite(23, eShip1.x + 8, eShip1.y + 24);*/
}

void SetColliders()
{
    // Reset colliders
    ship.colliderTop = ship.y;
    ship.colliderLeft = ship.x;
    ship.colliderRight = ship.x + ship.width;
    ship.colliderBottom = ship.y + ship.height;
}

void inputLoop()
{
    uint8_t joyInput = joypad();

        // Ship Movement
        if  ((joyInput & J_UP) && ship.y > 8)
        {
            ship.y -= moveSpeed;
            MovePlayer(ship.x, ship.y);
            
            SetColliders();
        } else if ((joyInput & J_DOWN) && ship.y < 110)
        {
            ship.y += moveSpeed;
            MovePlayer(ship.x, ship.y);

            SetColliders();
        }

        if ((joyInput & J_LEFT) && ship.x > 4)
        {
            ship.x -= moveSpeed;
            MovePlayer(ship.x, ship.y);

            SetColliders();
        } else if ((joyInput & J_RIGHT) && ship.x < 140)
        {
            ship.x += moveSpeed;
            MovePlayer(ship.x, ship.y);

            SetColliders();
        }

        if (joyInput & J_A)
        {
            //if (shots > 1)
                //delay(10);
            fireWeapon();
        }
        else if (joyInput & J_B && IS_FRAME_4)
        {
            if (playData.weapon != 4)
            {
                playData.weapon++;
            } else {
                playData.weapon = 0;
            }
        }

        if (joyInput & J_SELECT)
        {
            
        }

        if (joyInput & J_START)
        {
            
        }

        // Test if colliders work
        if (ship.colliderTop < 32)
        {
            ship.visible = 0;
        }
}