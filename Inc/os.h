#ifndef __OS_H
#define __OS_H

#include "define.h"

/*******************************************************************************
* 1、任务句柄声明
*******************************************************************************/
extern osThreadId LedTaskHandle;
extern osThreadId RtcTaskHandle;
extern osThreadId TestTaskHandle;

/*******************************************************************************
* 2、定时器句柄声明
*******************************************************************************/
extern osTimerId LedTimerHandle;
extern osTimerId RtcUpdateTimerHandle;










#endif