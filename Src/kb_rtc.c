#include "kb_rtc.h"

/*******************************************************************************
* 1、结构体定义
*******************************************************************************/ 
typedef struct
{
    bool Open;
    
    uint32_t timestamp;
    
    uint8_t timestr[50];
}RtcTypeDef;

/*******************************************************************************
* 2、变量定义
*******************************************************************************/
RtcTypeDef Rtc = {.Open = false, .timestamp = 0};

/*******************************************************************************
* Function Name : 
* Description   : 打开RTC 
* Input         :           
* Output        :         
* Return        :         
*******************************************************************************/
bool RTC_Open(struct tm * time)
{
    /*rtc硬件初始化*/
    MX_RTC_Init();
    
    /*设置rtc时间*/
    if(RTC_DateTimeSetByTm(time) == false)
    {
        return false;
    }
    
    /*开启linux时间戳刷新定时器*/
    if(xTimerChangePeriod(RtcUpdateTimerHandle, 500, 100) == pdFAIL)
    {
        return false;
    }
    
    Rtc.Open = true;
    
    return true;
}

/*******************************************************************************
* Function Name : 
* Description   : 关闭RTC 
* Input         :           
* Output        :         
* Return        :         
*******************************************************************************/
void RTC_Close(void)
{
    HAL_RTC_DeInit(&hrtc);
    
    Rtc.Open = false;
}

/*******************************************************************************
* Function Name : 
* Description   : 查询RTC是否开启 
* Input         :           
* Output        :         
* Return        :         
*******************************************************************************/
bool RTC_IsOpen(void)
{
    return Rtc.Open;
}

/*******************************************************************************
* Function Name : 
* Description   ：以linux时间戳设置RTC时间 
* Input         :           
* Output        :         
* Return        :         
*******************************************************************************/
bool RTC_DateTimeSetByTimestamp(uint32_t timestamp)
{
    struct tm time;
    uint32_t timestamp_tmp = timestamp;
    
    time = *gmtime(&timestamp_tmp);
    
    return(RTC_DateTimeSetByTm(&time));
}

/*******************************************************************************
* Function Name : 
* Description   : 以struct tm时间设置RTC时间
* Input         :           
* Output        :         
* Return        :         
*******************************************************************************/
bool RTC_DateTimeSetByTm(struct tm * timeptr)
{  
    RTC_DateTypeDef date = {.Year = timeptr->tm_year - 100, 
                            .Month = timeptr->tm_mon + 1,
                            .Date = timeptr->tm_mday,};
    HAL_StatusTypeDef hal_status = HAL_RTC_SetDate(&hrtc, &date, RTC_FORMAT_BIN);
    if(hal_status == HAL_OK)
    {
        /*日期设置成功*/
    }
    else
    {
        /*日期设置失败*/
        return false;
    }
    
    RTC_TimeTypeDef time = {.Hours = timeptr->tm_hour,
                            .Minutes = timeptr->tm_min,
                            .Seconds = timeptr->tm_sec,};
    hal_status = HAL_RTC_SetTime(&hrtc, &time, RTC_FORMAT_BIN);
    if(hal_status == HAL_OK)
    {
        /*时间设置成功*/
    }
    else
    {
        /*时间设置失败*/
        return false;
    }      
    
    return true;
}

/*******************************************************************************
* Function Name : 
* Description   : 查询linux时间戳
* Input         :           
* Output        :         
* Return        :         
*******************************************************************************/
uint32_t RTC_TimestampGet(void)
{
    return Rtc.timestamp;
}

/*******************************************************************************
* Function Name : 
* Description   : 查询时间戳(带有小数点)
* Input         :           
* Output        :         
* Return        :         
*******************************************************************************/
float RTC_TimestampWithPointGet(void)
{
    uint16_t hight = READ_REG(hrtc.Instance->DIVH);
    uint16_t lower = READ_REG(hrtc.Instance->DIVL);
    
    float time_decimal = ((hight << 16) + lower) / 32768.0;
    
    return (Rtc.timestamp + time_decimal);
}

/*******************************************************************************
* Function Name : 
* Description   : 查询时间戳(带有小数点)
* Input         :           
* Output        :         
* Return        :         
*******************************************************************************/
uint8_t * RTC_TimestampWithPointByStrGet(void)
{
    uint16_t hight = READ_REG(hrtc.Instance->DIVH);
    uint16_t lower = READ_REG(hrtc.Instance->DIVL);
    
    float time_decimal = ((hight << 16) + lower) / 32768.0;
    
    struct tm * tm_time;
    uint32_t time = Rtc.timestamp + 8 * 3600;
    tm_time = localtime(&time);
    
    sprintf((char *)Rtc.timestr, "[%d-%d-%d %d:%d:%d %f]", tm_time->tm_year - 100, 
            tm_time->tm_mon + 1, tm_time->tm_mday, tm_time->tm_hour, tm_time->tm_min,
            tm_time->tm_sec, time_decimal);
    return Rtc.timestr;
}

/*******************************************************************************
* Function Name : 
* Description   : linux时间戳更新函数 
* Input         :           
* Output        :         
* Return        :         
*******************************************************************************/
bool RTC_UpdateTimerCallback(void)
{
    RTC_TimeTypeDef time;
    HAL_StatusTypeDef hal_status = HAL_RTC_GetTime(&hrtc, &time, RTC_FORMAT_BIN);
    if(hal_status != HAL_OK)
    {
        /*查询时间失败*/
        return false;
    }
    else
    {
        /*查询时间成功*/
        struct tm tm_time = 
        {
            .tm_year = hrtc.DateToUpdate.Year + 100,
            .tm_mon = hrtc.DateToUpdate.Month -1,
            .tm_mday = hrtc.DateToUpdate.Date,
            .tm_hour = time.Hours,
            .tm_min = time.Minutes,
            .tm_sec = time.Seconds,
        };
        
        Rtc.timestamp = mktime(&tm_time);
    }
    
    return true;
}














