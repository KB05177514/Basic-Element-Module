#include "stm32l0xx_hal.h"
#include "usart.h"
#include "rtc.h"
#include "system.h"
#include<string.h>

struct system
{
	enum bootmode boot_mode;
};

static struct system sys = 
{
	.boot_mode = boot_mode_power_on_start,
};

/*******************************************************************************
* Brief		:  
* Param    	: 
* Return	:      
*******************************************************************************/
void sys_bootmode(void)
{
	/*调用前确保RCC时钟以初始化*/

	enum bootmode sys_bootmode= boot_mode_power_on_start;

	/*打开PWR外设时钟*/
	__HAL_RCC_PWR_CLK_ENABLE();

	if(__HAL_PWR_GET_FLAG(PWR_FLAG_SB | PWR_FLAG_WU))
	{
		sys_bootmode = boot_mode_standby_wakeup;
		/*清除唤醒标志，否则无法再次进入休眠*/
		__HAL_PWR_CLEAR_FLAG(PWR_FLAG_SB | PWR_FLAG_WU);
	}
	else if(__HAL_RCC_GET_FLAG(RCC_FLAG_IWDGRST))
	{
		sys_bootmode = boot_mode_iwdg_reset;
	}
	else if(__HAL_RCC_GET_FLAG(RCC_FLAG_PORRST | RCC_FLAG_PINRST))
	{
		sys_bootmode = boot_mode_power_on_start;
	}

	/*清除复位标志*/
	__HAL_RCC_CLEAR_RESET_FLAGS();
	
	sys.boot_mode = sys_bootmode;
}

/*******************************************************************************
* Brief		:  
* Param    	: 
* Return	:      
*******************************************************************************/
enum bootmode sys_read_bootmode(void)
{
	return sys.boot_mode;
}

/*******************************************************************************
* Brief		:  
* Param    	: 
* Return	:      
*******************************************************************************/
void sys_clear_wakeuptimer_flag(void)
{
    __HAL_RCC_PWR_CLK_ENABLE();
    HAL_PWR_EnableBkUpAccess();
    RTC->ISR &= ~(RTC_FLAG_WUTF);
    HAL_PWR_DisableBkUpAccess();    
}

/*******************************************************************************
* Brief		:  
* Param    	: 
* Return	:      
*******************************************************************************/
void sys_clear_alarm_a_flag(void)
{
    __HAL_RCC_PWR_CLK_ENABLE();
    HAL_PWR_EnableBkUpAccess();
    RTC->ISR &= ~(RTC_FLAG_ALRAF);
//    HAL_PWR_DisableBkUpAccess();    	
}

/*******************************************************************************
* Brief		:  
* Param    	: 
* Return	:      
*******************************************************************************/
void sys_set_alarm_a_time(void)
{
	RTC_TimeTypeDef time;

	HAL_RTC_GetTime(&hrtc, &time, RTC_FORMAT_BIN);

	time.Minutes += 1;

	RTC_AlarmTypeDef alarm;
	alarm.AlarmTime = time;
	alarm.AlarmMask = RTC_ALARMMASK_DATEWEEKDAY;
	alarm.AlarmSubSecondMask = RTC_ALARMSUBSECONDMASK_ALL;
  	alarm.AlarmDateWeekDaySel = RTC_ALARMDATEWEEKDAYSEL_DATE;	
  	alarm.AlarmDateWeekDay = 0x1;
	alarm.Alarm = RTC_ALARM_A;
	
	HAL_StatusTypeDef status = HAL_RTC_SetAlarm_IT(&hrtc, &alarm, RTC_FORMAT_BIN);

	uint8_t tmp[32] = {0};
	sprintf((char*)tmp, "alarm.time=%d,status=%d.\n", alarm.AlarmTime.Minutes, status);
	HAL_UART_Transmit(&huart1, tmp, strlen((char *)tmp), 10);
	
}









