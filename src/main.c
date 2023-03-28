#pragma bank 0

#include "gb.h"
//#include "sgb.h"
#include "cgb.h"
#include "bgb_emu.h"
#include <stdio.h>
#include <stdlib.h>

#include "commonFunc.h"
#include "spriteHandler.h"
#include "backgroundHandler.h"

void InitializeSound()
{
    NR52_REG = 0X80;    // Is 1000 0000 in binary, turns on sound
    NR51_REG = 0XFF;    // Selects which channels we want to use
    NR50_REG = 0X77;    // Sets the volume for both left and right channel
}

void main(void)
{
    //BGB_MESSAGE("TEST"); //For debuging

    //ENABLE_RAM_MBC5; //We don't need extra ram banks right now.

    SHOW_BKG;
    SHOW_SPRITES;
    DISPLAY_ON;

    //Same CPU Speed as DMG for lower power usage.
    if (getGBType() == 3)
    {
        cpu_slow();
    }

    InitializeSound();
    //Bank 1:
    //Title, Menu, Intro
    SWITCH_ROM_MBC5(1);
    Title();
    Menu();
    //Bank 2:
    //Hanger, Shop, Sector Select, 
    //Background and Sprite Handlers
    //Menu, Hanger, and Player Sprites
    SWITCH_ROM_MBC5(2);
    Hanger();
}
