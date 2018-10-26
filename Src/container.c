#include<stdbool.h>
#include<stdint.h>
#include<stdlib.h>
#include<string.h>
#include "container.h"

/*Èí¼þ°æ±¾ºÅv0.0*/

/*******************************************************************************
* Brief		:  
* Param    	: 
* Return	:      
*******************************************************************************/
bool malloc_container(struct container * pcont, uint32_t len)
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
* Brief		:  
* Param    	: 
* Return	:      
*******************************************************************************/
void free_container(struct container * pcont)
{
	if(pcont != NULL)
	{
		free(pcont->pbuff);
	}
}

/*******************************************************************************
* Brief		:  
* Param    	: 
* Return	:      
*******************************************************************************/
bool fill_container(struct container * pcont, uint8_t * psrc, uint32_t len)
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
* Brief		:  
* Param    	: 
* Return	:      
*******************************************************************************/
void clear_container(struct container * pcont)
{
	pcont->data_len = 0;
}




























