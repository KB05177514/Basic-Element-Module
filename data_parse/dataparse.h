#ifndef __DATAPARSE_H
#define __DATAPARSE_H

#include "Ulib.h"
#include "crc16.h"

/*************************************************************************************************
* 1、宏定义
*
*************************************************************************************************/
#define EXTRACT_DATA_FRAME_MAX_NUM                          5

/*************************************************************************************************
* 2、结构体定义
*
*************************************************************************************************/
typedef enum
{
    DATA_FRAME_OK               = 0,
    DATA_FRAME_LENGTH_ERROR     = 1,
    DATA_FRAME_CHECK_ERROR      = 2
}DataFrameStatusTypeDef;

typedef struct
{
    void * Ptr;
    uint32_t Length;
}DataPacketInfoTypeDef;

typedef struct
{
    void * Ptr;
    uint32_t Length;
}DataFrameInfoTypeDef;

typedef struct
{
    bool Flag;
    uint8_t * const Ptr;
    uint32_t Length;
}BuffInfoTypeDef;

typedef struct
{
    DataFrameInfoTypeDef Unit[EXTRACT_DATA_FRAME_MAX_NUM];
}DataFrameGroupInfoTypeDef;

/*************************************************************************************************
* 3、外部函数声明
*
*************************************************************************************************/
uint8_t DataPacketExtract(BuffInfoTypeDef * pBuffInfo, DataFrameGroupInfoTypeDef * pDataFrameGroupInfo);
DataFrameStatusTypeDef DataFrameFormatCheck(DataFrameInfoTypeDef * pDataFrameInfo);



















#endif