#include<stdint.h>
#include<string.h>


/*******************************************************************************
* Description   :��С�˸�ʽת��   
* Param         :@pData ��ת������ָ��
                :@Len ��ת�����ݳ���
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








