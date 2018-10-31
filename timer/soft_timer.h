#ifndef __soft_timer_H
#define __soft_timer_H

#include<stdint.h>
#include<stdbool.h>


/*******************************************************************************
*1.ºê¶¨Òå      
*******************************************************************************/
typedef void *(*TimerRegFunc)(void * argv);

typedef struct
{                                                              
    volatile bool    	Enable;
    volatile bool 		IsPeriod;
    volatile uint32_t   Count;
    volatile uint32_t 	Period;
    TimerRegFunc 		RegFunc;
}SoftTimerTypeDef;

/*******************************************************************************
*2.APIÉùÃ÷      
*******************************************************************************/
uint32_t Read_5ms_Count(void);
void Inc_5ms_Count(void);
void TimerOpen( SoftTimerTypeDef * Ptr, uint32_t period, bool IsPeriod, TimerRegFunc RegFunc);
bool TimerCheck(SoftTimerTypeDef * Ptr);
void TimerClose(SoftTimerTypeDef * Ptr);

#endif
