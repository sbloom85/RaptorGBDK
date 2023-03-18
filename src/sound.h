#include "gb.h"

void InitializeSound()
{
    NR52_REG = 0X80;    // Is 1000 0000 in binary, turns on sound
    NR50_REG = 0X77;    // Sets the volume for both left and right channel
    NR51_REG = 0XFF;    // Selects which channels we want to use
}

void MachineGunSound()
{
    
}