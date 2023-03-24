#include "../backgrounds/Title.h"
#include "../backgrounds/Menu.h"
#include "../backgrounds/Hanger.h"
#include "../backgrounds/Shop.h"
#include "../backgrounds/ShopTiles.h"
#include "../maps/Bravo1TilesGBC.h"
#include "../maps/BravoW1GBC.h"

const UWORD bkgSGBPaletteTitle[] = {
	RGB_WHITE, RGB(15, 15, 15), RGB_RED, RGB(5, 5, 5)
};

const UWORD bkgSGBPaletteHanger[] = {
    Bravo1MapTilesCGBPal0c0, Bravo1MapTilesCGBPal0c1, Bravo1MapTilesCGBPal0c2, Bravo1MapTilesCGBPal0c3,
};

const UWORD bkgSGBPaletteWater[] = {
	Bravo1MapTilesCGBPal1c0, Bravo1MapTilesCGBPal1c1, Bravo1MapTilesCGBPal2c2, RGB(5, 5, 5),
};

const UWORD bkgShopPalette[] = {
    ShopTilesCGBPal0c0, ShopTilesCGBPal0c1, ShopTilesCGBPal0c2, ShopTilesCGBPal0c3,
    ShopTilesCGBPal1c0, ShopTilesCGBPal1c1, ShopTilesCGBPal1c2, ShopTilesCGBPal1c3,
    ShopTilesCGBPal2c0, ShopTilesCGBPal2c1, ShopTilesCGBPal2c2, ShopTilesCGBPal2c3,
    ShopTilesCGBPal3c0, ShopTilesCGBPal3c1, ShopTilesCGBPal3c2, ShopTilesCGBPal3c3,
};

const UWORD bkgBravo1Palette[] = {
	Bravo1MapTilesCGBPal0c0, Bravo1MapTilesCGBPal0c1, Bravo1MapTilesCGBPal0c2, Bravo1MapTilesCGBPal0c3,
    Bravo1MapTilesCGBPal1c0, Bravo1MapTilesCGBPal1c1, Bravo1MapTilesCGBPal1c2, Bravo1MapTilesCGBPal1c3,
    Bravo1MapTilesCGBPal2c0, Bravo1MapTilesCGBPal2c1, Bravo1MapTilesCGBPal2c2, Bravo1MapTilesCGBPal2c3,
    Bravo1MapTilesCGBPal3c0, Bravo1MapTilesCGBPal3c1, Bravo1MapTilesCGBPal3c2, Bravo1MapTilesCGBPal3c3,
    Bravo1MapTilesCGBPal4c0, Bravo1MapTilesCGBPal4c1, Bravo1MapTilesCGBPal4c2, Bravo1MapTilesCGBPal4c3,
    Bravo1MapTilesCGBPal5c0, Bravo1MapTilesCGBPal5c1, Bravo1MapTilesCGBPal5c2, Bravo1MapTilesCGBPal5c3,
    Bravo1MapTilesCGBPal6c0, Bravo1MapTilesCGBPal6c1, Bravo1MapTilesCGBPal6c2, Bravo1MapTilesCGBPal6c3,
    Bravo1MapTilesCGBPal7c0, Bravo1MapTilesCGBPal7c1, Bravo1MapTilesCGBPal7c2, Bravo1MapTilesCGBPal7c3,
};