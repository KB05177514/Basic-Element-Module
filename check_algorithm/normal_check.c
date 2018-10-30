#include "normal_check.h"

/*******************************************************************************
* Description   :  
* Param         : 
* Return        :      
*******************************************************************************/
/****************************************************************************** 
* Description   : 异或校验  
* Param         : @pSrc 待校验数据头指针 
                : @Len 待校验数据长度
* Return        : 异或校验结果        
*******************************************************************************/
uint8_t XorCheck(uint8_t * pSrc, uint32_t Len)
{
    uint32_t cnti = 0;
    uint8_t result = 0;
    
    for(; cnti < Len; cnti++)
    {
        result ^= *(pSrc + cnti);
    }
    
    return result;
}

/******************************************************************************* 
* Description   : 和校验 
* Param         : @pSrc 待校验数据头指针
                : @Len 待校验数据长度
* Return        : 和校验结果     
*******************************************************************************/
uint8_t SumCheck(uint8_t * pSrc, uint32_t Len)
{
    uint32_t cnti = 0;
    uint8_t result = 0;
    
    for(; cnti < Len; cnti++)
    {
        result += *(pSrc + cnti);
    }
    
    return result;
}






