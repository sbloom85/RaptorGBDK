#include "gb.h"
#include "cgb.h"
#include <stdio.h>
//#include <stdlib.h>
#include "gamecharacter.h"
#include "projectile.h"
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

const UWORD sprPalette[] = {
	RGB_GREEN, RGB_RED, RGB(15, 15, 15), RGB(5, 5, 5)
};

// Move the character
void MovePlayer(struct Player* character, uint8_t x, uint8_t y)
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

void initProjectiles()
{
    uint8_t startID = 8; //Everything below 8 is resurved for ship.
    for (int8_t i = 0; i < MAX_PROJECTILES; i++)
    {
        newProjectile[i].id = startID;
        startID++;
        newProjectile[i].enabled = 0;
    }
}

void moveProjectiles()
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

void fireMachineGun()
{
    MachineGunSound();    // Plays sound effect from sound.h
    for (int8_t i = 0; i < MAX_PROJECTILES; i++)
    {
        if (!newProjectile[i].enabled)
        {
            newProjectile[i].x = ship.x + 12;
            newProjectile[i].y = ship.y + 4;
            newProjectile[i].enabled = 1;
            set_sprite_data(newProjectile[i].id, 1, MchBulletTLE0);
            set_sprite_tile(newProjectile[i].id, newProjectile[i].id);
            i = MAX_PROJECTILES; //Break out of loop.
        }
    }
}

// Initialize ship struct
void setupShip()
{
    set_sprite_palette(0, 1, sprPalette);

    ship.x = 80;
    ship.y = 120;
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

void SetupEnemyShip()
{
    eShip1.x = 80;
    eShip1.y = 30;
    eShip1.width = 32;
    eShip1.height = 24;
    eShip1.enabled = 1;
    eShip1.visible = 1;

    // Load sprites for ship
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
            MovePlayer(&ship, ship.x, ship.y);
            
            SetColliders();
        } else if ((joyInput & J_DOWN) && ship.y < 126)
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
            fireMachineGun();
            //delay(100);
        }
        else if (joyInput & J_B)
        {
            MissileSound();       // Plays missile launch sound effect
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