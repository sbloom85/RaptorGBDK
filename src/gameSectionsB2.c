#pragma bank 2

#include "gb.h"
#include "cgb.h"

#include "maps.h"

#include "commonFunc.h"
#include "spriteHandler.h"
#include "gameHandler.h"
#include "gameSectionsCommon.h"
#include "gameSectionsB0.h"
#include "gameSectionsB2.h"

#include "sram/sramHandler.h"

const enum selected {Shop = 0, Fly = 1, Save = 2, Exit = 3};

static const uint16_t black_palette[] = {RGB_BLACK, RGB_BLACK, RGB_BLACK, RGB_BLACK, RGB_BLACK, RGB_BLACK, RGB_BLACK};

void WepShop() BANKED
{
    set_bkg_palette(0, 4, &bkgShopPalette[0]);
    set_bkg_data(0, 47, ShopTiles);

    if (sgb_check()) {
        SGBTransferPalettes(bkgShopPalette);
    }

    VBK_REG = 1;
    set_bkg_tiles(0, 0, 20, 18, ShopScreenPLN1);
    VBK_REG = 0;
    set_bkg_tiles(0, 0, 20, 18, ShopScreenPLN0);

    HIDE_SPRITES;
    SHOW_BKG;

    while (1)
    {
        wait_vbl_done();
        
        if (joypad() & J_A)
        {
            fadeout();
            HIDE_BKG;
            SHOW_SPRITES;
            Hanger();
        }
    }
}

void HangerSelection(enum selected selection) BANKED
{
    if (selection == Fly)
    {
        MoveCursor(30, 74);
    } else if (selection == Shop)
    {
        MoveCursor(135, 74);
    } else if (selection == Save)
    {
        MoveCursor(150, 50);
    } else //Exit
    {
        MoveCursor(80, 140);
    }
}

void Hanger() NONBANKED
{
    //Helps hide some graphics corruption
    set_bkg_palette(0, 1, &black_palette[0]);
    set_bkg_data(0, Hanger_TILE_COUNT, Hanger_tiles);
    set_bkg_palette(0, Hanger_PALETTE_COUNT, &Hanger_palettes[0]);

    if (sgb_check()) {
        SGBTransferPalettes(Hanger_palettes);
    }

    VBK_REG = 1;
    set_bkg_tiles(0, 0, 20, 18, Hanger_map_attributes);
    VBK_REG = 0;
    set_bkg_tiles(0, 0, 20, 18, Hanger_map);

    enum selected selection;
    selection = 1;

    InitCursor();
    MoveCursor(30, 74); //Default to Fly for now.

    playerInit();

    SHOW_SPRITES;
    SHOW_BKG;

    while (1)
    {
        uint8_t joyInput = joypad();

        PerformantDelay(8);

        if (joyInput & J_LEFT)
        {
            if (selection > 0)
            {
                selection--;
            } else {
                selection = 3;
            }

            HangerSelection(selection);

        } else if (joyInput & J_RIGHT) {
            if (selection < 3)
            {
                selection++;
            } else {
                selection = 0;
            }

            HangerSelection(selection);
        }

        if (joyInput & J_UP)
        {
            if (selection > 0)
            {
                selection--;
            } else {
                selection = 3;
            }

            HangerSelection(selection);

        } else if (joyInput & J_DOWN) {
            if (selection < 3)
            {
                selection++;
            } else {
                selection = 0;
            }

            HangerSelection(selection);
        }

        if (joyInput & J_A && selection == Fly)
        {
            HIDE_SPRITES;
            fadeout();
            gameInit();
            BravoOne();
            gameLoop();
        } else if (joyInput & J_A && selection == Shop) {
            fadeout();
            WepShop();
        } else if (joyInput & J_A && selection == Save) {
            saveData(0);
        } else if (joyInput & J_A && selection == Exit) {
            fadeout();
            SWITCH_ROM(1);
            HIDE_SPRITES;
            Menu();
            //reset();
        }
    }
}