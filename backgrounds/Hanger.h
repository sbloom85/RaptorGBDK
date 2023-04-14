//AUTOGENERATED FILE FROM png2asset
#ifndef METASPRITE_Hanger_H
#define METASPRITE_Hanger_H

#include <stdint.h>
#include <gbdk/platform.h>
#include <gbdk/metasprites.h>

#define Hanger_TILE_ORIGIN 0
#define Hanger_TILE_W 8
#define Hanger_TILE_H 8
#define Hanger_WIDTH 160
#define Hanger_HEIGHT 144
#define Hanger_TILE_COUNT 219
#define Hanger_PALETTE_COUNT 8
#define Hanger_COLORS_PER_PALETTE 4
#define Hanger_TOTAL_COLORS 32
#define Hanger_MAP_ATTRIBUTES Hanger_map_attributes
#define Hanger_MAP_ATTRIBUTES_WIDTH 20
#define Hanger_MAP_ATTRIBUTES_HEIGHT 18
#define Hanger_MAP_ATTRIBUTES_PACKED_WIDTH 20
#define Hanger_MAP_ATTRIBUTES_PACKED_HEIGHT 18

BANKREF_EXTERN(Hanger)

extern const palette_color_t Hanger_palettes[32];
extern const uint8_t Hanger_tiles[3504];

extern const unsigned char Hanger_map[360];
extern const unsigned char Hanger_map_attributes[360];

#endif
