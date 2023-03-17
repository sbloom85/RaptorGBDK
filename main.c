#include "gb.h"
#include <stdio.h>
#include "sprites/Raptor.c"
#include "gamecharacter.c"

// Game Character Struct
struct GameCharacter ship;
UBYTE spriteSize = 8;

// Move the character
void MoveGameCharacter(struct GameCharacter* character, uint8_t x, uint8_t y)
{
    move_sprite(character->spriteids[0], x + (spriteSize * 0), y + (spriteSize * 0));
    move_sprite(character->spriteids[1], x + (spriteSize * 1), y + (spriteSize * 0));
    move_sprite(character->spriteids[2], x + (spriteSize * 2), y + (spriteSize * 0));
    move_sprite(character->spriteids[3], x + (spriteSize * 3), y + (spriteSize * 0));
    move_sprite(character->spriteids[4], x + (spriteSize * 0), y + (spriteSize * 1));
    move_sprite(character->spriteids[5], x + (spriteSize * 1), y + (spriteSize * 1));
    move_sprite(character->spriteids[6], x + (spriteSize * 2), y + (spriteSize * 1));
    move_sprite(character->spriteids[7], x + (spriteSize * 3), y + (spriteSize * 1));
    move_sprite(character->spriteids[8], x + (spriteSize * 0), y + (spriteSize * 2));
    move_sprite(character->spriteids[9], x + (spriteSize * 1), y + (spriteSize * 2));
    move_sprite(character->spriteids[10], x + (spriteSize * 2), y + (spriteSize * 2));
    move_sprite(character->spriteids[11], x + (spriteSize * 3), y + (spriteSize * 2));
}

// Initialize ship struct
void setupShip()
{
    ship.x = 80;
    ship.y = 120;
    ship.width = 32;
    ship.height = 24;

    // Load sprites for ship
    set_sprite_tile(0, 0);
    ship.spriteids[0] = 0;
    set_sprite_tile(1, 1);
    ship.spriteids[1] = 1;
    set_sprite_tile(2, 2);
    ship.spriteids[2] = 2;
    set_sprite_tile(3, 3);
    ship.spriteids[3] = 0;
    set_sprite_tile(4, 4);
    ship.spriteids[4] = 0;
    set_sprite_tile(5, 5);
    ship.spriteids[5] = 5;
    set_sprite_tile(6, 6);
    ship.spriteids[6] = 6;
    set_sprite_tile(7, 7);
    ship.spriteids[7] = 0;
    set_sprite_tile(8, 8);
    ship.spriteids[8] = 8;
    set_sprite_tile(9, 9);
    ship.spriteids[9] = 9;
    set_sprite_tile(10, 10);
    ship.spriteids[10] = 10;
    set_sprite_tile(11, 11);
    ship.spriteids[11] = 11;

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
