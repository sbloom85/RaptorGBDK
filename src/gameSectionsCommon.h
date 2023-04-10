#ifndef GAMESECTC_H_INCLUDE
#define GAMESECTC_H_INCLUDE
#ifdef __TARGET_gb
#include <gb/gb.h>
#endif
#ifdef __TARGET_gg
#include <sms/sms.h>
#endif

extern int8_t BGP_REG_OLD;
extern uint8_t mapTileSet;

extern int16_t camera_y, old_camera_y;

extern uint8_t map_pos_y;
extern uint8_t old_map_pos_y;

extern uint8_t currentMapBank;

#endif