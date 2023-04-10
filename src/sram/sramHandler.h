#ifndef SAVHANDLER_H_INCLUDE
#define SAVHANDLER_H_INCLUDE

#ifdef __TARGET_gb
#include <gb/gb.h>
#endif
#if defined(__TARGET_sms) || defined(__TARGET_gg)
#include <sms/sms.h>
#endif

void saveData(uint8_t saveSlot);
void loadData(uint8_t saveSlot);

#endif