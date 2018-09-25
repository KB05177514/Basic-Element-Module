#ifndef __POWER_H
#define __POWER_H

#include "define.h"

/*******************************************************************************
*1、外部函数声明     
*******************************************************************************/
void Power_SensorOpen(void);
void Power_SensorClose(void);
bool Power_SensorPowerIsOpen(void);

void Power_STBPowerSwitch2_7V(bool input);
bool Power_STBPowerIs2_7V(void);

void Power_VACCOpen(void);
void Power_VACCClose(void);
bool Power_VACCIsOpen(void);


#endif