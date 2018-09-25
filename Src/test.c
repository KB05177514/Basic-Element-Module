#include "test.h"

/*******************************************************************************
* Function Name : 
* Description   :  
* Input         :           
* Output        :         
* Return        :         
*******************************************************************************/
void Test_RtcInit(void)
{
    struct tm time = {.tm_year = 18 + 100, 
                      .tm_mon = 9 - 1, 
                      .tm_mday = 12,
                      .tm_hour = 9,
                      .tm_min = 14,
                      .tm_sec = 0,};    
    
    bool result = RTC_Open(&time);
    
    result = RTC_IsOpen();
    
    return;
}

/*******************************************************************************
* Function Name : 
* Description   :  
* Input         :           
* Output        :         
* Return        :         
*******************************************************************************/
void Test_RtcProcess(void)
{
    uint32_t time = 0;
    
    time = RTC_TimestampGet();
    
    float time_decimal = RTC_TimestampWithPointGet();
    
    RTC_TimestampWithPointByStrGet();
    
    vTaskDelay(100);
    
    time = 1536738648;
    
    bool result = RTC_DateTimeSetByTimestamp(time);
    
    return;
}




















