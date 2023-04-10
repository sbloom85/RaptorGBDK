#ifdef __TARGET_gb
#pragma bank 3

#include "../sounds/hUGEDriver.h"
#include <stddef.h>

static const unsigned char order_cnt = 32;

static const unsigned char P0[] = {
    DN(Fs4,2,0x037),
    DN(___,0,0x037),
    DN(Fs4,3,0x037),
    DN(___,0,0x037),
    DN(___,0,0x037),
    DN(___,0,0x037),
    DN(Fs4,2,0x037),
    DN(___,0,0x037),
    DN(___,0,0x037),
    DN(___,0,0x037),
    DN(Fs4,2,0x037),
    DN(___,0,0x037),
    DN(Fs4,2,0x037),
    DN(___,0,0x037),
    DN(D_4,3,0x047),
    DN(___,0,0x047),
    DN(___,0,0x047),
    DN(___,0,0x047),
    DN(D_4,2,0x047),
    DN(___,0,0x047),
    DN(D_4,2,0x047),
    DN(___,0,0x047),
    DN(D_4,2,0x047),
    DN(___,0,0x047),
    DN(E_4,2,0x027),
    DN(___,0,0x027),
    DN(E_4,3,0x027),
    DN(___,0,0x027),
    DN(___,0,0x027),
    DN(___,0,0x027),
    DN(E_4,2,0x027),
    DN(___,0,0x027),
    DN(Fs4,2,0x037),
    DN(___,0,0x037),
    DN(Fs4,3,0x037),
    DN(___,0,0x037),
    DN(___,0,0x037),
    DN(___,0,0x037),
    DN(Fs4,2,0x037),
    DN(___,0,0x037),
    DN(___,0,0x037),
    DN(___,0,0x037),
    DN(Fs4,2,0x037),
    DN(___,0,0x037),
    DN(Fs4,2,0x037),
    DN(___,0,0x037),
    DN(A_4,3,0x047),
    DN(___,0,0x047),
    DN(___,0,0x047),
    DN(___,0,0x047),
    DN(A_4,2,0x047),
    DN(___,0,0x047),
    DN(A_4,2,0x047),
    DN(___,0,0x047),
    DN(A_4,2,0x047),
    DN(___,0,0x047),
    DN(E_4,2,0x027),
    DN(___,0,0x027),
    DN(E_4,3,0x027),
    DN(___,0,0x027),
    DN(___,0,0x027),
    DN(___,0,0x027),
    DN(E_4,2,0x027),
    DN(___,0,0x027),
};
static const unsigned char P1[] = {
    DN(Fs5,1,0x037),
    DN(___,0,0x037),
    DN(___,0,0x037),
    DN(___,0,0x037),
    DN(___,0,0x037),
    DN(___,0,0x037),
    DN(Fs5,1,0x037),
    DN(___,0,0x037),
    DN(___,0,0x037),
    DN(___,0,0x037),
    DN(Fs5,1,0x037),
    DN(___,0,0x037),
    DN(___,0,0x037),
    DN(___,0,0x037),
    DN(D_5,1,0x047),
    DN(___,0,0x047),
    DN(___,0,0x047),
    DN(___,0,0x047),
    DN(D_5,1,0x047),
    DN(___,0,0x047),
    DN(___,0,0x047),
    DN(___,0,0x047),
    DN(___,0,0x047),
    DN(___,0,0x047),
    DN(E_5,1,0x047),
    DN(___,0,0x047),
    DN(___,0,0x047),
    DN(___,0,0x047),
    DN(E_5,1,0x047),
    DN(___,0,0x047),
    DN(E_5,1,0x047),
    DN(___,0,0x047),
    DN(Fs5,1,0x037),
    DN(___,0,0x037),
    DN(___,0,0x037),
    DN(___,0,0x037),
    DN(___,0,0x037),
    DN(___,0,0x037),
    DN(Fs5,1,0x037),
    DN(___,0,0x037),
    DN(___,0,0x037),
    DN(___,0,0x037),
    DN(Fs5,1,0x037),
    DN(___,0,0x037),
    DN(___,0,0x037),
    DN(___,0,0x037),
    DN(A_5,1,0x047),
    DN(___,0,0x047),
    DN(___,0,0x047),
    DN(___,0,0x047),
    DN(A_5,1,0x047),
    DN(___,0,0x047),
    DN(___,0,0x047),
    DN(___,0,0x047),
    DN(___,0,0x047),
    DN(___,0,0x047),
    DN(E_5,1,0x047),
    DN(___,0,0x047),
    DN(___,0,0x047),
    DN(___,0,0x047),
    DN(E_5,1,0x047),
    DN(___,0,0x047),
    DN(E_5,1,0x047),
    DN(___,0,0x047),
};
static const unsigned char P2[] = {
    DN(Fs3,2,0x000),
    DN(___,0,0xC03),
    DN(Fs4,2,0x421),
    DN(___,0,0x422),
    DN(___,0,0x423),
    DN(___,0,0xC03),
    DN(Fs4,2,0x000),
    DN(___,0,0x000),
    DN(Fs3,2,0x000),
    DN(___,0,0xC03),
    DN(Fs4,2,0x000),
    DN(___,0,0xC03),
    DN(Fs3,2,0x000),
    DN(___,0,0xC03),
    DN(D_4,2,0x421),
    DN(___,0,0x422),
    DN(___,0,0x423),
    DN(___,0,0x000),
    DN(D_3,2,0x000),
    DN(___,0,0xC03),
    DN(D_4,2,0x000),
    DN(___,0,0xC03),
    DN(D_3,2,0x000),
    DN(___,0,0xC03),
    DN(E_3,2,0x000),
    DN(___,0,0xC03),
    DN(E_4,2,0x421),
    DN(___,0,0x422),
    DN(___,0,0x423),
    DN(___,0,0xC03),
    DN(E_4,2,0x000),
    DN(___,0,0xC03),
    DN(Fs3,2,0x000),
    DN(___,0,0xC03),
    DN(Fs4,2,0x421),
    DN(___,0,0x422),
    DN(___,0,0x423),
    DN(___,0,0xC03),
    DN(Fs4,2,0x000),
    DN(___,0,0x000),
    DN(Fs3,2,0x000),
    DN(___,0,0xC03),
    DN(Fs4,2,0x000),
    DN(___,0,0xC03),
    DN(Fs3,2,0x000),
    DN(___,0,0xC03),
    DN(A_4,2,0x421),
    DN(___,0,0x422),
    DN(___,0,0x423),
    DN(___,0,0x000),
    DN(A_3,2,0x000),
    DN(___,0,0xC03),
    DN(A_4,2,0x000),
    DN(___,0,0xC03),
    DN(A_3,2,0x000),
    DN(___,0,0xC03),
    DN(E_3,2,0x000),
    DN(___,0,0xC03),
    DN(E_4,2,0x421),
    DN(___,0,0x422),
    DN(___,0,0x423),
    DN(___,0,0xC03),
    DN(E_4,2,0x000),
    DN(___,0,0xC03),
};
static const unsigned char P3[] = {
    DN(A_5,2,0xE03),
    DN(___,0,0x000),
    DN(A_5,2,0xE03),
    DN(___,0,0x000),
    DN(C_5,1,0x000),
    DN(___,0,0x000),
    DN(A_5,2,0xE03),
    DN(___,0,0x000),
    DN(A_5,2,0xE01),
    DN(___,0,0x000),
    DN(A_5,2,0xE03),
    DN(___,0,0x000),
    DN(C_5,1,0x000),
    DN(___,0,0x000),
    DN(A_5,2,0xE03),
    DN(___,0,0x000),
    DN(A_5,2,0xE01),
    DN(___,0,0x000),
    DN(A_5,2,0xE03),
    DN(___,0,0x000),
    DN(C_5,1,0x000),
    DN(___,0,0x000),
    DN(A_5,2,0xE03),
    DN(___,0,0x000),
    DN(A_5,2,0xE03),
    DN(___,0,0x000),
    DN(A_5,2,0xE03),
    DN(___,0,0x000),
    DN(C_5,1,0x000),
    DN(___,0,0x000),
    DN(A_5,2,0xE03),
    DN(___,0,0x000),
    DN(A_5,2,0xE03),
    DN(___,0,0x000),
    DN(A_5,2,0xE03),
    DN(___,0,0x000),
    DN(C_5,1,0x000),
    DN(___,0,0x000),
    DN(A_5,2,0xE03),
    DN(___,0,0x000),
    DN(A_5,2,0xE01),
    DN(___,0,0x000),
    DN(A_5,2,0xE03),
    DN(___,0,0x000),
    DN(C_5,1,0x000),
    DN(___,0,0x000),
    DN(A_5,2,0xE03),
    DN(___,0,0x000),
    DN(A_5,2,0xE01),
    DN(___,0,0x000),
    DN(A_5,2,0xE03),
    DN(___,0,0x000),
    DN(C_5,1,0x000),
    DN(___,0,0x000),
    DN(A_5,2,0xE03),
    DN(___,0,0x000),
    DN(A_5,2,0xE03),
    DN(___,0,0x000),
    DN(A_5,2,0xE03),
    DN(___,0,0x000),
    DN(C_5,1,0x000),
    DN(___,0,0x000),
    DN(A_5,2,0xE03),
    DN(___,0,0x000),
};
static const unsigned char P4[] = {
    DN(___,0,0xA05),
    DN(___,0,0xA05),
    DN(E_4,9,0x000),
    DN(Fs4,9,0x30F),
    DN(___,0,0x30F),
    DN(___,0,0x000),
    DN(A_4,9,0x000),
    DN(___,0,0x8EF),
    DN(A_4,9,0xC06),
    DN(___,0,0x8FF),
    DN(B_4,9,0x000),
    DN(___,0,0x8EF),
    DN(A_4,9,0xC06),
    DN(___,0,0x8FF),
    DN(B_4,9,0x000),
    DN(Cs5,9,0x30F),
    DN(___,0,0x30F),
    DN(___,0,0x000),
    DN(E_5,9,0x000),
    DN(___,0,0x000),
    DN(A_4,9,0x000),
    DN(___,0,0x000),
    DN(A_4,9,0xA04),
    DN(___,0,0x000),
    DN(Gs4,9,0x000),
    DN(___,0,0x000),
    DN(E_4,9,0x000),
    DN(___,0,0x000),
    DN(___,0,0x8EF),
    DN(E_4,9,0xC07),
    DN(Fs4,9,0x8FF),
    DN(___,0,0x8EF),
    DN(Fs4,9,0xC07),
    DN(___,0,0x8FF),
    DN(Gs4,9,0x000),
    DN(A_4,9,0x30F),
    DN(___,0,0x30F),
    DN(___,0,0x000),
    DN(A_4,9,0x000),
    DN(___,0,0x8EF),
    DN(A_4,9,0xC07),
    DN(___,0,0x8FF),
    DN(Gs4,9,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(E_4,9,0x412),
    DN(___,0,0x412),
    DN(___,0,0x412),
    DN(___,0,0x412),
    DN(Cs4,9,0x000),
    DN(___,0,0x000),
    DN(E_4,9,0x8EF),
    DN(Cs4,9,0xC07),
    DN(E_4,9,0x8EF),
    DN(E_4,9,0xC07),
    DN(Fs4,9,0x8FF),
    DN(___,0,0x000),
    DN(Gs4,9,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(A_4,9,0x30F),
    DN(___,0,0x30F),
};
static const unsigned char P8[] = {
    DN(___,0,0xA05),
    DN(___,0,0xA05),
    DN(Gs4,9,0x000),
    DN(A_4,9,0x30F),
    DN(___,0,0x30F),
    DN(___,0,0x000),
    DN(A_4,9,0x000),
    DN(___,0,0x8EF),
    DN(A_4,9,0xC07),
    DN(___,0,0x8FF),
    DN(Gs4,9,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(Gs4,9,0x000),
    DN(A_4,9,0x30F),
    DN(___,0,0x30F),
    DN(___,0,0x000),
    DN(Gs4,9,0x000),
    DN(___,0,0x000),
    DN(Fs4,9,0x000),
    DN(___,0,0x8EF),
    DN(Fs4,9,0xC07),
    DN(___,0,0x8FF),
    DN(Fs4,9,0x000),
    DN(___,0,0x000),
    DN(Gs4,9,0x000),
    DN(___,0,0x000),
    DN(___,0,0x8EF),
    DN(Gs4,9,0xC07),
    DN(A_4,9,0x8FF),
    DN(___,0,0x8EF),
    DN(A_4,9,0xC07),
    DN(___,0,0x8FF),
    DN(Gs4,9,0x000),
    DN(A_4,9,0x30F),
    DN(___,0,0x30F),
    DN(___,0,0x000),
    DN(A_4,9,0x000),
    DN(___,0,0x8EF),
    DN(A_4,9,0xC07),
    DN(___,0,0x8FF),
    DN(B_4,9,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(B_4,9,0x412),
    DN(Cs5,9,0x412),
    DN(___,0,0x412),
    DN(___,0,0x412),
    DN(E_5,9,0x000),
    DN(___,0,0x000),
    DN(Cs5,9,0x8EF),
    DN(E_5,9,0xC07),
    DN(Cs5,9,0x8EF),
    DN(Cs5,9,0xC07),
    DN(B_4,9,0x8FF),
    DN(___,0,0x000),
    DN(Gs4,9,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(A_4,9,0x30F),
    DN(___,0,0x000),
};
static const unsigned char P9[] = {
    DN(A_5,2,0xE03),
    DN(___,0,0x000),
    DN(A_5,2,0xE03),
    DN(___,0,0x000),
    DN(A_5,2,0x000),
    DN(___,0,0x000),
    DN(A_5,2,0xE03),
    DN(___,0,0x000),
    DN(A_5,2,0xE01),
    DN(___,0,0x000),
    DN(A_5,2,0xE03),
    DN(___,0,0x000),
    DN(A_5,2,0x000),
    DN(___,0,0x000),
    DN(A_5,2,0xE03),
    DN(___,0,0x000),
    DN(A_5,2,0xE01),
    DN(___,0,0x000),
    DN(A_5,2,0xE03),
    DN(___,0,0x000),
    DN(A_5,2,0x000),
    DN(___,0,0x000),
    DN(A_5,2,0xE03),
    DN(___,0,0x000),
    DN(A_5,2,0xE03),
    DN(___,0,0x000),
    DN(A_5,2,0xE03),
    DN(___,0,0x000),
    DN(A_5,2,0x000),
    DN(___,0,0x000),
    DN(A_5,2,0xE03),
    DN(___,0,0x000),
    DN(A_5,2,0xE03),
    DN(___,0,0x000),
    DN(A_5,2,0xE03),
    DN(___,0,0x000),
    DN(A_5,2,0x000),
    DN(___,0,0x000),
    DN(A_5,2,0xE03),
    DN(___,0,0x000),
    DN(A_5,2,0xE01),
    DN(___,0,0x000),
    DN(A_5,2,0xE03),
    DN(___,0,0x000),
    DN(A_5,2,0x000),
    DN(___,0,0x000),
    DN(A_5,2,0xE03),
    DN(___,0,0x000),
    DN(A_5,2,0xE01),
    DN(___,0,0x000),
    DN(A_5,2,0xE03),
    DN(___,0,0x000),
    DN(A_5,2,0x000),
    DN(___,0,0x000),
    DN(A_5,2,0xE03),
    DN(___,0,0x000),
    DN(A_5,2,0xE03),
    DN(___,0,0x000),
    DN(A_5,2,0xE03),
    DN(___,0,0x000),
    DN(A_5,2,0x000),
    DN(___,0,0x000),
    DN(A_5,2,0xE03),
    DN(___,0,0x000),
};
static const unsigned char P10[] = {
    DN(Cs5,5,0x000),
    DN(___,0,0xC03),
    DN(Cs5,5,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0xC03),
    DN(Cs5,5,0x000),
    DN(___,0,0xC03),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(Cs5,5,0x000),
    DN(___,0,0xC03),
    DN(Cs5,5,0x000),
    DN(___,0,0xC03),
    DN(A_4,5,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0xC03),
    DN(A_4,5,0x000),
    DN(___,0,0xC03),
    DN(A_4,5,0x000),
    DN(___,0,0xC03),
    DN(A_4,5,0x000),
    DN(___,0,0x000),
    DN(B_4,5,0x000),
    DN(___,0,0xC03),
    DN(B_4,5,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0xC03),
    DN(B_4,5,0x000),
    DN(___,0,0xC03),
    DN(Cs5,5,0x000),
    DN(___,0,0xC03),
    DN(Cs5,5,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0xC03),
    DN(Cs5,5,0x000),
    DN(___,0,0xC03),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(Cs5,5,0x000),
    DN(___,0,0xC03),
    DN(Cs5,5,0x000),
    DN(___,0,0xC03),
    DN(E_5,5,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0xC03),
    DN(E_5,5,0x000),
    DN(___,0,0xC03),
    DN(E_5,5,0x000),
    DN(___,0,0xC03),
    DN(E_5,5,0x000),
    DN(___,0,0x000),
    DN(B_4,5,0x000),
    DN(___,0,0xC03),
    DN(B_4,5,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0xC03),
    DN(B_4,5,0x000),
    DN(___,0,0xC03),
};
static const unsigned char P11[] = {
    DN(Fs4,5,0x000),
    DN(Fs4,5,0xC03),
    DN(Fs4,5,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(Fs4,5,0xC03),
    DN(Fs4,5,0x000),
    DN(Fs4,5,0xC03),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(Fs4,5,0x000),
    DN(Fs4,5,0xC03),
    DN(Fs4,5,0x000),
    DN(Fs4,5,0xC03),
    DN(D_4,5,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(D_4,5,0xC03),
    DN(D_4,5,0x000),
    DN(D_4,5,0xC03),
    DN(D_4,5,0x000),
    DN(D_4,5,0xC03),
    DN(D_4,5,0x000),
    DN(___,0,0x000),
    DN(E_4,5,0x000),
    DN(E_4,5,0xC03),
    DN(E_4,5,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(E_4,5,0xC03),
    DN(E_4,5,0x000),
    DN(E_4,5,0xC03),
    DN(Fs4,5,0x000),
    DN(Fs4,5,0xC03),
    DN(Fs4,5,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(Fs4,5,0xC03),
    DN(Fs4,5,0x000),
    DN(Fs4,5,0xC03),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(Fs4,5,0x000),
    DN(Fs4,5,0xC03),
    DN(Fs4,5,0x000),
    DN(Fs4,5,0xC03),
    DN(A_4,5,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(A_4,5,0xC03),
    DN(A_4,5,0x000),
    DN(A_4,5,0xC03),
    DN(A_4,5,0x000),
    DN(A_4,5,0xC03),
    DN(A_4,5,0x000),
    DN(___,0,0x000),
    DN(E_4,5,0x000),
    DN(E_4,5,0xC03),
    DN(E_4,5,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(E_4,5,0xC03),
    DN(E_4,5,0x000),
    DN(E_4,5,0xC03),
};
static const unsigned char P12[] = {
    DN(___,0,0x8BD),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x8AD),
    DN(___,0,0xA01),
    DN(___,0,0x8BC),
    DN(___,0,0xA01),
    DN(___,0,0x8AD),
    DN(___,0,0xA01),
    DN(___,0,0x8BC),
    DN(___,0,0xA01),
    DN(___,0,0x8AD),
    DN(___,0,0xA01),
    DN(___,0,0x8BC),
    DN(___,0,0xA01),
    DN(___,0,0x8FF),
    DN(B_4,9,0x000),
    DN(Cs5,9,0x30F),
    DN(___,0,0x30F),
    DN(___,0,0x000),
    DN(B_4,9,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(Gs4,9,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(Gs4,9,0xC03),
    DN(A_4,9,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x8AD),
    DN(___,0,0xA01),
    DN(___,0,0x8BC),
    DN(___,0,0xA01),
    DN(___,0,0x8AD),
    DN(___,0,0xA01),
    DN(___,0,0x8BC),
    DN(___,0,0xA01),
    DN(___,0,0x8AD),
    DN(___,0,0xA01),
    DN(___,0,0x8BC),
    DN(___,0,0xA01),
    DN(Gs4,9,0x8FF),
    DN(A_4,9,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(Gs4,9,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(E_4,9,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(E_4,9,0xC03),
};
static const unsigned char P13[] = {
    DN(Fs4,9,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x8AD),
    DN(___,0,0xA01),
    DN(___,0,0x8BC),
    DN(___,0,0xA01),
    DN(___,0,0x8AD),
    DN(___,0,0xA01),
    DN(___,0,0x8BC),
    DN(___,0,0xA01),
    DN(___,0,0x8AD),
    DN(___,0,0xA01),
    DN(___,0,0x8BC),
    DN(___,0,0xA01),
    DN(___,0,0x8FF),
    DN(___,0,0x8AD),
    DN(___,0,0xA01),
    DN(___,0,0x8BC),
    DN(___,0,0xA01),
    DN(___,0,0x8AD),
    DN(___,0,0xA01),
    DN(___,0,0x8BC),
    DN(___,0,0xA01),
    DN(___,0,0x8AD),
    DN(___,0,0xA01),
    DN(___,0,0x8BC),
    DN(___,0,0xA01),
    DN(___,0,0x8FF),
    DN(___,0,0x8AD),
    DN(___,0,0xA01),
    DN(___,0,0x8BC),
    DN(___,0,0xA01),
    DN(___,0,0x8AD),
    DN(___,0,0xA01),
    DN(___,0,0x8BC),
    DN(___,0,0xA01),
    DN(___,0,0x8AD),
    DN(___,0,0xA01),
    DN(___,0,0x8BC),
    DN(___,0,0xA01),
    DN(___,0,0x8FF),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(B_4,9,0x000),
    DN(Cs5,9,0x30F),
    DN(___,0,0x30F),
    DN(___,0,0x000),
    DN(E_5,9,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
};
static const unsigned char P14[] = {
    DN(E_5,9,0x000),
    DN(Fs5,9,0x30F),
    DN(___,0,0x30F),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x8AD),
    DN(___,0,0xA01),
    DN(___,0,0x8BC),
    DN(___,0,0xA01),
    DN(___,0,0x8AD),
    DN(___,0,0xA01),
    DN(Fs5,9,0x8FF),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(Gs5,9,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(Gs5,9,0x000),
    DN(A_5,9,0x30F),
    DN(___,0,0x30F),
    DN(A_5,9,0xC03),
    DN(Gs5,9,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(Gs5,9,0xC03),
    DN(E_5,9,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(Cs5,9,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(Cs5,9,0x8AD),
    DN(___,0,0xA01),
    DN(___,0,0x8BC),
    DN(___,0,0xA01),
    DN(B_4,9,0x8FF),
    DN(Cs5,9,0x30F),
    DN(___,0,0x30F),
    DN(___,0,0x000),
    DN(B_4,9,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(A_4,9,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(Gs4,9,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(Gs4,9,0xC03),
    DN(E_4,9,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(E_4,9,0xC03),
};
static const unsigned char P15[] = {
    DN(E_4,9,0x000),
    DN(Fs4,9,0x30F),
    DN(___,0,0x30F),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x8AD),
    DN(___,0,0xA01),
    DN(___,0,0x8BC),
    DN(___,0,0xA01),
    DN(___,0,0x8AD),
    DN(___,0,0xA01),
    DN(Fs4,9,0x8FF),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(Gs4,9,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(Gs4,9,0x000),
    DN(A_4,9,0x30F),
    DN(___,0,0x30F),
    DN(A_4,9,0xC03),
    DN(Gs4,9,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(Gs4,9,0xC03),
    DN(A_4,9,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(Cs5,9,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x8AD),
    DN(___,0,0xA01),
    DN(___,0,0x8BC),
    DN(___,0,0xA01),
    DN(B_4,9,0x8FF),
    DN(Cs5,9,0x30F),
    DN(___,0,0x30F),
    DN(___,0,0x000),
    DN(E_5,9,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(Fs5,9,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(Gs5,9,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(Gs5,9,0xC03),
    DN(E_5,9,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(E_5,9,0xC03),
};
static const unsigned char P16[] = {
    DN(E_5,9,0x000),
    DN(Fs5,9,0x30F),
    DN(___,0,0x300),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x8FE),
    DN(___,0,0xA01),
    DN(___,0,0x8EF),
    DN(___,0,0xA01),
    DN(___,0,0x8FE),
    DN(___,0,0xA01),
    DN(___,0,0x8EF),
    DN(___,0,0xA01),
    DN(___,0,0x8FE),
    DN(___,0,0xA01),
    DN(___,0,0x8EF),
    DN(___,0,0xA01),
    DN(___,0,0x8FE),
    DN(___,0,0xA01),
    DN(___,0,0x8EF),
    DN(___,0,0xA01),
    DN(___,0,0x8FE),
    DN(___,0,0xA01),
    DN(___,0,0x8EF),
    DN(___,0,0xA01),
    DN(___,0,0x8FE),
    DN(___,0,0xA01),
    DN(___,0,0x8FF),
    DN(___,0,0xA01),
    DN(Fs5,1,0x037),
    DN(___,0,0x037),
    DN(___,0,0x037),
    DN(___,0,0x037),
    DN(___,0,0x037),
    DN(___,0,0x037),
    DN(Fs5,1,0x037),
    DN(___,0,0x037),
    DN(___,0,0x037),
    DN(___,0,0x037),
    DN(Fs5,1,0x037),
    DN(___,0,0x037),
    DN(___,0,0x037),
    DN(___,0,0x037),
    DN(A_5,1,0x047),
    DN(___,0,0x047),
    DN(___,0,0x047),
    DN(___,0,0x047),
    DN(A_5,1,0x047),
    DN(___,0,0x047),
    DN(___,0,0x047),
    DN(___,0,0x047),
    DN(___,0,0x047),
    DN(___,0,0x047),
    DN(E_5,1,0x047),
    DN(___,0,0x047),
    DN(___,0,0x047),
    DN(___,0,0x047),
    DN(E_5,1,0x047),
    DN(___,0,0x047),
    DN(E_5,1,0x047),
    DN(___,0,0x047),
};

static const unsigned char itNoiseSP1[] = {
    DN(___,0,0x000),
    DN(53,0,0x000),
    DN(44,0,0x000),
    DN(33,0,0x000),
    DN(44,5,0x000),
    DN(37,0,0x000),
    DN(37,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,1,0x000),
};
static const unsigned char itNoiseSP2[] = {
    DN(___,0,0x000),
    DN(63,0,0x000),
    DN(64,0,0x000),
    DN(63,0,0x000),
    DN(62,5,0x000),
    DN(63,0,0x000),
    DN(62,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,1,0x000),
};
static const unsigned char itNoiseSP3[] = {
    DN(___,0,0x000),
    DN(56,0,0x000),
    DN(56,0,0x000),
    DN(54,0,0x000),
    DN(53,5,0x000),
    DN(50,0,0x000),
    DN(47,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,1,0x000),
};
static const unsigned char itNoiseSP4[] = {
    DN(___,0,0x000),
    DN(36,0,0x000),
    DN(36,0,0x000),
    DN(36,0,0x000),
    DN(36,5,0x000),
    DN(36,0,0x000),
    DN(36,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,1,0x000),
};
static const unsigned char itNoiseSP5[] = {
    DN(___,0,0x000),
    DN(36,0,0x000),
    DN(36,0,0x000),
    DN(36,0,0x000),
    DN(36,5,0x000),
    DN(36,0,0x000),
    DN(36,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,1,0x000),
};
static const unsigned char itNoiseSP6[] = {
    DN(___,0,0x000),
    DN(36,0,0x000),
    DN(36,0,0x000),
    DN(36,0,0x000),
    DN(36,5,0x000),
    DN(36,0,0x000),
    DN(36,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,1,0x000),
};
static const unsigned char itNoiseSP7[] = {
    DN(___,0,0x000),
    DN(36,0,0x000),
    DN(36,0,0x000),
    DN(36,0,0x000),
    DN(36,5,0x000),
    DN(36,0,0x000),
    DN(36,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,1,0x000),
};
static const unsigned char itNoiseSP8[] = {
    DN(___,0,0x000),
    DN(36,0,0x000),
    DN(36,0,0x000),
    DN(36,0,0x000),
    DN(36,5,0x000),
    DN(36,0,0x000),
    DN(36,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,1,0x000),
};
static const unsigned char itNoiseSP9[] = {
    DN(___,0,0x000),
    DN(36,0,0x000),
    DN(36,0,0x000),
    DN(36,0,0x000),
    DN(36,5,0x000),
    DN(36,0,0x000),
    DN(36,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,1,0x000),
};
static const unsigned char itNoiseSP10[] = {
    DN(___,0,0x000),
    DN(36,0,0x000),
    DN(36,0,0x000),
    DN(36,0,0x000),
    DN(36,5,0x000),
    DN(36,0,0x000),
    DN(36,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,1,0x000),
};
static const unsigned char itNoiseSP11[] = {
    DN(___,0,0x000),
    DN(36,0,0x000),
    DN(36,0,0x000),
    DN(36,0,0x000),
    DN(36,5,0x000),
    DN(36,0,0x000),
    DN(36,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,1,0x000),
};
static const unsigned char itNoiseSP12[] = {
    DN(___,0,0x000),
    DN(36,0,0x000),
    DN(36,0,0x000),
    DN(36,0,0x000),
    DN(36,5,0x000),
    DN(36,0,0x000),
    DN(36,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,1,0x000),
};
static const unsigned char itNoiseSP13[] = {
    DN(___,0,0x000),
    DN(36,0,0x000),
    DN(36,0,0x000),
    DN(36,0,0x000),
    DN(36,5,0x000),
    DN(36,0,0x000),
    DN(36,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,1,0x000),
};
static const unsigned char itNoiseSP14[] = {
    DN(___,0,0x000),
    DN(36,0,0x000),
    DN(36,0,0x000),
    DN(36,0,0x000),
    DN(36,5,0x000),
    DN(36,0,0x000),
    DN(36,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,1,0x000),
};
static const unsigned char itNoiseSP15[] = {
    DN(___,0,0x000),
    DN(36,0,0x000),
    DN(36,0,0x000),
    DN(36,0,0x000),
    DN(36,5,0x000),
    DN(36,0,0x000),
    DN(36,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,1,0x000),
};
static const unsigned char* const order1[] = {P0,P0,P4,P8,P4,P8,P12,P13,P14,P15,P14,P15,P14,P15,P16,P1};
static const unsigned char* const order2[] = {P1,P1,P0,P0,P0,P0,P11,P11,P11,P11,P11,P11,P0,P0,P0,P0};
static const unsigned char* const order3[] = {P2,P2,P2,P2,P2,P2,P10,P10,P10,P10,P10,P10,P2,P2,P2,P2};
static const unsigned char* const order4[] = {P3,P3,P3,P3,P3,P3,P9,P9,P9,P9,P9,P9,P3,P3,P3,P3};

static const hUGEDutyInstr_t duty_instruments[] = {
    {8,0,99,0,128},
    {8,64,161,0,128},
    {8,192,165,0,128},
    {8,192,240,0,128},
    {8,128,112,0,128},
    {8,64,241,0,128},
    {8,128,241,0,128},
    {8,192,241,0,128},
    {8,0,240,0,128},
    {8,128,240,0,128},
    {8,128,240,0,128},
    {8,128,240,0,128},
    {8,128,240,0,128},
    {8,128,240,0,128},
    {8,128,240,0,128},
};
static const hUGEWaveInstr_t wave_instruments[] = {
    {0,64,0,0,128},
    {0,32,1,0,128},
    {0,32,2,0,128},
    {0,32,3,0,128},
    {0,64,2,0,128},
    {0,32,5,0,128},
    {0,32,6,0,128},
    {0,32,7,0,128},
    {0,32,8,0,128},
    {0,32,9,0,128},
    {0,32,10,0,128},
    {0,32,11,0,128},
    {0,32,12,0,128},
    {0,32,13,0,128},
    {0,32,14,0,128},
};
static const hUGENoiseInstr_t noise_instruments[] = {
    {241,itNoiseSP1,192,0,0},
    {128,itNoiseSP2,57,0,0},
    {241,itNoiseSP3,121,0,0},
    {240,itNoiseSP4,0,0,0},
    {240,itNoiseSP5,0,0,0},
    {240,itNoiseSP6,0,0,0},
    {240,itNoiseSP7,0,0,0},
    {240,itNoiseSP8,0,0,0},
    {240,itNoiseSP9,0,0,0},
    {240,itNoiseSP10,0,0,0},
    {240,itNoiseSP11,0,0,0},
    {240,itNoiseSP12,0,0,0},
    {240,itNoiseSP13,0,0,0},
    {240,itNoiseSP14,0,0,0},
    {240,itNoiseSP15,0,0,0},
};

static const unsigned char waves[] = {
    0,0,255,255,255,255,255,255,255,255,255,255,255,255,255,255,
    51,48,17,7,120,137,153,85,171,187,187,187,187,187,165,85,
    0,0,0,0,0,0,0,0,255,255,255,255,255,255,255,255,
    0,0,0,0,0,0,0,0,0,0,0,0,255,255,255,255,
    0,1,18,35,52,69,86,103,120,137,154,171,188,205,222,239,
    254,220,186,152,118,84,50,16,18,52,86,120,154,188,222,255,
    122,205,219,117,33,19,104,189,220,151,65,1,71,156,221,184,
    15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,
    254,252,250,248,246,244,242,240,242,244,246,248,250,252,254,255,
    254,221,204,187,170,153,136,119,138,189,241,36,87,138,189,238,
    132,17,97,237,87,71,90,173,206,163,23,121,221,32,3,71,
    184,98,22,176,173,112,219,98,65,121,23,30,6,68,34,181,
    153,122,138,136,77,228,165,107,216,19,41,114,231,55,44,226,
    82,108,51,37,168,205,104,187,188,91,185,224,109,230,53,44,
    205,19,195,94,25,145,185,210,176,22,84,98,80,94,19,148,
    194,212,115,83,36,217,125,211,140,93,53,225,55,212,13,148,
};

const hUGESong_t ArachnoSadTouch = {5, &order_cnt, order1, order2, order3,order4, duty_instruments, wave_instruments, noise_instruments, NULL, waves};
#endif