#include "kb_lib.h"
#include "crc16.h"
#include "debug_write.h"
#include "data_parse.h"

/*******************************************************************************
* 1、宏定义    
*******************************************************************************/
typedef enum
{
    FORMAT_OK       = 0,                                                    	//数据帧正常
    HEADER_ERROR    = 1,                                                       	//帧头错误        
    LENGTH_ERROR    = 2,                                                     	//帧长度错误
    CHECK_ERROR     = 3                                                      	//校验错误
}DataFormatTypeDef;
/*******************************************************************************
* Brief		: 查找数据报文帧头位置 
* Param    	: @pSrc:待解析数据指针;@Len:待解析数据长度;@Start_Pos:待解析开始位置
* Return	: @-1:未找到帧头,>=0:帧头位置     
*******************************************************************************/
static int32_t FindCmdStart(uint8_t * pSrc, uint32_t Len, uint32_t Start_Pos)
{
    uint32_t cnti;
    
    for(cnti = Start_Pos; cnti < (Len - 1); cnti++)
    {
        if((pSrc[cnti] == 0x7E) && (pSrc[cnti + 1] == 0x7F))
        {
            return cnti;
        }
    }
    
    return -1;
}
/*******************************************************************************
* Brief		: 提取数据报文中数据长度信息 
* Param    	: @pSrc:待解析数据指针;@Len:待解析数据长度;@Start_Pos:待解析开始位置
* Return	: @-1:长度值异常,>=0:数据帧长度   
*******************************************************************************/
static int16_t ExtractDataLen(uint8_t * pSrc, uint32_t Len, uint32_t Start_Pos)
{
    uint16_t temp_16 = 0;
    
    memcpy(&temp_16, (pSrc + Start_Pos + 2), sizeof(temp_16));
    EndianTransform(&temp_16, sizeof(temp_16));
    
    if(temp_16 > (Len - Start_Pos))                                        		//长度值异常
    {
        return -1;
    }
    else
    {
        return temp_16;
    }
}
/*******************************************************************************
* Brief		: 数据报文校验检查 
* Param    	: @pSrc:待校验数据指针;@Len:待校验数据长度
* Return	: @false:校验失败,true:校验通过     
*******************************************************************************/
static bool DataCheck(uint8_t * pSrc, uint32_t Len)
{
    uint16_t temp_16 = 0;
    
    temp_16 = CRC16_ccitt(pSrc, Len - 2);
    EndianTransform(&temp_16, sizeof(temp_16));
    if(memcmp((pSrc + Len - 2), &temp_16, sizeof(temp_16)) == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}
/*******************************************************************************
* Brief		: 调试函数，打印数据解析中的错误信息 
* Param    	: @DataFormat:数据帧状态;@pSrc:log带入字符串 
* Return	:      
*******************************************************************************/
static void ExtractPacketDebug(DataFormatTypeDef DataFormat, uint8_t * pStr)
{
    switch(DataFormat)
    {
        case FORMAT_OK:
        {       
          
        }break;
        
        case HEADER_ERROR:
        {
            Log("[time:%d]%s.\n", HAL_GetTick(), pStr);
            Log("[time:%d]解析数据帧-帧头错误!\n", HAL_GetTick());
        }break;
        
        case LENGTH_ERROR:
        {
            Log("[time:%d]%s.\n", HAL_GetTick(), pStr);          
            Log("[time:%d]解析数据帧-长度错误!\n", HAL_GetTick());            
        }break;
        
        case CHECK_ERROR:
        {
            Log("[time:%d]%s.\n", HAL_GetTick(), pStr);          
            Log("[time:%d]解析数据帧-校验错误!\n", HAL_GetTick());          
        }break;
        
        default:
        {
            Log("[time:%d]%s.\n", HAL_GetTick(), pStr);          
            Log("[time:%d]解析数据帧-未知错误!\n", HAL_GetTick());          
        }break;
    }
}
/*******************************************************************************
* Brief		: 提取数据报文 
* Param    	: @pSrc:待解析数据指针;@Len:待解析数据长度;
*			: @pParseFunc:带入解析函数@pStr:带入log信息
* Return	:      
*******************************************************************************/
void ExtractPacket(uint8_t * pSrc, uint32_t Len, ParsePacket pParseFunc, uint8_t * pStr)
{
    uint32_t data_start = 0;
    DataFormatTypeDef dataformat = FORMAT_OK;
    
    while((pSrc + Len) > (pSrc + data_start))                                	//循环退出点
    {
        data_start = FindCmdStart(pSrc, Len, data_start);
        if(data_start == -1)                                                  	//未找到帧头
        {
            dataformat = HEADER_ERROR;            
            
            ExtractPacketDebug(dataformat, pStr);                           	//调试函数        
            
            break;                                                          	//循环退出点
        }
        
        int16_t data_len = ExtractDataLen(pSrc, Len, data_start);
        if(data_len == -1)                                                   	//数据报文长度提取错误
        {
            data_start += 2;
          
            dataformat = LENGTH_ERROR;   
            
            ExtractPacketDebug(dataformat, pStr);                              	//调试函数  
                         
            continue;
        }
        
        bool data_check = DataCheck((pSrc + data_start), data_len);         	//报文校验检查
        if(data_check == false)
        {
            data_start += data_len;
          
            dataformat = CHECK_ERROR;
            
            ExtractPacketDebug(dataformat, pStr);                          		//调试函数  
                       
            continue;
        }
        
        (*pParseFunc)((pSrc + data_start), data_len);                        	//解析数据报文
                
        data_start += data_len;                                               	//注意该位置，正常情况下该起始位置已经越界                         
    }
}

