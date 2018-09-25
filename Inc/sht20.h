#ifndef __STH20_H
#define __STH20_H

/*******************************************************************************
*1、外部函数声明     
*******************************************************************************/
void SHT20_Open(void);
void SHT20_Close(void);
bool SHT20_WriteTMeasureCmd(void);
bool SHT20_ReadTData(void);
bool SHT20_WriteRHMeasureCmd(void);
bool SHT20_ReadRHData(void);
float SHT20_GetT(void);
float SHT20_GetRH(void);
void SHT20_Handler(void);

#endif