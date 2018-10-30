#include "define.h"

/*******************************************************************************
* Brief		:  
* Param    	: 
* Return	:      
*******************************************************************************/
bool float_circular_container_malloc(struct float_circular_container * pcrc_cont, uint32_t len)
{
	float * pbuff = malloc(sizeof(float) * len);
	if(pbuff == NULL)
	{
		return false;
	}

	pcrc_cont->pbuff = pbuff;
	pcrc_cont->len = len;
	pcrc_cont->count = 0;
	pcrc_cont->position = 0;
	
	return true;
}

/*******************************************************************************
* Brief		:  
* Param    	: 
* Return	:      
*******************************************************************************/
void float_circular_container_free(struct float_circular_container * pcrc_cont)
{
	free(pcrc_cont.pbuff);
}

/*******************************************************************************
* Brief		:  
* Param    	: 
* Return	:      
*******************************************************************************/
void float_circular_container_fill(struct float_circular_container * pcrc_cont, float data)
{
	pcrc_cont->pbuff[pcrc_cont->position] = data;
	pcrc_cont->position++;
	pcrc_cont->position %= pcrc_cont->len;
	pcrc_cont->count++;
	if(pcrc_cont->count >= pcrc_cont->len)
	{
		pcrc_cont->count = pcrc_cont->len;
	}
}

/*******************************************************************************
* Brief		:  
* Param    	: 
* Return	:      
*******************************************************************************/
void float_circular_container_clear(struct float_circular_container * pcrc_cont)
{
	pcrc_cont->count = 0;
	pcrc_cont->position = 0;
}

