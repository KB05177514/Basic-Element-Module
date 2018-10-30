#include "table_schedule.h"

/************************************************************************************************************
* 1������������                                                                                                     
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
* 2����������                                                                                                     
************************************************************************************************************/


/************************************************************************************************************
* 3����������                                                                                                     
************************************************************************************************************/
/*************************************************************************************************
* Function Name : 
* Description   : �¼���ʼ��
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
* Description   : �¼�������
* Input         :           
* Output        :         
* Return        :         
*************************************************************************************************/
void EventTblSet(EventTypeDef * pEvent, uint8_t index)
{
    /*��������*/
    index &= 0x3F;                                                              
  
    pEvent->Grp |= MapTbl[index >> 3];
    pEvent->Tbl[index >> 3] |= MapTbl[index & 0x07];
}

/*************************************************************************************************
* Function Name : 
* Description   : �¼�������
* Input         :           
* Output        :         
* Return        :         
*************************************************************************************************/
void static EventTblClear(EventTypeDef * pEvent, uint8_t index)
{   
    /*��������*/
    index &= 0x3F;                                                              
  
    if((pEvent->Tbl[index >> 3] &= ~MapTbl[index & 0x07]) == 0x00)
    {
        pEvent->Grp &= ~MapTbl[index >> 3];
    }
}

/*************************************************************************************************
* Function Name : 
* Description   : �¼����Ƿ�Ϊ��
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
* Description   : �����¼�Ϊ��
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
* Description   : �¼���ռ���¼���ָ� 
* Input         :           
* Output        :         
* Return        :         
*************************************************************************************************/
static bool EventPreemptiveAndEventTblResume(EventTypeDef * pEvent, uint8_t index)
{
    uint8_t result = false;
    
    if((index <= EVENT_INDEX_ADMIN_4) && (index < pEvent->Index))
    {
         /*����ռ�¼��¼���ָ�*/
        EventTblSet(pEvent ,pEvent->Index);
        /*�����¼�����*/
        pEvent->Index = index;    
        result = true;
    }
    
    return result;
}

/*************************************************************************************************
* Function Name : 
* Description   : �¼����� 
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
    
    switch(index)                                                               //ɸѡ�¼�
    {
        case EVENT_INDEX_ADMIN_0: 
        case EVENT_INDEX_ADMIN_1:                                                //��Ȩ�¼�    
        case EVENT_INDEX_ADMIN_2:       
        case EVENT_INDEX_ADMIN_3:
        case EVENT_INDEX_ADMIN_4:
        {
            /*��Ȩ�¼�����*/
            result = EventPreemptiveAndEventTblResume(pEvent, index);           
        }break;
        
        case EVENT_INDEX_SYSTEM_IDLE:
        {
            result = false;                                                              
        }break;
        
        default:                                                                //һ���¼�
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
    
    if(result == true)                                                          //�����¼���        
    {
        EventTblClear(pEvent, index);
    }
    
    return result;
}







