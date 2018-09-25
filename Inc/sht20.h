#ifndef __STH20_H
#define __STH20_H

/*******************************************************************************
*1、外部函数声明     
*******************************************************************************/
void SHT20_Open(void);
void SHT20_Close(void);

static bool SHT20_ReadTemperature(void);
static bool SHT20_ReadRelativeHumidity(void);

float SHT20_GetTemperature(void);
float SHT20_GetRelativeHumidity(void);

void SHT20_Handler(void);

#endif