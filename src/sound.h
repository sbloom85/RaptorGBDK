/*-----------------------------------------------------------------------------
 *
 *  RaptorGBDK: A Gameboy Demake based off the MSDOS Game 
 *  Raptor: Call of the Shadows
 *  Copyright (C) 1994 by
 *  Apogee Software, Scott Host, Rich Fleider, Tim Neveu,  
 *  Matt Murphy, Robert Prince, Les Dorscheid, Steven Maines
 *
 *  This program is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU General Public License
 *  as published by the Free Software Foundation; either version 2
 *  of the License, or (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA
 *  02111-1307, USA.
 *
 *-----------------------------------------------------------------------------*/

// Channel 1, register 0, frequency sweep settings
// 7    Unused
// 6-4  Sweep time (update rate, if 0, sweeping is off)
// 3    Sweep direction (1: decrease; 0: increase)
// 2-0  Sweep shift amount (if 0, sweeping is off)
// 0001 0110 = 0x16, sweep time 1, sweep direction increase, shift amount per step 110 (6)

// Channel 1, register 1: Wave pattern duty and sound length
// Channels 1, 2 and 4
// 7-6: Wave pattern duty cycle 03 (12.5%, 25%, 50%, 75%), duty cycle is how long a quadrangular wave is "on" vs "off" so 50% (2) is both equal.
// 5-0: Sound length (higher number = shorter length)
// 0100 0000: 0X40, duty cycle 1 (25%), wave length 0 (long)

// Channel 1, register 2: Volume envelope (makes the volume get louder or quieter each "tick")
// On channels 1, 2 and 4
// 7-4  (Initial) Channel volume
// 3    Volume sweep direction (0: down, 1: up)
// 2-0  Length of each step in sweep (if 0, sweeping is off)
// NOTE: Each step is n/64 seconds long, where "n" is 1-7
// 0111 0011 is 0x73, volume 7, sweep down, step length 3

// Channel 1, register 3: Frequency least significant bits and noise options
// For channels 1, 2 and 3
// 7-0  8 least significant bits of frequency (3 most significant bits are set in register 4)

// Channel 1, register 4: Playback and frequency most significant bits
// All channels
// 7    Initialize
// 6    Consecutive select/length counter enable (read/write). When "0", regardless of the length of data on the NR11 register, sound can be produced
// 5-3  Unused
// 2-0  3 most significant bits of frequency
// 1100 0011    is 0xC3, initialize, not consecutive, frequency = MSB + LSB = 011 0000 0000 = 0x300


#ifndef SOUND_H_INCLUDE
#define SOUND_H_INCLUDE

#ifdef __TARGET_gb
#include <gb/gb.h>
#endif
#ifdef __TARGET_gg
#include <sms/sms.h>
#endif

#include <stddef.h>

#ifdef __TARGET_gb
// Plays when machine gun is fired
void MachineGunSound()
{
    NR10_REG = 0x1D;
    NR11_REG = 0x40;
    NR12_REG = 0x73;
    NR13_REG = 0x9C;
    NR14_REG = 0x84;
}

// Plays when missile is fired
void MissileSound()
{
    NR10_REG = 0x5E;
    NR11_REG = 0x00;
    NR12_REG = 0x57;
    NR13_REG = 0x73;
    NR14_REG = 0x86;
}

// Plays when a new weapon item is picked up
void WeaponPickupSound()
{
    NR10_REG = 0x75;
    NR11_REG = 0x00;
    NR12_REG = 0x40;
    NR13_REG = 0x73;
    NR14_REG = 0x86;
}

// Plays when bonus money is picked up
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
    NR10_REG = 0x44;
    NR11_REG = 0x00;
    NR12_REG = 0x57;
    NR13_REG = 0x73;
    NR14_REG = 0x86;
}

// Plays when player or enemy is destroyed
void DeadSound()
{
    NR10_REG = 0x4B;
    NR11_REG = 0x00;
    NR12_REG = 0x57;
    NR13_REG = 0x73;
    NR14_REG = 0x86;
}

// Plays when a laser weapon is fired
void LaserWeaponSound()
{
    NR10_REG = 0x34;
    NR11_REG = 0x01;
    NR12_REG = 0x73;
    NR13_REG = 0x73;
    NR14_REG = 0x86;
}

// Plays when Twin Laser is fired
void TwinLaserSound()
{
    
}

// Plays when an enemy fires
void EnemyShotSound()
{
    NR10_REG = 0x1D;
    NR11_REG = 0x40;
    NR12_REG = 0x73;
    NR13_REG = 0x73;
    NR14_REG = 0x86;
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

// Plays during the final wave of Bravo Sector
void BravoBossWaveMusic()
{

}

// Plays during the final wave of Tango Sector
void TangoBossWaveMusic()
{

}

// Plays during the final wave of the Outer Regions
void OuterBossWaveMusic()
{

}

//Plays during Game Over
void GameOverMusic()
{

}

// Plays during credits
void CreditsMusic()
{

}
#endif

#endif