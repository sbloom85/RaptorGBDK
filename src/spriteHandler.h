#ifndef SPRIHANDLE_H_INCLUDE
#define SPRIHANDLE_H_INCLUDE

void InitCursor();
void MoveCursor(uint8_t x, uint8_t y);
void initProjectiles();
void moveProjectiles();
void playerInit();
void setupShip();
void SetupEnemyShip();
void SetColliders();
void inputLoop();

#endif