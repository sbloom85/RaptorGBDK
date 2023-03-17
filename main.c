#include <gb/gb.h>
#include <stdio.h>
#include "sprites/Smiley.c"

void main(void)
{
    uint8_t tileSize = 8;
    set_sprite_data(0, 4, Smiley);
    set_sprite_tile(0, 0);
    move_sprite(0, 80, 72);
    SHOW_SPRITES;

    while(1)
    {
        switch(joypad())
        {
            case J_LEFT:
                scroll_sprite(0, -tileSize, 0);
                set_sprite_tile(0, 0);
                break;
            case J_RIGHT:
                scroll_sprite(0, tileSize, 0);
                set_sprite_tile(0, 3);
                break;
            case J_UP:
                scroll_sprite(0, 0, -tileSize);
                set_sprite_tile(0, 2);
                break;
            case J_DOWN:
                scroll_sprite(0, 0, tileSize);
                set_sprite_tile(0, 1);
                break;
        }
        delay(100);
    }
}
