#pragma bank 0

#include "gb.h"
#include "cgb.h"

//#include <stdio.h>

#include "commonFunc.h"
#include "spriteHandler.h"
#include "gameSectionsB0.h"
#include "gameSectionsB2.h"
#include "gameHandler.h"

#include "sgb_border.h"
#include "../backgrounds/SGBBack.h"

void InitializeSound()
{
    NR52_REG = 0X80;    // Is 1000 0000 in binary, turns on sound
    NR51_REG = 0XFF;    // Selects which channels we want to use
    NR50_REG = 0X77;    // Sets the volume for both left and right channel
}

void main(void)
{
    // Wait 4 frames
    // For SGB on PAL SNES this delay is required on startup, otherwise borders don't show up
    for (uint8_t i = 4; i != 0; i--) wait_vbl_done();

    DISPLAY_ON;

    //Bank 1:
    //Title, Menu, Intro
    SWITCH_ROM(3);
    set_sgb_border(SGBBack_tiles, sizeof(SGBBack_tiles), SGBBack_map, sizeof(SGBBack_map), SGBBack_palettes, sizeof(SGBBack_palettes));

    wait_vbl_done();

    SHOW_BKG;
    SHOW_SPRITES;

    //Same CPU Speed as DMG for lower power usage.
    //cpu_slow();

    InitializeSound();
    SWITCH_ROM(1);
    Title();
    Menu();
    //Bank 2:
    //Hanger, Shop, Sector Select, 
    //Background and Sprite Handlers
    //Menu, Hanger, and Player Sprites
    SWITCH_ROM(2);
    Hanger();
}
