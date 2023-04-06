#pragma bank 2

#include <gb/gb.h>
#include <gb/cgb.h>
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

//Place in free spot in HighRam
uint8_t AT(0xFFA0) game_time;

// Game Character Struct
struct PlayerData playData;
struct PlayerShip ship;
struct Enemy eShip1;

const uint8_t spriteSize = 8;
const uint8_t moveSpeed = 2;

int8_t shots = 0;

const UWORD sprPalette[] = {
	RGB_GREEN, RGB_RED, RGB(15, 15, 15), RGB(5, 5, 5),
    RGB_GREEN, RGB(20, 20, 20), RGB(15, 15, 15), RGB(5, 5, 5),
    RGB_GREEN, RGB_CYAN, RGB(15, 15, 15), RGB(5, 5, 5),
    RGB_GREEN, RGB_BROWN, RGB(15, 15, 15), RGB(5, 5, 5),
};

void InitCursor() BANKED
{
    set_sprite_palette(0, 1, sprPalette);
    set_sprite_data(0, 1, CursorTileTLE0);
    set_sprite_tile(0, 0);
}

void MoveCursor(uint8_t x, uint8_t y) NONBANKED
{
    move_sprite(0, x, y);
}

// Move the character
void MovePlayer(uint8_t x, uint8_t y) BANKED
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

void initProjectiles() BANKED
{
    //Everything below 8 is resurved for ship.
    uint8_t shotStartID = 8;
    for (int8_t i = 0; i < MAX_PROJECTILES; i++)
    {
        newProjectile[i].id = shotStartID;
        shotStartID++;
        newProjectile[i].enabled = 0;
    }
}

void moveProjectiles() NONBANKED
{
    for (uint8_t i = 0; i < 8; i++)
    {
        if (newProjectile[i].enabled)
        {
            newProjectile[i].y -= 4;
            if (newProjectile[i].y > 8)
            {
                move_sprite(newProjectile[i].id, newProjectile[i].x, newProjectile[i].y);
            } else {
                newProjectile[i].enabled = 0;                
            }
        }
    }
}

void fireWeapon() BANKED
{
    while (shots < 8 && IS_FRAME_4)
    {
        if (!newProjectile[shots].enabled)
        {
            playData.cashAmount += 100; //Disable later.
            switch (playData.weapon)
            {
                case 0:
                    MachineGunSound();    // Plays sound effect from sound.h
                    set_sprite_data(newProjectile[shots].id, 1, WProjectilesTilesTLE0);
                    break;
                case 1:
                    MissileSound();    // Plays sound effect from sound.h
                    set_sprite_data(newProjectile[shots].id, 1, WProjectilesTilesTLE1);
                    break;
                case 2:
                    MissileSound();    // Plays sound effect from sound.h
                    set_sprite_data(newProjectile[shots].id, 1, WProjectilesTilesTLE2);
                    break;
                case 3:
                    MissileSound();    // Plays sound effect from sound.h
                    set_sprite_data(newProjectile[shots].id, 1, WProjectilesTilesTLE3);
                    break;
                case 4:
                    MachineGunSound();    // Plays sound effect from sound.h
                    set_sprite_data(newProjectile[shots].id, 1, WProjectilesTilesTLE4);
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

void playerInit() BANKED
{
    playData.weapon = 0;
    playData.mBomb = 0;
    playData.ionScanner = 0;
    playData.numShields = 0;

    playData.ownsMachGun = 1;
    playData.ownsAirMiss = 0;
    playData.ownsGrnMiss = 0;
    playData.ownsPlasCannon = 0;
    playData.ownsDumbFire = 0;
    playData.ownsMicroMiss = 0;
    playData.ownsPulseCannon = 0;
    playData.ownsDeathRay = 0;

    playData.curHealth = 75;
    playData.curShield = 0;
    playData.cashAmount = 10000;
}

// Initialize ship struct
void setupShip() BANKED
{
    set_sprite_palette(0, 3, &sprPalette[0]);

    ship.x = 80;
    ship.y = 110;
    ship.width = 32;
    ship.height = 24;
    ship.enabled = 1;
    ship.visible = 1;

    // Load sprites for ship
    set_sprite_data(0, 1, RaptorTLE0);
    set_sprite_tile(0, 0);
    ship.spriteids[0] = 0;
    set_sprite_data(1, 1, RaptorTLE1);
    set_sprite_tile(1, 1);
    ship.spriteids[1] = 1;
    set_sprite_data(2, 1, RaptorTLE2);
    set_sprite_tile(2, 2);
    ship.spriteids[2] = 2;
    set_sprite_data(3, 1, RaptorTLE3);
    set_sprite_tile(3, 3);
    ship.spriteids[3] = 3;
    set_sprite_data(4, 1, RaptorTLE4);
    set_sprite_tile(4, 4);
    ship.spriteids[4] = 4;
    set_sprite_data(5, 1, RaptorTLE5);
    set_sprite_tile(5, 5);
    ship.spriteids[5] = 5;
    set_sprite_data(6, 1, RaptorTLE6);
    set_sprite_tile(6, 6);
    ship.spriteids[6] = 6;
    set_sprite_data(7, 1, RaptorTLE7);
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

        SWITCH_ROM(2);
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

void SetColliders() BANKED
{
    // Reset colliders
    ship.colliderTop = ship.y;
    ship.colliderLeft = ship.x;
    ship.colliderRight = ship.x + ship.width;
    ship.colliderBottom = ship.y + ship.height;
}

void inputLoop() BANKED
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
            if (playData.weapon < 4)
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