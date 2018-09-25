#ifndef __KB_RTC_H
#define __KB_RTC_H

#include "define.h"

/*******************************************************************************
* 1¡¢º¯ÊýÉùÃ÷
*******************************************************************************/ 
bool RTC_Open(struct tm * time);
void RTC_Close(void);
bool RTC_IsOpen(void);

bool RTC_DateTimeSetByTimestamp(uint32_t timestamp);
bool RTC_DateTimeSetByTm(struct tm * timeptr);
uint32_t RTC_TimestampGet(void);
float RTC_TimestampWithPointGet(void);
uint8_t * RTC_TimestampWithPointByStrGet(void);

bool RTC_UpdateTimerCallback(void);
























#endif