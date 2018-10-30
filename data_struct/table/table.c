#include<stdint.h>
#include<stdlib.h>
#include<string.h>

/*******************************************************************************
* Brief		: 获取表中有效元素数量 
* Param    	: @ pelement:表数据指针;@ size:表尺寸;@ element_num:表中有效元素个数
* Return	: @ -1:参数错误; -2:空间分配失败; 0:调用成功     
*******************************************************************************/
int8_t table_get_valid_element_count(void * pelement, uint8_t size, uint8_t * element_num)
{
    /*数据尺寸最大32字节*/
    if(size > 32)
    {
        /*参数错误*/
        return -1;
    }
    
    uint32_t cnti = 0;
    int32_t number = 0;
    uint8_t * pbuff = malloc(size);
    
    memcpy(pbuff, pelement, size);
    
    if(pbuff == NULL)
    {
        /*空间分配失败*/
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















