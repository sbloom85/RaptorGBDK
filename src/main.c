#include "gb.h"
#include "cgb.h"
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
    SHOW_BKG;
    SHOW_SPRITES;
    DISPLAY_ON;

    Title();
    //delay(5000);
    Hanger();
    initProjectiles();
    
    InitializeSound();
    BravoOne();
    setupShip();
    SetColliders();

    init_camera();

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
