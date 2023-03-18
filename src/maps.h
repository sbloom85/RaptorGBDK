#include "gb.h"
#include "../maps/BravoW1.h"
#include "../maps/RaptorMapTiles.h"

void BravoOne()
{
    set_bkg_data(0, 51, RaptorTilesBravo);
    set_bkg_tiles(0, 0, 20, 255, BravoWave1);
}