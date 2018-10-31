#include "kb_lib.h"
#include "crc16.h"
#include "debug_write.h"
#include "data_parse.h"

/*******************************************************************************
* 1���궨��    
*******************************************************************************/
typedef enum
{
    FORMAT_OK       = 0,                                                    	//����֡����
    HEADER_ERROR    = 1,                                                       	//֡ͷ����        
    LENGTH_ERROR    = 2,                                                     	//֡���ȴ���
    CHECK_ERROR     = 3                                                      	//У�����
}DataFormatTypeDef;
/*******************************************************************************
* Brief		: �������ݱ���֡ͷλ�� 
* Param    	: @pSrc:����������ָ��;@Len:���������ݳ���;@Start_Pos:��������ʼλ��
* Return	: @-1:δ�ҵ�֡ͷ,>=0:֡ͷλ��     
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
* Brief		: ��ȡ���ݱ��������ݳ�����Ϣ 
* Param    	: @pSrc:����������ָ��;@Len:���������ݳ���;@Start_Pos:��������ʼλ��
* Return	: @-1:����ֵ�쳣,>=0:����֡����   
*******************************************************************************/
static int16_t ExtractDataLen(uint8_t * pSrc, uint32_t Len, uint32_t Start_Pos)
{
    uint16_t temp_16 = 0;
    
    memcpy(&temp_16, (pSrc + Start_Pos + 2), sizeof(temp_16));
    EndianTransform(&temp_16, sizeof(temp_16));
    
    if(temp_16 > (Len - Start_Pos))                                        		//����ֵ�쳣
    {
        return -1;
    }
    else
    {
        return temp_16;
    }
}
/*******************************************************************************
* Brief		: ���ݱ���У���� 
* Param    	: @pSrc:��У������ָ��;@Len:��У�����ݳ���
* Return	: @false:У��ʧ��,true:У��ͨ��     
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
* Brief		: ���Ժ�������ӡ���ݽ����еĴ�����Ϣ 
* Param    	: @DataFormat:����֡״̬;@pSrc:log�����ַ��� 
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
            Log("[time:%d]��������֡-֡ͷ����!\n", HAL_GetTick());
        }break;
        
        case LENGTH_ERROR:
        {
            Log("[time:%d]%s.\n", HAL_GetTick(), pStr);          
            Log("[time:%d]��������֡-���ȴ���!\n", HAL_GetTick());            
        }break;
        
        case CHECK_ERROR:
        {
            Log("[time:%d]%s.\n", HAL_GetTick(), pStr);          
            Log("[time:%d]��������֡-У�����!\n", HAL_GetTick());          
        }break;
        
        default:
        {
            Log("[time:%d]%s.\n", HAL_GetTick(), pStr);          
            Log("[time:%d]��������֡-δ֪����!\n", HAL_GetTick());          
        }break;
    }
}
/*******************************************************************************
* Brief		: ��ȡ���ݱ��� 
* Param    	: @pSrc:����������ָ��;@Len:���������ݳ���;
*			: @pParseFunc:�����������@pStr:����log��Ϣ
* Return	:      
*******************************************************************************/
void ExtractPacket(uint8_t * pSrc, uint32_t Len, ParsePacket pParseFunc, uint8_t * pStr)
{
    uint32_t data_start = 0;
    DataFormatTypeDef dataformat = FORMAT_OK;
    
    while((pSrc + Len) > (pSrc + data_start))                                	//ѭ���˳���
    {
        data_start = FindCmdStart(pSrc, Len, data_start);
        if(data_start == -1)                                                  	//δ�ҵ�֡ͷ
        {
            dataformat = HEADER_ERROR;            
            
            ExtractPacketDebug(dataformat, pStr);                           	//���Ժ���        
            
            break;                                                          	//ѭ���˳���
        }
        
        int16_t data_len = ExtractDataLen(pSrc, Len, data_start);
        if(data_len == -1)                                                   	//���ݱ��ĳ�����ȡ����
        {
            data_start += 2;
          
            dataformat = LENGTH_ERROR;   
            
            ExtractPacketDebug(dataformat, pStr);                              	//���Ժ���  
                         
            continue;
        }
        
        bool data_check = DataCheck((pSrc + data_start), data_len);         	//����У����
        if(data_check == false)
        {
            data_start += data_len;
          
            dataformat = CHECK_ERROR;
            
            ExtractPacketDebug(dataformat, pStr);                          		//���Ժ���  
                       
            continue;
        }
        
        (*pParseFunc)((pSrc + data_start), data_len);                        	//�������ݱ���
                
        data_start += data_len;                                               	//ע���λ�ã���������¸���ʼλ���Ѿ�Խ��                         
    }
}

