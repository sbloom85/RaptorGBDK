#include "gb.h"
#include "cgb.h"
#include <stdio.h>
#include <stdlib.h>
#include "../sprites/Raptor.h"
#include "gamecharacter.h"
#include "projectile.h"
#include "sound.h"
#include "maps.h"

const UWORD bkgPalette[] = {
	RaptorMapTilesCGBPal0c0, RaptorMapTilesCGBPal0c1, RaptorMapTilesCGBPal0c2, RaptorMapTilesCGBPal0c3,
    RaptorMapTilesCGBPal1c0, RaptorMapTilesCGBPal1c1, RaptorMapTilesCGBPal1c2, RaptorMapTilesCGBPal1c3,
    RaptorMapTilesCGBPal2c0, RaptorMapTilesCGBPal2c1, RaptorMapTilesCGBPal2c2, RaptorMapTilesCGBPal2c3,
    RaptorMapTilesCGBPal3c0, RaptorMapTilesCGBPal3c1, RaptorMapTilesCGBPal3c2, RaptorMapTilesCGBPal3c3,
};

const UWORD sprPalette[] = {
	RGB_GREEN, RGB_RED, RGB(15, 15, 15), RGB(5, 5, 5)
};

// current and old positions of the camera in pixels
uint16_t camera_x, camera_y, old_camera_x, old_camera_y;
// current and old position of the map in tiles
uint8_t map_pos_x, map_pos_y, old_map_pos_x, old_map_pos_y;
// redraw flag, indicates that camera position was changed
uint8_t redraw;

// Game Character Struct
struct Player ship;
struct Enemy eShip1;
const uint8_t spriteSize = 8;
const uint8_t moveSpeed = 2;

#define MAX_PROJECTILES 20

struct projectile newProjectile[MAX_PROJECTILES];

// More CPU efficient delay
void PerformantDelay(uint8_t numLoops)
{
    for (uint8_t i = numLoops; i--;)
    {
        wait_vbl_done();
    }
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

void Hanger()
{
    set_bkg_palette(0, Hanger_PALETTE_COUNT, &Hanger_palettes[0]);
    set_bkg_data(0, Hanger_TILE_COUNT, Hanger_tiles);

    //VBK_REG = 1;
    set_bkg_tiles(0, 0, 20, 18, Hanger_map);
    //VBK_REG = 0;
    //set_bkg_tiles(0, 0, 20, 18, Intro_map);

    enum selected {Fly = 0, Shop = 1, Save = 2, Exit = 3};
    enum selected selection;

    selection = 0;

    while (1)
    {
        uint8_t joyInput = joypad();

        /*if (joyInput & J_LEFT)
        {
            if (selection > 0)
            {
                selection--;
            }
        } else if (joyInput & J_RIGHT) {
            if (selection < 3)
            {
                selection++;
            }
        }*/

        if (joyInput & J_A ) //&& selection == Fly
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

void main(void)
{
    Title();
    //delay(5000);
    Hanger();
    initProjectiles();
    set_sprite_palette(0, 1, sprPalette);
    InitializeSound();
    BravoOne();
    setupShip();
    SetColliders();

    SHOW_BKG;
    SHOW_SPRITES;
    DISPLAY_ON;

    camera_x = 0;
    //camera_y = 104;
    camera_y = 0;
    old_camera_x = camera_x; 
    old_camera_y = camera_y;

    redraw = TRUE;

    SCX_REG = camera_x; SCY_REG = camera_y;

    while (1)
    {
        set_camera();

        camera_y--;

        moveProjectiles();

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

        PerformantDelay(2);
        // delay(25);
    }
}
