#include "gb.h"
#include "hUGEDriver.h"
#include <stddef.h>

void InitializeSound()
{
    NR52_REG = 0X80;    // Is 1000 0000 in binary, turns on sound
    NR51_REG = 0XFF;    // Selects which channels we want to use
    NR50_REG = 0X77;    // Sets the volume for both left and right channel
}

void TutorialSound()
{
    // Channel 1, register 0, frequency sweep settings
    // 7    Unused
    // 6-4  Sweep time (update rate, if 0, sweeping is off)
    // 3    Sweep direction (1: decrease; 0: increase)
    // 2-0  Sweep shift amount (if 0, sweeping is off)
    // 0001 0110 = 0x16, sweep time 1, sweep direction increase, shift amount per step 110 (6)
    NR10_REG = 0x16;
    
    // Channel 1, register 1: Wave pattern duty and sound length
    // Channels 1, 2 and 4
    // 7-6: Wave pattern duty cycle 03 (12.5%, 25%, 50%, 75%), duty cycle is how long a quadrangular wave is "on" vs "off" so 50% (2) is both equal.
    // 5-0: Sound length (higher number = shorter length)
    // 0100 0000: 0X40, duty cycle 1 (25%), wave length 0 (long)
    NR11_REG = 0X40;

    // Channel 1, register 2: Volume envelope (makes the volume get louder or quieter each "tick")
    // On channels 1, 2 and 4
    // 7-4  (Initial) Channel volume
    // 3    Volume sweep direction (0: down, 1: up)
    // 2-0  Length of each step in sweep (if 0, sweeping is off)
    // NOTE: Each step is n/64 seconds long, where "n" is 1-7
    // 0111 0011 is 0x73, volume 7, sweep down, step length 3
    NR12_REG = 0x73;

    // Channel 1, register 3: Frequency least significant bits and noise options
    // For channels 1, 2 and 3
    // 7-0  8 least significant bits of frequency (3 most significant bits are set in register 4)
    NR13_REG = 0x00;

    // Channel 1, register 4: Playback and frequency most significant bits
    // All channels
    // 7    Initialize
    // 6    Consecutive select/length counter enable (read/write). When "0", regardless of the length of data on the NR11 register, sound can be produced
    // 5-3  Unused
    // 2-0  3 most significant bits of frequency
    // 1100 0011    is 0xC3, initialize, not consecutive, frequency = MSB + LSB = 011 0000 0000 = 0x300
    NR14_REG = 0xC3;
}

// Plays when machine gun is fired
void MachineGunSound()
{
    NR10_REG = 0x1D;
    NR11_REG = 0x40;
    NR12_REG = 0x73;
    NR13_REG = 0x9C;
    NR14_REG = 0x84;
}

void MissileSound()
{
    NR10_REG = 0x5E;
    NR11_REG = 0x00;
    NR12_REG = 0x57;
    NR13_REG = 0x73;
    NR14_REG = 0x86;
}

void WeaponPickupSound()
{
    NR10_REG = 0x75;
    NR11_REG = 0x00;
    NR12_REG = 0x40;
    NR13_REG = 0x73;
    NR14_REG = 0x86;
}

void MoneyPickupSound()
{
    NR10_REG = 0x44;
    NR11_REG = 0x00;
    NR12_REG = 0x57;
    NR13_REG = 0x73;
    NR14_REG = 0x86;
}

// Plays when player or enemy is hit with projectile
void HitSound()
{

}

// Plays when player or enemy is destroyed
void DeadSound()
{

}

void TutorialMusic()
{
    
}

// Plays when the title screen is displayed
void TitleMusic()
{

}

// Plays when in the hangar
void HangarMusic()
{

}

// Plays during Bravo Sector
void BravoMusic()
{

}

// Plays during Tango Sector
void TangoMusic()
{

}

// Plays during Outer Regions
void OuterMusic()
{

}

// Plays during credits
void CreditsMusic()
{

}