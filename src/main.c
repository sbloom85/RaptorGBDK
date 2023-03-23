#pragma bank 0

#include "gb.h"
#include "sgb.h"
#include "cgb.h"
#include <stdio.h>
#include <stdlib.h>

#include "commonFunc.h"
#include "spriteHandler.h"
#include "backgroundHandler.h"
//#include "fade_manager.h"

void InitializeSound()
{
    NR52_REG = 0X80;    // Is 1000 0000 in binary, turns on sound
    NR51_REG = 0XFF;    // Selects which channels we want to use
    NR50_REG = 0X77;    // Sets the volume for both left and right channel
}

void main(void)
{
    //ENABLE_RAM;

    SHOW_BKG;
    SHOW_SPRITES;
    DISPLAY_ON;

    //Same CPU Speed as DMG to assure game runs right on both.
    if (getGBType() == CGB_TYPE)
    {
        cpu_slow();
    }

    InitializeSound();
    SWITCH_ROM_MBC5(2);
    Title();
    Hanger();
    initProjectiles();
    init_camera();
    //SWITCH_ROM_MBC5(2);
    BravoOne();
    //SWITCH_ROM_MBC5(1);
    setupShip();
    SetColliders();

    //Main Game Loop
    while (1)
    {
        set_camera();

        scroll_cam_up();

        moveProjectiles();

        inputLoop();

        PerformantDelay(2);
        // delay(25);
    }
}
