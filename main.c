#include <gb/gb.h>
#include <stdio.h>
#include "maps/BackTiles.c"
#include "maps/SimpleBackground.c"

void main(void)
{
    set_bkg_data(0, 7, BackTiles);
    set_bkg_tiles(0, 0, 40, 18, SimpleBackground);

    SHOW_BKG;
    DISPLAY_ON;

    while (1)
    {
        scroll_bkg(1, 0);
        delay(100);
    }
}
