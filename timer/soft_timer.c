#include<stdint.h>
#include<stdbool.h>
#include "soft_timer.h"

/*******************************************************************************
* Brief		:  
* Param		: 
* Return	:      
*******************************************************************************/

/*******************************************************************************
* 1.1 ͨ��ʱ����صĺ�������                                                                                                     
*******************************************************************************/
static volatile uint32_t Count_5ms = 0;                                        	//5msʱ�ӱ�������

/*******************************************************************************
* Brief		: ��ȡ5ms��������ֵ 
* Param		: 
* Return	:      
*******************************************************************************/
uint32_t Read_5ms_Count(void)
{
    return Count_5ms;
}

/*******************************************************************************
* Brief		: 5ms�������ۼ� 
* Param		: 
* Return	:      
*******************************************************************************/
void Inc_5ms_Count(void)
{
    Count_5ms++;
}

/*******************************************************************************
* Brief		: �������ʱ�� 
* Param		: @Ptr:�����ʱ��ָ��
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
* Brief		: ��������ʱ�� 
* Param		: @Ptr:����ⶨʱ��ָ��;@DelayNum:��ʱֵ
* Return	: @true:�����ʱ����ʱ,false:�����ʱ��δ��ʱ     
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
        
            return true;                                             			//�����ʱ����ʱ
        }
    }   
             
    return false;                                                         		//�����ʱ��δ��ʱ         
}

/*******************************************************************************
* Brief		: �ر������ʱ�� 
* Param		: @Ptr:���ر������ʱ��ָ��
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










