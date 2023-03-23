#pragma bank 1

#include "gb.h"
#include "sgb.h"
#include "cgb.h"
#include <stdio.h>
//#include <stdlib.h>
#include "spriteStructs.h"
#include "projectile.h"
#include "../sprites/Cursor.h"
#include "../sprites/Raptor.h"

#include "sound.h"
#include "spriteHandler.h"

#define MAX_PROJECTILES 20

struct projectile newProjectile[MAX_PROJECTILES];

// Game Character Struct
struct Player ship;
struct Enemy eShip1;

const uint8_t spriteSize = 8;
const uint8_t moveSpeed = 2;

int8_t shots = 0;

const UWORD sprPalette[] = {
	RGB_GREEN, RGB_RED, RGB(15, 15, 15), RGB(5, 5, 5)
};

void InitCursor() BANKED
{
    set_sprite_palette(0, 1, sprPalette);
    set_sprite_data(0, 1, CursorTileTLE0);
    set_sprite_tile(0, 0);
}

void MoveCursor(uint8_t x, uint8_t y) BANKED
{
    move_sprite(0, x, y);
}

// Move the character
void MovePlayer(struct Player* character, uint8_t x, uint8_t y) BANKED
{
    move_sprite(character->spriteids[0], x + (spriteSize + 0), y + (spriteSize + 0));
    move_sprite(character->spriteids[1], x + (spriteSize + 8), y + (spriteSize + 0));
    move_sprite(character->spriteids[2], x + (spriteSize + 0), y + (spriteSize + 8));
    move_sprite(character->spriteids[3], x + (spriteSize + 8), y + (spriteSize + 8));
    move_sprite(character->spriteids[4], x + (spriteSize - 8), y + (spriteSize + 16));
    move_sprite(character->spriteids[5], x + (spriteSize + 0), y + (spriteSize + 16));
    move_sprite(character->spriteids[6], x + (spriteSize + 8), y + (spriteSize + 16));
    move_sprite(character->spriteids[7], x + (spriteSize + 16), y + (spriteSize + 16));
}

void initProjectiles() BANKED
{
    uint8_t startID = 8; //Everything below 8 is resurved for ship.
    for (int8_t i = 0; i < MAX_PROJECTILES; i++)
    {
        newProjectile[i].id = startID;
        startID++;
        newProjectile[i].enabled = 0;
    }
}

void moveProjectiles() BANKED
{
    for (int8_t i = 0; i < MAX_PROJECTILES; i++)
    {
        if (newProjectile[i].enabled)
        {
            newProjectile[i].y -= 4;
            if (newProjectile[i].y > 0)
            {
                move_sprite(newProjectile[i].id, newProjectile[i].x, newProjectile[i].y);
            } else {
                newProjectile[i].enabled = 0;                
            }
        }
    }
}

void fireMachineGun() BANKED
{
    while (shots < MAX_PROJECTILES)
    {
        if (!newProjectile[shots].enabled)
        {
            MachineGunSound();    // Plays sound effect from sound.h
            newProjectile[shots].x = ship.x + 12;
            newProjectile[shots].y = ship.y + 4;
            newProjectile[shots].enabled = 1;
            set_sprite_data(newProjectile[shots].id, 1, MchBulletTLE0);
            set_sprite_tile(newProjectile[shots].id, newProjectile[shots].id);
            shots = MAX_PROJECTILES; //Break out of loop.
        }
        //if (newProjectile[0].enabled)
        //{

        //}
        shots++;
    }
    shots = 0;
}

// Initialize ship struct
void setupShip() BANKED
{
    set_sprite_palette(0, 1, sprPalette);

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

    MovePlayer(&ship, ship.x, ship.y);
}

void SetupEnemyShip() BANKED
{
    eShip1.x = 80;
    eShip1.y = 30;
    eShip1.width = 32;
    eShip1.height = 24;
    eShip1.enabled = 1;
    eShip1.visible = 1;

    // Load sprites for ship
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
            MovePlayer(&ship, ship.x, ship.y);
            
            SetColliders();
        } else if ((joyInput & J_DOWN) && ship.y < 110)
        {
            ship.y += moveSpeed;
            MovePlayer(&ship, ship.x, ship.y);

            SetColliders();
        }

        if ((joyInput & J_LEFT) && ship.x > 16)
        {
            ship.x -= moveSpeed;
            MovePlayer(&ship, ship.x, ship.y);

            SetColliders();
        } else if ((joyInput & J_RIGHT) && ship.x < 128)
        {
            ship.x += moveSpeed;
            MovePlayer(&ship, ship.x, ship.y);

            SetColliders();
        }

        if (joyInput & J_A)
        {
            //if (shots > 1)
                //delay(10);
            fireMachineGun();
        }
        else if (joyInput & J_B)
        {
            
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