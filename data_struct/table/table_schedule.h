#ifndef __table_schedule_H
#define __table_schedule_H

#include<stdint.h>
#include<stdbool.h>
#include<string.h>

/*************************************************************************************************
* 1 宏定义
*************************************************************************************************/
#define EVENT_INDEX_ADMIN_0                     0
#define EVENT_INDEX_ADMIN_1                     1
#define EVENT_INDEX_ADMIN_2                     2
#define EVENT_INDEX_ADMIN_3                     3
#define EVENT_INDEX_ADMIN_4                     4
#define EVENT_INDEX_SYSTEM_IDLE                63

/*************************************************************************************************
* 2 结构体定义
*************************************************************************************************/
typedef struct
{
    volatile uint8_t Index;
    
    volatile uint8_t Grp;
    
    volatile uint8_t Tbl[8];
}EventTypeDef;

/*************************************************************************************************
* 3 变量声明
*************************************************************************************************/
extern const uint8_t MapTbl[8];
extern const uint8_t UnMapTbl[256];

/*************************************************************************************************
* 4 API声明
*************************************************************************************************/
void EventInit(EventTypeDef * pEvent);
void EventTblSet(EventTypeDef * pEvent, uint8_t eventindex);
bool EventTblIsEmpty(EventTypeDef * pEvent);
void EventIndexClear(EventTypeDef * pEvent);
bool EventSchedule(EventTypeDef * pEvent);



#endif


