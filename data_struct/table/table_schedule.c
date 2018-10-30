#include "table_schedule.h"

/************************************************************************************************************
* 1、常变量定义                                                                                                     
*************************************************************************************************************/
const uint8_t MapTbl[8] = 
{
    0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80
};

const uint8_t UnMapTbl[256] = 
{
    0, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,       /* 0x00 to 0x0F                             */
    4, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,       /* 0x10 to 0x1F                             */
    5, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,       /* 0x20 to 0x2F                             */
    4, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,       /* 0x30 to 0x3F                             */
    6, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,       /* 0x40 to 0x4F                             */
    4, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,       /* 0x50 to 0x5F                             */
    5, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,       /* 0x60 to 0x6F                             */
    4, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,       /* 0x70 to 0x7F                             */
    7, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,       /* 0x80 to 0x8F                             */
    4, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,       /* 0x90 to 0x9F                             */
    5, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,       /* 0xA0 to 0xAF                             */
    4, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,       /* 0xB0 to 0xBF                             */
    6, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,       /* 0xC0 to 0xCF                             */
    4, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,       /* 0xD0 to 0xDF                             */
    5, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,       /* 0xE0 to 0xEF                             */
    4, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0        /* 0xF0 to 0xFF                             */
};

/************************************************************************************************************
* 2、函数声明                                                                                                     
************************************************************************************************************/


/************************************************************************************************************
* 3、函数定义                                                                                                     
************************************************************************************************************/
/*************************************************************************************************
* Function Name : 
* Description   : 事件初始化
* Input         :           
* Output        :         
* Return        :         
*************************************************************************************************/
void EventInit(EventTypeDef * pEvent)
{
    pEvent->Index = EVENT_INDEX_SYSTEM_IDLE;
    
    memset((void *)pEvent->Tbl, 0, 8); 
    pEvent->Grp = 0x00;
    
    EventTblSet(pEvent, EVENT_INDEX_SYSTEM_IDLE);
}

/*************************************************************************************************
* Function Name : 
* Description   : 事件表设置
* Input         :           
* Output        :         
* Return        :         
*************************************************************************************************/
void EventTblSet(EventTypeDef * pEvent, uint8_t index)
{
    /*参数过滤*/
    index &= 0x3F;                                                              
  
    pEvent->Grp |= MapTbl[index >> 3];
    pEvent->Tbl[index >> 3] |= MapTbl[index & 0x07];
}

/*************************************************************************************************
* Function Name : 
* Description   : 事件表清理
* Input         :           
* Output        :         
* Return        :         
*************************************************************************************************/
void static EventTblClear(EventTypeDef * pEvent, uint8_t index)
{   
    /*参数过滤*/
    index &= 0x3F;                                                              
  
    if((pEvent->Tbl[index >> 3] &= ~MapTbl[index & 0x07]) == 0x00)
    {
        pEvent->Grp &= ~MapTbl[index >> 3];
    }
}

/*************************************************************************************************
* Function Name : 
* Description   : 事件表是否为空
* Input         :           
* Output        :         
* Return        :         
*************************************************************************************************/
bool EventTblIsEmpty(EventTypeDef * pEvent)
{
    uint8_t temp_8[8] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80};
    
    if(memcmp((void *)pEvent->Tbl, temp_8, 8) == 0)
    {
        return true;
    }
    else
    {
        return false;
    }      
}

/*************************************************************************************************
* Function Name : 
* Description   : 设置事件为空
* Input         :           
* Output        :         
* Return        :         
*************************************************************************************************/
void EventIndexClear(EventTypeDef * pEvent)
{
    pEvent->Index = EVENT_INDEX_SYSTEM_IDLE;
}

/*************************************************************************************************
* Function Name : 
* Description   : 事件抢占及事件表恢复 
* Input         :           
* Output        :         
* Return        :         
*************************************************************************************************/
static bool EventPreemptiveAndEventTblResume(EventTypeDef * pEvent, uint8_t index)
{
    uint8_t result = false;
    
    if((index <= EVENT_INDEX_ADMIN_4) && (index < pEvent->Index))
    {
         /*被抢占事件事件表恢复*/
        EventTblSet(pEvent ,pEvent->Index);
        /*更新事件索引*/
        pEvent->Index = index;    
        result = true;
    }
    
    return result;
}

/*************************************************************************************************
* Function Name : 
* Description   : 事件调度 
* Input         :           
* Output        :         
* Return        :         
*************************************************************************************************/
bool EventSchedule(EventTypeDef * pEvent)
{
    bool result = false;
       
    uint8_t temp_y = UnMapTbl[pEvent->Grp];
    uint8_t temp_x = UnMapTbl[pEvent->Tbl[temp_y]];   
    uint8_t index = (temp_y << 3) | temp_x;
    
    switch(index)                                                               //筛选事件
    {
        case EVENT_INDEX_ADMIN_0: 
        case EVENT_INDEX_ADMIN_1:                                                //特权事件    
        case EVENT_INDEX_ADMIN_2:       
        case EVENT_INDEX_ADMIN_3:
        case EVENT_INDEX_ADMIN_4:
        {
            /*特权事件调度*/
            result = EventPreemptiveAndEventTblResume(pEvent, index);           
        }break;
        
        case EVENT_INDEX_SYSTEM_IDLE:
        {
            result = false;                                                              
        }break;
        
        default:                                                                //一般事件
        {
            if(pEvent->Index == EVENT_INDEX_SYSTEM_IDLE)
            {
                pEvent->Index = index;
                
                result = true;
            }
            else
            {
                result = false;
            }
        }break;
    }
    
    if(result == true)                                                          //清理事件表        
    {
        EventTblClear(pEvent, index);
    }
    
    return result;
}







