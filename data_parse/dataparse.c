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
 
    uint8_t * pconstdata = pBuffInfo->Ptr;                                                          //��ʼ��ȡʱ����ȡ����ͷָ��
    uint32_t constdatalen = pBuffInfo->Length;                                                      //��ʼ��ȡʱ����ȡ���ݳ���
    
    uint8_t * pdata = pBuffInfo->Ptr;                                                               //����ȡ����ͷָ��
    uint32_t datalen = pBuffInfo->Length;                                                           //����ȡ���ݳ���    
    
    uint8_t cnti = 0;                                                                               //���ݰ�����ȡ����֡����
    
    do
    {
        ptr = u_memstr(pdata, "\x7e\x7f", datalen);                                                 //�������ض��ַ�����ͷ������֡
        if(ptr != NULL)
        {
            pDataFrameGroupInfo->Unit[cnti].Ptr = ptr;                                             //��¼���ҵ������ض��ַ�����ͷ������֡
            
            pdata += 1;                                                                             //���´����Ҵ洢�ռ�ָ��λ��
            datalen = constdatalen - (ptr - pconstdata);                                            //���´����Ҵ洢�ռ䳤��     
              
            cnti++;                                                                                 //���Ҵ����ۼ�
        }
        else
        {
            break;
        }
    }while(cnti < EXTRACT_DATA_FRAME_MAX_NUM);
    
    uint8_t cntj = 0;
    
    switch(cnti)                                                                                    //������ȡ����ÿһ֡���ݵĳ���
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
            while(cntj < (cnti - 1))                                                                //����ÿһ֡���ݵĳ���
            {
                pDataFrameGroupInfo->Unit[cntj].Length =  
                (uint8_t *)pDataFrameGroupInfo->Unit[cntj + 1].Ptr - (uint8_t *)pDataFrameGroupInfo->Unit[cntj].Ptr;
                cntj++;
            }     
            
            pDataFrameGroupInfo->Unit[cntj].Length = 
            constdatalen - ((uint8_t *)pDataFrameGroupInfo->Unit[cntj].Ptr - pconstdata);  
        }break;
    }
    
    return cnti;                                                                                    //������ȡ��������֡֡��
}

/*************************************************************************************************
* Function Name : DataFrameFormatCheck()
* Description   : ����֡��ʽ���
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





















