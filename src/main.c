#pragma bank 0

#include "gb.h"
#include "cgb.h"

#include "commonFunc.h"
#include "spriteHandler.h"
#include "gameSectionsB0.h"
#include "gameSectionsB2.h"
#include "gameHandler.h"

void InitializeSound()
{
    NR52_REG = 0X80;    // Is 1000 0000 in binary, turns on sound
    NR51_REG = 0XFF;    // Selects which channels we want to use
    NR50_REG = 0X77;    // Sets the volume for both left and right channel
}

void main(void)
{
    //ENABLE_RAM; //We don't need extra ram banks right now.

    SHOW_BKG;
    SHOW_SPRITES;
    DISPLAY_ON;

    //Same CPU Speed as DMG for lower power usage.
    cpu_slow();

    InitializeSound();
    //Bank 1:
    //Title, Menu, Intro
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
