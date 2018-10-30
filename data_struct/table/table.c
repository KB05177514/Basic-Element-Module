#include<stdint.h>
#include<stdlib.h>
#include<string.h>

/*******************************************************************************
* Brief		: ��ȡ������ЧԪ������ 
* Param    	: @ pelement:������ָ��;@ size:��ߴ�;@ element_num:������ЧԪ�ظ���
* Return	: @ -1:��������; -2:�ռ����ʧ��; 0:���óɹ�     
*******************************************************************************/
int8_t table_get_valid_element_count(void * pelement, uint8_t size, uint8_t * element_num)
{
    /*���ݳߴ����32�ֽ�*/
    if(size > 32)
    {
        /*��������*/
        return -1;
    }
    
    uint32_t cnti = 0;
    int32_t number = 0;
    uint8_t * pbuff = malloc(size);
    
    memcpy(pbuff, pelement, size);
    
    if(pbuff == NULL)
    {
        /*�ռ����ʧ��*/
        return -2;
    }
    
    for(; cnti < size*8; cnti++)
    {
        if(pbuff[cnti/8] & (0x01 << (cnti % 8)))
        {
            number++;
        }
    }

    *element_num = number; 
    
    free(pbuff);
    
    return 0;
}















