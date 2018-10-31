#include<stdint.h>
#include<stdbool.h>
#include<ctype.h>

/*******************************************************************************
* Description   : һ���ֽ�hex��תΪAscii�� 
* Param         : @SrcData:��ת��hex����
* Return        : ��:0x37=>'3'<<8 + '7'     
*******************************************************************************/
int16_t HexToAscii(int8_t SrcData)
{
    int16_t des_data = 0;
    
    if((SrcData >> 4) >= 0x0A)
    {
        des_data = (SrcData >> 8) - 0x0A + 'A';
    }
    else
    {
        des_data = (SrcData >> 8) + '0';
    }
    des_data <<= 8;
    
    if((SrcData & 0x0F) >= 0x0A)
    {
        des_data |= (SrcData & 0x0F) - 0x0A + 'A';
    }
    else
    {
        des_data |= (SrcData & 0x0F) + '0';
    }
    
    return des_data;
}

/*******************************************************************************
* Description   : ����ֽ�hexת��Ϊascii��
* Param         : @pSrc:��ת��hex��ָ��;@Len:��ת��hex�볤��;@pDes:ת�����ָ��
* Return        :      
*******************************************************************************/
void HexToAsciiS(uint8_t * pSrc, uint32_t Len, uint8_t * pDes)
{
    uint32_t cnti = 0;
    
    for(; cnti < Len; cnti++)
    {
        uint8_t tmp_hight = *(pSrc + cnti) >> 4;
        uint8_t tmp_lower = *(pSrc + cnti) & 0x0F;
      
        if(tmp_hight >= 0x0A)
        {
            *(pDes + 2*cnti) = (tmp_hight - 0x0A) + 'A';
        }
        else
        {
            *(pDes + 2*cnti) = tmp_hight + '0';
        }
        
        if(tmp_lower >= 0x0A)
        {
            *(pDes + 2*cnti + 1) = (tmp_lower - 0x0A) + 'A';
        }
        else
        {
            *(pDes + 2*cnti + 1) = tmp_lower + '0';
        }
    }    
}

/*******************************************************************************
* Description   : �����ֽڵ�ascii��ת��Ϊhex�� 
* Param         : @DataHigh:��ת�����ֽ�ascii��;@DataLower:��ת�����ֽ�ascii��
*				: @ResultData:ת�����
* Return        : @true:�����Ϸ�,false:�������Ϸ�     
*******************************************************************************/
bool AsciiToHex(int8_t DataHigh, int8_t DataLower, int8_t ResultData)
{
    /*��ڲ����ж�*/
    if((isxdigit(DataHigh) && isxdigit(DataLower)) == false)
    {
        return false;
    }
    /*������ĸ,��ת��Ϊ��д*/
    if(isxdigit(DataHigh))
    {
        DataHigh = (int8_t)toupper(DataHigh);
    }
    /*������ĸ,��ת��Ϊ��д*/
    if(isxdigit(DataLower))
    {
        DataLower = (int8_t)toupper(DataLower);
    }
  
    if(DataHigh >= 'A')
    {
        ResultData = DataHigh - 'A' + 0x0A;
    }
    else
    {
        ResultData = DataHigh - '0';
    }
    ResultData <<= 4;
    
    if(DataLower >= 'A')
    {
        ResultData |= DataLower - 'A' + 0x0A;
    }
    else
    {
        ResultData |= DataLower - '0';
    }
    
    return true;
}

/*******************************************************************************
* Description   : ����ֽڵ�ascii��תΪhex�� 
* Param         : @pSrc:��ת��ascii��ָ��;@Len:��ת��ascii�볤��
*				: @pDes:ת�����ָ��
* Return        : @true:��ת�����ݲ����Ϸ�,false:��ת�����ݲ����Ƿ�     
*******************************************************************************/
bool AsciiToHexS(uint8_t * pSrc, uint32_t Len, uint8_t * pDes)
{
    uint32_t cnti = 0;
    
    for(; cnti < (Len / 2); cnti++)
    {
        if(AsciiToHex(*(pSrc + cnti*2), *(pSrc + cnti*2 + 1), *(pDes + cnti)) != true)
        {
            return false;
        }
    }
    
    return true;
}

/*******************************************************************************
* Description   : Convert a 2 digit decimal to BCD format
* Param         : @Value:Byte to be converted
* Return        : @Converted byte     
*******************************************************************************/
uint8_t ByteToBcd2(uint8_t Value)
{
  uint32_t bcdhigh = 0U;

  while(Value >= 10U)
  {
    bcdhigh++;
    Value -= 10U;
  }

  return  ((uint8_t)(bcdhigh << 4U) | Value);
}

/*******************************************************************************
* Description   : Convert from 2 digit BCD to Binary
* Param         : @Value:BCD value to be converted
* Return        : @Converted word     
*******************************************************************************/
uint8_t Bcd2ToByte(uint8_t Value)
{
  uint32_t tmp = 0U;
  tmp = ((uint8_t)(Value & (uint8_t)0xF0U) >> (uint8_t)0x4U) * 10U;
  return (tmp + (Value & (uint8_t)0x0FU));
}
























