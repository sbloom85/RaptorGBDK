#ifndef COMMONFUNC_H_INCLUDE
#define COMMONFUNC_H_INCLUDE

#ifdef __TARGET_gb
#include <gb/gb.h>
#include <gb/sgb.h>
#include <gb/cgb.h>
#endif
#if defined(__TARGET_sms) || defined(__TARGET_gg)
#include <sms/sms.h>
#endif
#include "spriteStructs.h"
#include "projectile.h"
#include "../backgrounds/BlankPLN1.h"
#include "../backgrounds/BlackScrTiles.h"
#include <stdio.h>

#define IS_FRAME_256 ((game_time & 0xFF) == 0)
#define IS_FRAME_128 ((game_time & 0x7F) == 0)
#define IS_FRAME_64 ((game_time & 0x3F) == 0)
#define IS_FRAME_32 ((game_time & 0x1F) == 0)
#define IS_FRAME_16 ((game_time & 0xF) == 0)
#define IS_FRAME_15 ((game_time & 0xF) == 1)
#define IS_FRAME_8 ((game_time & 0x7) == 0)
#define IS_FRAME_7 ((game_time & 0x7) == 1)
#define IS_FRAME_4 ((game_time & 0x3) == 0)
#define IS_FRAME_3 ((game_time & 0x3) == 1)
#define IS_FRAME_2 ((game_time & 0x1) == 0)
#define IS_FRAME_ODD ((game_time & 0x1) == 1)
#define IS_FRAME_EVEN ((game_time & 0x1) == 0)

extern UBYTE _cpu;

#ifdef __TARGET_gb
//Place in free spot in HighRam
extern uint8_t AT(0xFF93) game_time;
#else
extern uint8_t game_time;
#endif


extern struct projectile newProjectile[20];
extern struct Enemy eShip1;

void PerformantDelay(uint8_t numLoops);
uint8_t getGBType();
void SGBTransferPalettes(const UWORD *SGBPallete);
void fadein();
void fadeout();
void fadeoutDMG();
void fadeoutCGB();

#endif