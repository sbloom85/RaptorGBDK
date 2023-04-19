#pragma bank 0

#ifdef __TARGET_gb
#include <gb/gb.h>
#include <gb/cgb.h>
#endif
#ifdef __TARGET_gg
#include <sms/sms.h>
#endif

#include "commonFunc.h"
#include "spriteHandler.h"
#include "gameSectionsB0.h"
#include "gameSectionsB2.h"
#include "gameHandler.h"

#include "sgb_border.h"
#include "../backgrounds/SGBBack.h"

void InitializeSound()
{
    #ifdef __TARGET_gb
    NR52_REG = 0X80;    // Is 1000 0000 in binary, turns on sound
    NR51_REG = 0XFF;    // Selects which channels we want to use
    NR50_REG = 0X77;    // Sets the volume for both left and right channel
    #endif
}

void main(void)
{
    // Wait 4 frames
    // For SGB on PAL SNES this delay is required on startup, otherwise borders don't show up
    #ifdef __TARGET_gb
    if (sgb_check()) 
    {
        for (uint8_t i = 4; i != 0; i--) wait_vbl_done();
    }
    #endif
    
    DISPLAY_ON;

    SWITCH_ROM(1);
    #ifdef __TARGET_gb
    if (sgb_check())
    {
        set_sgb_border(SGBBack_tiles, sizeof(SGBBack_tiles), SGBBack_map, sizeof(SGBBack_map), SGBBack_palettes, sizeof(SGBBack_palettes));
    }
    #endif
        
    SHOW_BKG;
    SHOW_SPRITES;

    InitializeSound();
    //SWITCH_ROM(1);
    Title();
    Menu();
    SWITCH_ROM(3);
    Hanger();
}
