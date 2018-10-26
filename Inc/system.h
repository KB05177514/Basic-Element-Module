#ifndef __system_H
#define __system_H


enum bootmode
{
	boot_mode_power_on_start 	= 0,
	boot_mode_standby_wakeup	= 1,
	boot_mode_iwdg_reset		= 2,
};

void sys_bootmode(void);
enum bootmode sys_read_bootmode(void);
void sys_clear_wakeuptimer_flag(void);
void sys_clear_alarm_a_flag(void);
void sys_set_alarm_a_time(void);




#endif




























