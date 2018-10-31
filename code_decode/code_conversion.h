#ifndef __code_conversion_H
#define __code_conversion_H

#include<stdint.h>
#include<stdbool.h>

/*
* @APIÉùÃ÷
*/
int16_t HexToAscii(int8_t SrcData);
void HexToAsciiS(uint8_t * pSrc, uint32_t Len, uint8_t * pDes);
bool AsciiToHex(int8_t DataHigh, int8_t DataLower, int8_t ResultData);
bool AsciiToHexS(uint8_t * pSrc, uint32_t Len, uint8_t * pDes);
uint8_t ByteToBcd2(uint8_t Value);
uint8_t Bcd2ToByte(uint8_t Value);
#endif