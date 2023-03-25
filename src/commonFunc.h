#ifndef COMMONFUNC_H_INCLUDE
#define COMMONFUNC_H_INCLUDE

#include "gb.h"
#include "spriteStructs.h"
#include <stdio.h>

#define IS_FRAME_256 ((game_time & 0xFF) == 0)
#define IS_FRAME_128 ((game_time & 0x7F) == 0)
#define IS_FRAME_64 ((game_time & 0x3F) == 0)
#define IS_FRAME_32 ((game_time & 0x1F) == 0)
#define IS_FRAME_16 ((game_time & 0xF) == 0)
#define IS_FRAME_8 ((game_time & 0x7) == 0)
#define IS_FRAME_4 ((game_time & 0x3) == 0)
#define IS_FRAME_2 ((game_time & 0x1) == 0)
#define IS_FRAME_ODD ((game_time & 0x1) == 1)
#define IS_FRAME_EVEN ((game_time & 0x1) == 0)

extern UBYTE _cpu;
extern UINT8 game_time;

extern struct Player ship;

uint8_t getGBType();
void PerformantDelay(uint8_t numLoops);

#endif