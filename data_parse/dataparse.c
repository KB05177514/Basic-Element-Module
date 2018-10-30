#include "dataparse.h"

/*************************************************************************************************
* Function Name : DataPacketExtract()
* Description   : 
* Input         :           
* Output        :         
* Return        :         
*************************************************************************************************/
uint8_t DataPacketExtract(BuffInfoTypeDef * pBuffInfo, DataFrameGroupInfoTypeDef * pDataFrameGroupInfo)
{
    uint8_t * ptr = NULL;
 
    uint8_t * pconstdata = pBuffInfo->Ptr;                                                          //开始提取时待提取数据头指针
    uint32_t constdatalen = pBuffInfo->Length;                                                      //开始提取时待提取数据长度
    
    uint8_t * pdata = pBuffInfo->Ptr;                                                               //待提取数据头指针
    uint32_t datalen = pBuffInfo->Length;                                                           //待提取数据长度    
    
    uint8_t cnti = 0;                                                                               //数据包中提取数据帧次数
    
    do
    {
        ptr = u_memstr(pdata, "\x7e\x7f", datalen);                                                 //查找以特定字符串开头的数据帧
        if(ptr != NULL)
        {
            pDataFrameGroupInfo->Unit[cnti].Ptr = ptr;                                             //记录查找到的以特定字符串开头的数据帧
            
            pdata += 1;                                                                             //更新待查找存储空间指针位置
            datalen = constdatalen - (ptr - pconstdata);                                            //更新待查找存储空间长度     
              
            cnti++;                                                                                 //查找次数累加
        }
        else
        {
            break;
        }
    }while(cnti < EXTRACT_DATA_FRAME_MAX_NUM);
    
    uint8_t cntj = 0;
    
    switch(cnti)                                                                                    //计算提取到的每一帧数据的长度
    {
        case 0x00:
        {
            //pass
        }break;
        
        case 0x01:
        {
            pDataFrameGroupInfo->Unit[0].Length = 
            constdatalen - ((uint8_t*)pDataFrameGroupInfo->Unit[0].Ptr - pconstdata);
        }break;
        
        default:
        {
            while(cntj < (cnti - 1))                                                                //计算每一帧数据的长度
            {
                pDataFrameGroupInfo->Unit[cntj].Length =  
                (uint8_t *)pDataFrameGroupInfo->Unit[cntj + 1].Ptr - (uint8_t *)pDataFrameGroupInfo->Unit[cntj].Ptr;
                cntj++;
            }     
            
            pDataFrameGroupInfo->Unit[cntj].Length = 
            constdatalen - ((uint8_t *)pDataFrameGroupInfo->Unit[cntj].Ptr - pconstdata);  
        }break;
    }
    
    return cnti;                                                                                    //返回提取到的数据帧帧数
}

/*************************************************************************************************
* Function Name : DataFrameFormatCheck()
* Description   : 数据帧格式检查
* Input         :           
* Output        :         
* Return        :         
*************************************************************************************************/
DataFrameStatusTypeDef DataFrameFormatCheck(DataFrameInfoTypeDef * pDataFrameInfo)
{
    uint8_t * ptr = (uint8_t *)pDataFrameInfo->Ptr;
    uint32_t len = pDataFrameInfo->Length;
  
    uint16_t temp_16 = 0;
    
    memcpy(&temp_16, ptr + 2, sizeof(temp_16));
    EndianTransform(&temp_16, sizeof(temp_16));
    if(temp_16 != len)
    {
        return DATA_FRAME_LENGTH_ERROR;
    }
    
    temp_16 = CRC16_ccitt(ptr, len - 2);
    EndianTransform(&temp_16, sizeof(temp_16));
    if(memcmp((ptr + len - 2), &temp_16, sizeof(temp_16)) != 0)
    {
        return DATA_FRAME_CHECK_ERROR;
    }
    
    return DATA_FRAME_OK;
}





















