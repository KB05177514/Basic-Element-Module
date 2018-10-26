#include<stdbool.h>
#include<stdint.h>
#include<stdlib.h>
#include<string.h>
#include "buffer_container.h"

/*Èí¼þ°æ±¾ºÅv0.1*/

/*******************************************************************************
* Brief		: ÉêÇë»º³åÈÝÆ÷ 
* Param    	: @ pcont:´ýÉêÇë»º³åÈÝÆ÷Ö¸Õë;@ len:´ýÉêÇëÈÝÆ÷´óÐ¡(byte)
* Return	: @ true:ÉêÇë³É¹¦;@ false:ÉêÇëÊ§°Ü     
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
* Brief		: ÊÍ·Å»º³åÈÝÆ÷ 
* Param    	: @ pcont:´ýÊÍ·ÅÈÝÆ÷Ö¸Õë
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
* Brief		: Ïò»º³åÈÝÆ÷Ìî³äÊý¾Ý 
* Param    	: @ pcont:´ýÌî³äÊý¾ÝÈÝÆ÷Ö¸Õë;@ psrc:´ýÌî³äÊý¾ÝÖ¸Õë;@ len:´ýÌî³äÊý¾Ý³¤¶È
* Return	: @ true:Ìî³äÊý¾Ý³É¹¦;@ false:Ìî³äÊý¾ÝÊ§°Ü(»º³åÇø²»×ã)     
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
* Brief		: Çå¿Õ»º³åÈÝÆ÷ 
* Param    	: @ pcont:´ýÇåÀí»º³åÈÝÆ÷Ö¸Õë
* Return	:      
*******************************************************************************/
void buffer_container_clear(struct buffer_container * pcont)
{
	pcont->data_len = 0;
}


















