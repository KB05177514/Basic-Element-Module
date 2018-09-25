#include "normal_check_test.h"

/*******************************************************************************
* Description   : 一般校验测试程序 
* Param         : 
* Return        :      
*******************************************************************************/
void NormalCheckTestProcess(void)
{
    uint8_t result = 0;
    
    result = XorCheck((uint8_t *)TestData, 32);
    
    result = SumCheck((uint8_t *)TestData, 32);
    
    return;
}