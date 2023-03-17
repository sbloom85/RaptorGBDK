#include <gb/gb.h>
#include <stdio.h>
#include "sprites/Smiley.c"

void main(void)
{
    set_sprite_data(0, 2, Smiley);
    set_sprite_tile(0, 0);
    move_sprite(0, 88, 78);
    SHOW_SPRITES;
}
