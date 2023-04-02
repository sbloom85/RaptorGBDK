#ifndef GAMEHANDLE_H_INCLUDE
#define GAMEHANDLE_H_INCLUDE

#include "../backgrounds/BlankPLN1.h"
#include "../backgrounds/BlackScrTiles.h"

#include "../Window/RaptorDialogTiles.h"
#include "../Window/RaptorWindow.h"

void fadein();
void fadeout();
void init_camera();
void scroll_cam_up();
void set_camera();
void MoveEnemy();
void gameInit();
void gameLoop();


#endif