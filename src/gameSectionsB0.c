#pragma bank 0

#ifdef __TARGET_gb
#include <gb/gb.h>
#include <gb/cgb.h>
#endif
#ifdef __TARGET_gg
#include <sms/sms.h>
#endif

#include <stdio.h>
#include <string.h>

#include "maps.h"

#include "commonFunc.h"
#include "spriteHandler.h"
#include "gameHandler.h"
#include "gameSectionsCommon.h"
#include "gameSectionsB0.h"
#include "gameSectionsB2.h"

void Title() NONBANKED
{
    #ifdef __TARGET_gb
    set_bkg_palette(0, Intro_PALETTE_COUNT, &Intro_palettes[0]);
    
    set_bkg_data(0, Intro_TILE_COUNT, Intro_tiles);
    #ifdef __TARGET_gb
    if (sgb_check()) {
        SGBTransferPalettes(Intro_palettes);
    }
    #endif
    //VBK_REG = 1;
    set_bkg_tiles(0, 0, 20, 18, Intro_map);
    //VBK_REG = 0;
    //set_bkg_tiles(0, 0, 20, 18, Intro_map);
    #endif

    #ifdef __TARGET_gg
    set_palette(0, TitleGG_PALETTE_COUNT, &TitleGG_palettes[0]);

    set_bkg_4bpp_data(0, TitleGG_TILE_COUNT, TitleGG_tiles);

    set_tile_map_compat(0, 0, 20, 18, TitleGG_map);
    #endif

    PerformantDelay(130);
    //SWITCH_ROM(3);
    fadeout();
    SWITCH_ROM(2);
}

void Menu() NONBANKED
{
    SWITCH_ROM(2);

    #ifdef __TARGET_gb
    set_bkg_palette(0, Menu_PALETTE_COUNT, &Menu_palettes[0]);
    
    set_bkg_data(0, Menu_TILE_COUNT, Menu_tiles);
    
    if (sgb_check()) {
        SGBTransferPalettes(Menu_palettes);
    }
    
    VBK_REG = 1;
    set_bkg_tiles(0, 0, 20, 18, Menu_map_attributes);
    VBK_REG = 0;
    
    set_bkg_tiles(0, 0, 20, 18, Menu_map);
    #endif

    #ifdef __TARGET_gg
    set_palette(0, MenuGG_PALETTE_COUNT, &MenuGG_palettes[0]);

    set_bkg_4bpp_data(0, MenuGG_TILE_COUNT, MenuGG_tiles);

    set_tile_map_compat(0, 0, 20, 18, MenuGG_map);
    #endif

    while (1)
    {
        wait_vbl_done();

        if (joypad() & J_A)
        {
            SWITCH_ROM(3);
            fadeout();
            //SWITCH_ROM(1);
            //break;
            Hanger();
        }
    }
}

void BravoOne() NONBANKED
{
    #ifdef __TARGET_gb
    mapTileSet = 1;
    set_bkg_palette(0, 8, &bkgBravo1Palette[0]);

    if (sgb_check()) {
        SGBTransferPalettes(bkgSGBBravo1Palette);
    }
    #endif
    
    SWITCH_ROM(Bravo1MapTilesMainBank);

    #ifdef __TARGET_gb
    VBK_REG = 1;
    //set_bkg_data(0, 128, Bravo1MapTilesVBank1);
    set_bkg_data(128, 128, Bravo1MapTilesVBank1);
    VBK_REG = 0;
    if (sgb_check())
    {
        set_bkg_data(0, 128, Bravo1MapTilesMain);
    } else {
        set_bkg_data(0, 102, Bravo1MapTilesMain);
    }
    
    set_bkg_data(128, 128, Bravo1MapTilesSGB);
    #endif

    map_pos_y = (uint8_t)(camera_y >> 3u);

    currentMapBank = 6;
    SWITCH_ROM(currentMapBank);

    #ifdef __TARGET_gg
    set_palette(0, 1, &BravoW1TilesGG_palettes[0]);

    set_bkg_4bpp_data(0, BravoW1TilesGG_TILE_COUNT, BravoW1TilesGG_tiles);
    #endif

    #ifdef __TARGET_gb
    currentMapPLN0 = (unsigned char*)BravoWave1PLN0;
    currentMapPLN1 = (unsigned char*)BravoWave1PLN1;
    currentMapPLN2 = (unsigned char*)BravoWave1PLN2;
    #endif
    #ifdef __TARGET_gg
    currentMapPLN0 = (unsigned char*)BravoW1MapGG_map;
    #endif
    
    //memcpy(0xCA00, currentMapPLN2, sizeof(currentMapPLN2));

    #ifdef __TARGET_gb
    hUGE_init(&Rap08);
    #endif

    #ifdef __TARGET_gb
    for (uint8_t i = 144; i--;)
    {
        VBK_REG = VBK_ATTRIBUTES;
        set_bkg_based_submap(0, map_pos_y +i, 20, 1, (unsigned char*)currentMapPLN1, 20, 0);
        VBK_REG = VBK_TILES;
        set_bkg_based_submap(0, map_pos_y +i, 20, 1, (unsigned char*)currentMapPLN0, 20, 128);
    }
    #endif

    #ifdef __TARGET_gg
    for (uint8_t i = 144; i--;)
    {
        set_tile_submap_compat(0, map_pos_y +i, 20, 1, 20, (unsigned char*)currentMapPLN0);
        
    }
    #endif
    gameLoop();

    //map_pos_y = 0;
    old_map_pos_y = 255;

    //Switch back to Bank 2 for Game Handler use.
    SWITCH_ROM(3);
}