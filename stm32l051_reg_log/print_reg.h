#ifndef __print_reg_H
#define __print_reg_H

/*******************************************************************************
* Brief		:  
* Param    	: 
* Return	:      
*******************************************************************************/
#define BIT_0                               (0x01 << 0)
#define BIT_1                               (0x01 << 1)
#define BIT_2                               (0x01 << 2)
#define BIT_3                               (0x01 << 3)
#define BIT_4                               (0x01 << 4)
#define BIT_5                               (0x01 << 5)
#define BIT_6                               (0x01 << 6)
#define BIT_7                               (0x01 << 7)
#define BIT_8                               (0x01 << 8)
#define BIT_9                               (0x01 << 9)
#define BIT_10                              (0x01 << 10)
#define BIT_11                              (0x01 << 11)
#define BIT_12                              (0x01 << 12)
#define BIT_13                              (0x01 << 13)
#define BIT_14                              (0x01 << 14)
#define BIT_15                              (0x01 << 15)
#define BIT_16                              (0x01 << 16)
#define BIT_17                              (0x01 << 17)
#define BIT_18                              (0x01 << 18)
#define BIT_19                              (0x01 << 19)
#define BIT_20                              (0x01 << 20)
#define BIT_21                              (0x01 << 21)
#define BIT_22                              (0x01 << 22)
#define BIT_23                              (0x01 << 23)
#define BIT_24                              (0x01 << 24)
#define BIT_25                              (0x01 << 25)
#define BIT_26                              (0x01 << 26)
#define BIT_27                              (0x01 << 27)
#define BIT_28                              (0x01 << 28)
#define BIT_29                              (0x01 << 29)
#define BIT_30                              (0x01 << 30)
#define BIT_31                              (0x01 << 31)

/*RTC macro define*/
#define RTC_CR                              BIT_0
#define RTC_DR                              BIT_1






void print_iwdg_reg(void);
void print_sys_boot_reg(void);
void print_rtc_reg(void);






#endif






