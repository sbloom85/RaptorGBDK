#include "gb.h"

// Generic character structure: id, position, graphics
struct GameCharacter
{
    UBYTE spriteids[12];    // Character uses 12 sprites
    uint8_t x, y;           // Character X and Y positions
    uint8_t width, height;  // Character width and height
};