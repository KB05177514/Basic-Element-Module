#include "coder.h"

/*******************************************************************************
* Description   :大小端格式转换   
* Param         :@pData 带转换数据指针
                :@Len 带转换数据长度
* Return        :None      
*******************************************************************************/
void EndianTransform(void * const pData, const uint8_t Len)
{
    uint8_t temp[8] = {0};
    uint8_t cnti = Len;
    
    memcpy(temp, pData, Len);
    
    while(cnti != 0)
    {
        *((uint8_t *)pData + Len - cnti) = temp[cnti - 1];
        cnti--;
    }
}

/*******************************************************************************
* Description   : 一个字节hex码转为Ascii码 
* Param         : 
* Return        :      
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
* Description   : 多个字节hex转换为ascii码
* Param         : 
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
* Description   : 两个字节的ascii码转换为hex码 
* Param         : 
* Return        :      
*******************************************************************************/
bool AsciiToHex(int8_t DataHigh, int8_t DataLower, int8_t ResultData)
{
    /*入口参数判定*/
    if((isxdigit(DataHigh) && isxdigit(DataLower)) == false)
    {
        return false;
    }
    /*若是字母,则转换为大写*/
    if(isxdigit(DataHigh))
    {
        DataHigh = (int8_t)toupper(DataHigh);
    }
    /*若是字母,则转换为大写*/
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
* Description   : 多个字节的ascii码转为hex码 
* Param         : 
* Return        :      
*******************************************************************************/
bool AsciiToHexS(uint8_t * pSrc, uint32_t Len, uint8_t * pDes)
{
    uint32_t cnti = 0;
    
    for(; cnti < (len / 2); cnti++)
    {
        if(AsciiToHex(*(pSrc + cnti*2), *(pSrc + cnti*2 + 1), *(pDes + cnti)) != true)
        {
            return false;
        }
    }
    
    return true;
}


























