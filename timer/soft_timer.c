#include<stdint.h>
#include<stdbool.h>
#include "soft_timer.h"

/*******************************************************************************
* Brief		:  
* Param		: 
* Return	:      
*******************************************************************************/

/*******************************************************************************
* 1.1 通用时间相关的函数定义                                                                                                     
*******************************************************************************/
static volatile uint32_t Count_5ms = 0;                                        	//5ms时钟变量定义

/*******************************************************************************
* Brief		: 获取5ms计数器数值 
* Param		: 
* Return	:      
*******************************************************************************/
uint32_t Read_5ms_Count(void)
{
    return Count_5ms;
}

/*******************************************************************************
* Brief		: 5ms计数器累加 
* Param		: 
* Return	:      
*******************************************************************************/
void Inc_5ms_Count(void)
{
    Count_5ms++;
}

/*******************************************************************************
* Brief		: 打开软件定时器 
* Param		: @Ptr:软件定时器指针
* Return	:      
*******************************************************************************/
void TimerOpen( SoftTimerTypeDef * Ptr, uint32_t period, bool IsPeriod, TimerRegFunc RegFunc)
{
    Ptr->Enable = true;
    Ptr->IsPeriod = IsPeriod;
    Ptr->Count = Read_5ms_Count();
    Ptr->Period = period;
    Ptr->RegFunc = RegFunc;
}

/*******************************************************************************
* Brief		: 检查软件定时器 
* Param		: @Ptr:待检测定时器指针;@DelayNum:延时值
* Return	: @true:软件定时器超时,false:软件定时器未超时     
*******************************************************************************/
bool TimerCheck(SoftTimerTypeDef * Ptr)
{
    if(Ptr->Enable == true)
    {
        if((Read_5ms_Count() - Ptr->Count) > Ptr->Period)
        {
 			*Ptr->RegFunc(NULL);       	
			if(Ptr->IsPeriod == false)
			{
				TimerClose(Ptr);
			}
        
            return true;                                             			//软件定时器超时
        }
    }   
             
    return false;                                                         		//软件定时器未超时         
}

/*******************************************************************************
* Brief		: 关闭软件定时器 
* Param		: @Ptr:待关闭软件定时器指针
* Return	:      
*******************************************************************************/
void TimerClose(SoftTimerTypeDef * Ptr)
{
    Ptr->Enable = false;
    Ptr->Period = false;
    Ptr->Count = 0;  
    Ptr->Period = 0;
    Ptr->RegFunc = NULL;
}










