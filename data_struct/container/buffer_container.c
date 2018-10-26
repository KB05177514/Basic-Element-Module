#include<stdbool.h>
#include<stdint.h>
#include<stdlib.h>
#include<string.h>
#include "buffer_container.h"

/*����汾��v0.1*/

/*******************************************************************************
* Brief		: ���뻺������ 
* Param    	: @ pcont:�����뻺������ָ��;@ len:������������С(byte)
* Return	: @ true:����ɹ�;@ false:����ʧ��     
*******************************************************************************/
bool buffer_container_malloc(struct buffer_container * pcont, uint32_t len)
{		
	void* pbuff = malloc(len);
	if(pbuff == NULL)
	{
		return false;
	}

	pcont->pbuff = pbuff;
	pcont->buff_size = len;
	pcont->data_len = 0;

	return true;
}

/*******************************************************************************
* Brief		: �ͷŻ������� 
* Param    	: @ pcont:���ͷ�����ָ��
* Return	:      
*******************************************************************************/
void buffer_container_free(struct buffer_container * pcont)
{
	if(pcont != NULL)
	{
		free(pcont->pbuff);
	}
}

/*******************************************************************************
* Brief		: �򻺳������������ 
* Param    	: @ pcont:�������������ָ��;@ psrc:���������ָ��;@ len:��������ݳ���
* Return	: @ true:������ݳɹ�;@ false:�������ʧ��(����������)     
*******************************************************************************/
bool buffer_container_fill(struct buffer_container * pcont, uint8_t * psrc, uint32_t len)
{
	if(len > (pcont->buff_size - pcont->data_len))
	{
		return false;
	}

	memcpy((pcont->pbuff + pcont->data_len), psrc, len);
	pcont->data_len += len;

	return true;
}

/*******************************************************************************
* Brief		: ��ջ������� 
* Param    	: @ pcont:������������ָ��
* Return	:      
*******************************************************************************/
void buffer_container_clear(struct buffer_container * pcont)
{
	pcont->data_len = 0;
}


















