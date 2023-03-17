#include "gb.h"
#include <stdio.h>
#include "../sprites/Raptor.h"
#include "gamecharacter.h"

// Game Character Struct
struct Player ship;
struct Enemy eShip1;
const uint8_t spriteSize = 8;

// Move the character
void MoveGameCharacter(struct Player* character, uint8_t x, uint8_t y)
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

    MoveGameCharacter(&ship, ship.x, ship.y);
}

void main(void)
{
    setupShip();
    SHOW_SPRITES;

    /*
    while (1)
    {
        scroll_bkg(1, 0);
        delay(100);
    }
    */
}
