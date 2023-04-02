#pragma bank 0

#include "gb.h"
#include "cgb.h"
#include "commonFunc.h"

static const uint16_t fadeout_palette[] = {RGB_WHITE, RGB_LIGHTGRAY,  RGB_DARKGRAY, RGB_BLACK, RGB_BLACK, RGB_BLACK, RGB_BLACK};

// More CPU efficient delay
void PerformantDelay(uint8_t numLoops)
{
    for (uint8_t i = numLoops; i--;)
    {
        wait_vbl_done();
    }
}

void fadein() NONBANKED
{
    for (int i = 4; --i;)
    {
        set_bkg_palette(0, 1, fadeout_palette + i);
        set_sprite_palette(0, 1, fadeout_palette + i);
        PerformantDelay(5);
    }
}

//Thanks to basxto for the fadeout code.
//Edited
void fadeout() NONBANKED
{
    VBK_REG = 1;
    set_bkg_tiles(0, 0, 20, 18, Blank_map_attributes);
    VBK_REG = 0;

    for (int i = 1; i < 4; i++) 
    {
        set_bkg_palette(0, 1, fadeout_palette + i);
        set_sprite_palette(0, 1, fadeout_palette + i);
        PerformantDelay(18);
    }

    set_bkg_tiles(0, 0, 20, 18, BlckScrTiles);
}